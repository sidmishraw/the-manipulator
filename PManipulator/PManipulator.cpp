//
//  PManipulator.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/27/18.
//

#include "PManipulator.hpp"

#include <memory>
#include <iostream>

//
// ----------------------------------------------------------------------------
//
using namespace Manipulator;
unsigned char PManipulator::RENDER_GEN = 255;

//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
PManipulator::PManipulator(float p, float q, float w, float h) {

    this->baseR = PManipulator::RENDER_GEN;
    PManipulator::RENDER_GEN --;
    
    this->lc = ofPoint(0, 0);
    this->rc = ofPoint(w, h);
    
    this->mode = N; // no modes selected
}

//
// ----------------------------------------------------------------------------
//
using namespace Manipulator;
void PManipulator::show(float w, float h) {

    this->render(true, w, h);
}

//
// ----------------------------------------------------------------------------
//
using namespace Manipulator;
void PManipulator::hide(float w, float h) {

    this->render(false, w, h);
}

//
// ------------------------------
//
void PManipulator::constructComponents() {

    this->borderColor   = ofColor(this->baseR, 1, 0, 255);
    this->border        = ofRectangle(this->lc, this->rc.x, this->rc.y);

    //
    // for centering the rectangles
    //
    float w = this->rc.x / 2.0;
    float h = this->rc.y / 2.0;

    //
    //
    //
    int rw = 5; // affordance width
    int rh = 5; // affordance height
    //
    //
    //

    this->topLeftCornerColor    = ofColor(this->baseR, 1, 1, 255);
    this->topLeftCorner         = ofRectangle(this->lc.x - w                                , this->lc.y - h                                    , rw, rh);

    this->topRightCornerColor   = ofColor(this->baseR, 1, 2, 255);
    this->topRightCorner        = ofRectangle(this->lc.x + w                                , this->lc.y - h                                    , rw, rh);

    this->bottomLeftCornerColor = ofColor(this->baseR, 1, 3, 255);
    this->bottomLeftCorner      = ofRectangle(this->lc.x - w                                , this->lc.y + h                                    , rw, rh);

    this->bottomRightCornerColor    = ofColor(this->baseR, 1, 4, 255);
    this->bottomRightCorner         = ofRectangle(this->lc.x + w                            , this->lc.y + h                                    , rw, rh);

    this->topColor  = ofColor(this->baseR, 1, 5, 255);
    this->top       = ofRectangle(this->lc.x                                                , this->lc.y - h                                    , rw, rh);

    this->leftColor = ofColor(this->baseR, 1, 6, 255);
    this->left      = ofRectangle(this->lc.x - w                                            , this->lc.y                                        , rw, rh);

    this->bottomColor   = ofColor(this->baseR, 1, 7, 255);
    this->bottom        = ofRectangle(this->lc.x                                            , this->lc.y + h                                    , rw, rh);

    this->rightColor    = ofColor(this->baseR, 1, 8, 255);
    this->right         = ofRectangle(this->lc.x + w                                        , this->lc.y                                        , rw, rh);

    //
    //
    //
    float hbw = w / 3.0; // hitbox width
    float hbh = h / 3.0; // hitbox height
    //
    //
    //

    // for T mode
    this->hitboxColors[1][1]    = ofColor(this->baseR, 2, 4, 255);
    this->hitboxes[1][1]        = ofRectangle(this->lc.x                    , this->lc.y                    , (3.0 * this->rc.x / 4.0)              , (3.0 * this->rc.y / 4.0));

    // for RS mode
    this->hitboxColors[0][0]    = ofColor(this->baseR, 2, 0, 255);
    this->hitboxes[0][0]        = ofRectangle(this->lc.x - 5 * (hbw / 2.0)  , this->lc.y - 5 * (hbh / 2.0)  , hbw                                   , hbh                     );

    this->hitboxColors[2][2]    = ofColor(this->baseR, 2, 8, 255);
    this->hitboxes[2][2]        = ofRectangle(this->lc.x + 5 * (hbw / 2.0)  , this->lc.y + 5 * (hbh / 2.0)  , hbw                                   , hbh                     );

    this->hitboxColors[0][2]    = ofColor(this->baseR, 2, 2, 255);
    this->hitboxes[0][2]        = ofRectangle(this->lc.x + 5 * (hbw / 2.0)  , this->lc.y - 5 * (hbh / 2.0)  , hbw                                   , hbh                     );

    this->hitboxColors[2][0]    = ofColor(this->baseR, 2, 6, 255);
    this->hitboxes[2][0]        = ofRectangle(this->lc.x - 5 * (hbw / 2.0)  , this->lc.y + 5 * (hbh / 2.0)  , hbw                                   , hbh                     );

    // for S mode
    this->hitboxColors[0][1]    = ofColor(this->baseR, 2, 1, 255);
    this->hitboxes[0][1]        = ofRectangle(this->lc.x                    , this->lc.y - 5 * (hbh / 2.0)  , 2.0 * hbw                             , hbh                     );

    this->hitboxColors[1][0]    = ofColor(this->baseR, 2, 3, 255);
    this->hitboxes[1][0]        = ofRectangle(this->lc.x - 5 * (hbw / 2.0)  , this->lc.y                    , hbw                                   , 2.0 * hbh               );

    this->hitboxColors[2][1]    = ofColor(this->baseR, 2, 7, 255);
    this->hitboxes[2][1]        = ofRectangle(this->lc.x                    , this->lc.y + 5 * (hbh / 2.0)  , 2.0 * hbw                             , hbh                     );

    this->hitboxColors[1][2]    = ofColor(this->baseR, 2, 5, 255);
    this->hitboxes[1][2]        = ofRectangle(this->lc.x + 5 * (hbw / 2.0)  , this->lc.y                    , hbw                                   , 2.0 * hbh               );

}


