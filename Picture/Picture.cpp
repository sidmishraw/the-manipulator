//
//  Picture.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Picture.hpp"
#include <sstream>
#include <cmath>

// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
Manipulator::Picture::Picture(string filePath, float tx, float ty) : Manipulator::ObedientObj() {
    
    this->imagePath = filePath;
    this->selected  = false;
    this->isSelectionRenderPass = false;

    this->tMatrix.set(tx, ty);
    this->sMatrix.set(1.0, 1.0);
    this->theta = 0.0;
    
}

// ------------
//
void Manipulator::Picture::transform() {
    
    this->renderMat.makeIdentityMatrix(); // restore to inital state and then apply the transformations

    this->renderMat.scale(this->sMatrix);
    this->renderMat.rotate(this->theta, 0, 0, 1); // same as ofRotate(degrees) -- rotate along the Z axis
    this->renderMat.translate(this->tMatrix);
    
}

//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
void Manipulator::Picture::render() {

    this->transform(); // update to the latest transformation
    
    // --------------
    
    ofPushMatrix();
    
        ofMultMatrix(this->renderMat); // apply the render mat only for this shape
    
        if (this->isSelectionRenderPass) {
            
            this->manipulator->renderSelectionPass();
        } else {
            
            ofSetColor(255, 255, 255, 255);
            ofSetRectMode(OF_RECTMODE_CENTER); // center the image at the drop point?
            this->contents.draw(0,0);
            
            if(this->selected) {
                
                this->manipulator->show(this->contents.getWidth(),
                                        this->contents.getHeight());
            } else {
                
                this->manipulator->hide(this->contents.getWidth(),
                                        this->contents.getHeight());
            }
        }
    
    ofPopMatrix();

    // --------------
    
    auto mode = this->manipulator->getMode();
    string fpsStr; // mode print string
    
    switch(mode) {
            
        case T: {
            
            fpsStr = "Manipulator mode = Translate";
            
            break;
        }
            
        case RS: {
            
            fpsStr = "Manipulator mode = Rotation + Uniform Scale";
            
            break;
        }
            
        case S: {
            
            fpsStr = "Manipulator mode = Non-Uniform Scale";

            break;
        }
            
        default: {
            
            fpsStr = "";
            
            break;
        }
    };

    ofPushMatrix();
        ofTranslate(ofGetWindowWidth() - fpsStr.size() * 10.25, ofGetWindowHeight() - 32);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(fpsStr, 0, 0);
    ofPopMatrix();
    
}

//
// ----------------------------------------------------------------------------
//
bool Manipulator::Picture::load() {
    
    bool loadStatus = false;
    
    loadStatus = this->contents.load(this->imagePath);
    
    if(!loadStatus) return loadStatus;
    
    this->manipulator = make_shared<PManipulator>(100, 100, this->contents.getWidth(), this->contents.getHeight());
    this->manipulator->setRenderMat(&this->renderMat);
    
    return loadStatus;
}

//
// ----------------------------------------------------------------------------
//
void Manipulator::Picture::drawBorder() {
    
    this->selected = true;
}

//
// ----------------------------------------------------------------------------
//
void Manipulator::Picture::removeBorder() {
    
    this->selected = false;
}

//
// ----------------------------------------------------------------------------
//
bool Manipulator::Picture::isSelected() {

    return this->selected;
}

//
// ----------------------------------------------------------------------------
//
using namespace std;
bool Manipulator::Picture::containsPoint(float x, float y) {
    
    bool status = false;

    status = this->manipulator->canPictureBeSelected(x, y);
    
    return status;
    
}

// ----------------------------------------------------------------------------
//
using namespace std;
void Manipulator::Picture::fromString(string contents) {
    
    istringstream ss (contents);
    
    ss >> this->imagePath; // get the image path
    
    string tx, ty;
    ss >> tx; // get trans Matrix x
    ss >> ty; // get trans Matrix y
    this->tMatrix.set(stof(tx), stof(ty));
    
    string sx, sy;
    ss >> sx; // get scale matrix x
    ss >> sy; // get scale matrix y
    this->sMatrix.set(stof(sx), stof(sy));
    
    string theta;
    ss >> theta; // rotation angle
    this->theta = stof(theta);
    
}

// ----------------------------------------------------------------------------
//
using namespace std;
string Manipulator::Picture::toString() { 
    
    string contents;
    
    contents += this->imagePath + string("\n");
    contents += to_string(this->tMatrix.x) + string("\n");
    contents += to_string(this->tMatrix.y) + string("\n");
    contents += to_string(this->sMatrix.x) + string("\n");
    contents += to_string(this->sMatrix.y) + string("\n");
    contents += to_string(this->theta) + string("\n");
    
    
    return contents;
    
}