//
// ----------------------------------------------------------------------------
//
using namespace Manipulator;
using namespace std;
void PManipulator::render(bool isSelected, float w, float h) {

    this->constructComponents();
    
    if(!isSelected) {

        this->mode = N;

        return;
    }
    
    ofSetRectMode(OF_RECTMODE_CENTER); // center the rectangle

    switch(this->mode) {
            
        case RS: {
            
            ofSetColor(255, 255, 255);
            ofNoFill();
            ofSetLineWidth(1.0);
            ofDrawRectangle(this->border);
            ofDrawRectangle(this->top);
            ofDrawRectangle(this->right);
            ofDrawRectangle(this->bottom);
            ofDrawRectangle(this->left);

            ofSetColor(0, 255, 0);
            ofNoFill();
            ofSetLineWidth(1.2);
            ofDrawRectangle(this->topRightCorner);
            ofDrawRectangle(this->topLeftCorner);
            ofDrawRectangle(this->bottomRightCorner);
            ofDrawRectangle(this->bottomLeftCorner);
            
            break;
        }
            
        case S: {
            
            ofSetColor(255, 255, 255);
            ofNoFill();
            ofSetLineWidth(1.0);
            ofDrawRectangle(this->border);
            ofDrawRectangle(this->topRightCorner);
            ofDrawRectangle(this->topLeftCorner);
            ofDrawRectangle(this->bottomRightCorner);
            ofDrawRectangle(this->bottomLeftCorner);

            ofSetColor(255, 105, 180);
            ofNoFill();
            ofSetLineWidth(1.5);
            ofDrawRectangle(this->top);
            ofDrawRectangle(this->right);
            ofDrawRectangle(this->bottom);
            ofDrawRectangle(this->left);
            
            break;
        }
            
        case T: {
            
            ofSetColor(255, 0, 0);
            ofNoFill();
            ofSetLineWidth(1.5);
            ofDrawRectangle(this->border);
            
            ofSetColor(255, 255, 255);
            ofNoFill();
            ofSetLineWidth(1.0);
            ofDrawRectangle(this->topRightCorner);
            ofDrawRectangle(this->top);
            ofDrawRectangle(this->topLeftCorner);
            ofDrawRectangle(this->right);
            ofDrawRectangle(this->bottomRightCorner);
            ofDrawRectangle(this->bottom);
            ofDrawRectangle(this->bottomLeftCorner);
            ofDrawRectangle(this->left);
            
            break;
        }
            
        default: {

            // case N -- none
            this->mode = T;
            
            ofSetColor(255, 0, 0);
            ofNoFill();
            ofSetLineWidth(1.5);
            ofDrawRectangle(this->border);
            
            ofSetColor(255, 255, 255);
            ofNoFill();
            ofSetLineWidth(1.0);
            ofDrawRectangle(this->topRightCorner);
            ofDrawRectangle(this->top);
            ofDrawRectangle(this->topLeftCorner);
            ofDrawRectangle(this->right);
            ofDrawRectangle(this->bottomRightCorner);
            ofDrawRectangle(this->bottom);
            ofDrawRectangle(this->bottomLeftCorner);
            ofDrawRectangle(this->left);
            
            break;
        }
    };
    
}


//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
void PManipulator::renderSelectionPass() {

    ofSetRectMode(OF_RECTMODE_CENTER); // center the rectangle
    ofFill();
    
    //
    // Selection pass -- draw the colors for just 1 frame --------------
    //
    ofSetColor(this->borderColor);
    ofDrawRectangle(this->border);

    ofSetColor(this->topColor);
    ofDrawRectangle(this->top);

    ofSetColor(this->rightColor);
    ofDrawRectangle(this->right);

    ofSetColor(this->bottomColor);
    ofDrawRectangle(this->bottom);

    ofSetColor(this->leftColor);
    ofDrawRectangle(this->left);

    ofSetColor(this->topRightCornerColor);
    ofDrawRectangle(this->topRightCorner);

    ofSetColor(this->topLeftCornerColor);
    ofDrawRectangle(this->topLeftCorner);

    ofSetColor(this->bottomRightCornerColor);
    ofDrawRectangle(this->bottomRightCorner);

    ofSetColor(this->bottomLeftCornerColor);
    ofDrawRectangle(this->bottomLeftCorner);

    for(int i = 0; i < 3; i++) {
        
        for(int j = 0; j < 3; j ++) {
            
            ofSetColor(this->hitboxColors[i][j]);
            ofDrawRectangle(this->hitboxes[i][j]);
        }
    }

    // --------
    
}

//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
bool PManipulator::canPictureBeSelected(float x, float y) {
    
    bool status = false;
    
    for (int i = 0; i < 3; i++) {
        
        for (int j = 0; j < 3; j++) {
            
            this->rsthb[i][j] = false; // reset the bitmap
        }
    }
    
    // ----------
    
    unsigned char pixelColorIndices[4]; // underlying pixels read into this array
    GLint viewport[4]; // generally -- [0, 0, 1024, 768]
    
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelColorIndices);
    
    ofColor selectedPixelColor = ofColor(pixelColorIndices[0], pixelColorIndices[1], pixelColorIndices[2]);
    
    // ----------
    
    for (int i = 0; i < 3;  i++) {
        
        for(int j = 0; j < 3; j++) {
            
            if ( this->hitboxColors[i][j] == selectedPixelColor ) {
        
                if ( (i == j) && (i == 1) ) {
                    
                    // translate mode
                    this->mode  = ManipulatorMode::T;
                    
                } else if ( abs(i - j) == 1 ) {
                    
                    // non-uniform scale mode
                    this->mode = ManipulatorMode::S;
                    
                } else {
                    
                    // uniform scale mode
                    this->mode = ManipulatorMode::RS;
                }
                
                status              = true;   // manipulator is active
                this->rsthb[i][j]   = true;   // select the hitbox hit
                
                break;
            }
        }
    }

    if ( !status ) {
        // for rechecking in case the click was exactly on one
        // of the 8 affordances.
    
        if ( this->topLeftCornerColor == selectedPixelColor
            || this->topRightCornerColor == selectedPixelColor
            || this->bottomLeftCornerColor == selectedPixelColor
            || this->bottomRightCornerColor == selectedPixelColor ) {
    
            this->mode = ManipulatorMode::RS;
            status = true;
    
        } else if ( this->topColor == selectedPixelColor
                   || this->bottomColor == selectedPixelColor
                   || this->leftColor == selectedPixelColor
                   || this->rightColor == selectedPixelColor ) {
    
            this->mode = ManipulatorMode::S;
            status = true;
    
        } else if ( this->borderColor == selectedPixelColor ) {
    
            this->mode = ManipulatorMode::T;
            status = true;
    
        } else {
    
            this->mode = ManipulatorMode::N;
            status = false;
        }
        
    }
    
    return status;
}

//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
Manipulator::ManipulatorMode PManipulator::getMode() {
    
    return this->mode;
}

//
// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
char PManipulator::getHitBoxIndex() {
    
    char c = 'a' - 1; // take it one below so that it can begin at 'a'
    
    for (int i = 0; i < 3; i++) {
        
        for (int j = 0; j < 3; j++) {
            
            c++; // chars are int too
            
            if(this->rsthb[i][j]) {
                
                return c;
            }
            
        }
    }
    
    return '\0'; // if none found
}

//
// --------------- --------------- --------------- --------------- -------------
//
using namespace std;
using namespace Manipulator;
ofPoint PManipulator::getBorderCorner() {
    
    return this->border.getPosition();
}

//
// --------------- --------------- --------------- --------------- -------------
//
using namespace std;
using namespace Manipulator;
void PManipulator::setRenderMat(ofMatrix4x4* m) {
    
    this->renderMat = m;
}

//
// --------------- --------------- --------------- --------------- -------------
//
using namespace std;
using namespace Manipulator;
ofVec2f PManipulator::getBorderCenter() {
    
    return this->border.getCenter();
}