// ----------------------------------------------------------------------------
//
//
// Utility function for finding the direction:
// +,+ = a  | +, - = b
// -,+ = c  | -, - = d
char getDirection(float x, float y) {
    if (x >= 0  &&  y >= 0)   return 'a'; // +ve, +ve
    if (x >= 0  &&  y < 0)    return 'b'; // +ve, -ve
    if (x < 0   &&  y >= 0)   return 'c'; // -ve, +ve
    if (x < 0   &&  y < 0)    return 'd'; // -ve, ve
    return '\0';
}

//
// Shrinking utility function
//
void shrink(ofVec2f& s, float delta) {
    s = delta >= 0 && delta < 1.0
        ? s - delta
        : s - (1.0 / delta);
}

//
// Expanding utility function
//
void expand(ofVec2f& s, float delta) {
    s = s + delta;
}

using namespace std;
using namespace Manipulator;
void Manipulator::Picture::processDelta(const ofVec2f &src, const ofVec2f &dest) {
    
    auto manipulatorMode = this->manipulator->getMode();
    
    switch(manipulatorMode) {
        
        case N: {

            // do nothing and bail
            break;
        }
            
        case T: {

            //
            // Translate
            //
            ofVec2f delta = dest - src;
            this->tMatrix = this->tMatrix + delta;
            
            break;
        }
            
        case S: {
       
            //
            // Non-Uniform Scale
            //
            ofVec2f delta = dest - src;
            float yScalingFactor = delta.length() / this->contents.getHeight();
            float xScalingFactor = delta.length() / this->contents.getWidth();
       
            char hbindex = this->manipulator->getHitBoxIndex();
            
            switch (hbindex) {
                
                case 'b': {
                    
                    // top --y scale
                    if (delta.y < 0) {

                        // moved up
                        // expand
                        this->sMatrix.y = this->sMatrix.y + yScalingFactor;
                    } else {

                        // moved down
                        // shrink
                        this->sMatrix.y = yScalingFactor >= 0 && yScalingFactor < 1.0
                            ? this->sMatrix.y - yScalingFactor
                            : this->sMatrix.y - (1.0 / yScalingFactor);
                    }
                    
                    break;
                }
                    
                case 'd' : {
                    
                    // left -- x scale
                    if (delta.x < 0) {
                        
                        // moved left
                        // expand
                        this->sMatrix.x = this->sMatrix.x + xScalingFactor;
                    } else {
                        
                        // moved right
                        // shrink
                        this->sMatrix.x = xScalingFactor >= 0 && xScalingFactor < 1.0
                            ? this->sMatrix.x - xScalingFactor
                            : this->sMatrix.x - (1.0 / xScalingFactor);
                    }
                    
                    break;
                }
                    
                case 'f': {
                    
                    // right -- x scale
                    if (delta.x >= 0) {
                        
                        // moved right
                        // expand
                        this->sMatrix.x = this->sMatrix.x + xScalingFactor;
                    } else {
                        
                        // moved left
                        // shrink
                        this->sMatrix.x = xScalingFactor >= 0 && xScalingFactor < 1.0
                            ? this->sMatrix.x - xScalingFactor
                            : this->sMatrix.x - (1.0 / xScalingFactor);
                    }
                    
                    break;
                }
                    
                case 'h' : {
                    
                    // bottom -- y scale
                    // top --y scale
                    if (delta.y >= 0) {
                        
                        // moved down
                        // expand
                        this->sMatrix.y = this->sMatrix.y + yScalingFactor;
                    } else {
                        
                        // moved up
                        // shrink
                        this->sMatrix.y = yScalingFactor >= 0 && yScalingFactor < 1.0
                            ? this->sMatrix.y - yScalingFactor
                            : this->sMatrix.y - (1.0 / yScalingFactor);
                    }
                    
                    break;
                }

                default: {
                    
                    cout << "not for non-uniform scaling" << endl;
                    break;
                }
            };
            
            break;
        }
            
        case RS: {
            
            //
            // Rotate and uniform scale
            //
            
            //
            // Uniform scaling happend along the diagonals
            // so,
            // D' = D + d, where D is the current diagonal length and d is the delta(magnitude)
            // sf = D' : D = 1 + (d/D)
            // sf ~ d/D
            ofVec2f delta = dest - src;
            float scalingFactor = abs(delta.length() / sqrt(pow(this->contents.getWidth(), 2) + pow(this->contents.getHeight(), 2)));
            
            char hbindex = this->manipulator->getHitBoxIndex();
            
            cout << "hbindex = " << hbindex << endl;
            cout << "delta = " << delta << endl;
            
            switch (hbindex) {
                    
                case 'a': {
                    
                    // top left
                    // +ve x and +ve y = positive scaling = expanding
                    // +ve x and -ve y = rotation clockwise
                    // -ve x and +ve y = rotation anti-clockwise
                    // -ve x and -ve y = negative scaling = shrinking
                    
                    switch(getDirection(delta.x, delta.y)) {
                            
                        case 'a': {
                            
                            // shrink
                            shrink(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                            
                        case 'b': {
                            
                            // rotate clockwise
                            this->theta = this->theta + delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'c': {
                            
                            // rotate anticlockwise
                            this->theta = this->theta - delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'd': {
                            
                            // expand
                            expand(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                    };
                    
                    break;
                }
                    
                case 'c' : {

                    // top right
                    // +ve x and +ve y = rotation clockwise
                    // +ve x and -ve y = positive scaling = expanding
                    // -ve x and +ve y = negative scaling = shrinking
                    // -ve x and -ve y = rotation anti-clockwise
                    
                    switch(getDirection(delta.x, delta.y)) {
                            
                        case 'a': {
                            
                            // rotate clockwise
                            this->theta = this->theta + delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'b': {
                            
                            // expand
                            expand(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                            
                        case 'c': {
                            
                            // shrink
                            shrink(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                            
                        case 'd': {
                            
                            // rotate anti-clockwise
                            this->theta = this->theta - delta.length() * 0.1;
                            
                            break;
                        }
                    };
                    
                    break;
                }
                    
                case 'g': {

                    // bottom left
                    // +ve x and +ve y = rotation anti-clockwise
                    // +ve x and -ve y = negative scaling = shrinking
                    // -ve x and +ve y = positive scaling = expanding
                    // -ve x and -ve y = rotation clockwise
                    
                    switch(getDirection(delta.x, delta.y)) {
                            
                        case 'a': {

                            // anticlockwise rotate
                            this->theta = this->theta - delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'b': {
                            
                            // shrink
                            shrink(this->sMatrix, scalingFactor);
                            break;
                        }
                            
                        case 'c': {
                            
                            // expand
                            expand(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                            
                        case 'd': {

                            // clockwise rotate
                            this->theta = this->theta + delta.length() * 0.1;
                            
                            break;
                        }
                    };
                    
                    break;
                }
                    
                case 'i': {
                    
                    // bottom right
                    // +ve x and +ve y = positive scaling = expanding
                    // +ve x and -ve y = rotation anti-clockwise
                    // -ve x and +ve y = rotation clockwise
                    // -ve x and -ve y = negative scaling = shrinking
                    
                    switch(getDirection(delta.x, delta.y)) {
                            
                        case 'a': {
                            
                            // expand
                            expand(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                            
                        case 'b': {
                            
                            // rotate anticlockwise
                            this->theta = this->theta - delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'c': {
                            
                            // rotate clockwise
                            this->theta = this->theta + delta.length() * 0.1;
                            
                            break;
                        }
                            
                        case 'd': {
                            
                            // shrink
                            shrink(this->sMatrix, scalingFactor);
                            
                            break;
                        }
                    };
                    
                    break;
                }
                    
                default: {
                    
                    cout << "No manipulation possible at this moment" << endl;
                    break;
                }
            };
            
            break;
        }
    };
    
}

// ----------------------------------------------------------------------------
//
/**
 * Makes a new Picture with the saved state.
 */
using namespace std;
shared_ptr<Manipulator::Picture> Manipulator::restore_picture(string savedContents) {
    
    istringstream ss (savedContents);
    
    string imagePath;
    ss >> imagePath; // get the image path
    
    string tx, ty; // get the image's last stored location
    ss >> tx;
    ss >> ty;
    
    auto picture = make_shared<Manipulator::Picture>(imagePath,
                                                     stof(tx),
                                                     stof(ty));
    
    /* -------- attempt to load the picture -------- */
    if(picture->load()) {
        picture->fromString(savedContents);
        return picture;
    }
    /* -------- attempt to load the picture -------- */
    
    picture.reset(); // nullptr
    
    return picture;
    
}

//
// ----- CONSTRAINED TRS --------------------------------- //
//
using namespace Manipulator;
void Manipulator::Picture::translateConstrained(bool isOnX, bool isPositive) {
    
    if (isOnX) {
        
        this->tMatrix.x = isPositive ? this->tMatrix.x + 25 : this->tMatrix.x - 25;
    } else {
        
        this->tMatrix.y = isPositive ? this->tMatrix.y + 25 : this->tMatrix.y - 25;
    }
}

using namespace Manipulator;
void Manipulator::Picture::scaleConstrained(bool isPositive) {
    
    this->sMatrix = isPositive ? this->sMatrix + 0.25 : this->sMatrix - 0.25;
}

using namespace Manipulator;
void  Manipulator::Picture::rotateConstrained(bool isPositive) {
    
    this->theta = isPositive ? this->theta + 15.0 : this->theta - 15.0;
}

//
// ----- CONSTRAINED TRS --------------------------------- //
//




