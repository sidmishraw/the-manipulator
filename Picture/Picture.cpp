//
//  Picture.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Picture.hpp"
#include <sstream>

// ----------------------------------------------------------------------------
//
using namespace std;
using namespace Manipulator;
Manipulator::Picture::Picture(string filePath, float tx, float ty) : Manipulator::ObedientObj() {
    
    this->imagePath = filePath;
    this->selected  = false;
    
    this->tMatrix.set(tx, ty);
    this->sMatrix.set(1, 1);
    this->theta = 0.0;
    
    this->manipulator = make_shared<PManipulator>();
    
}

// ----------------------------------------------------------------------------
//
void Manipulator::Picture::render() {
    
    ofPushMatrix();
    
    ofSetColor(255, 255, 255, 255);
    
    ofTranslate(this->tMatrix.x, this->tMatrix.y);
    ofRotate(this->theta);
    ofScale(this->sMatrix.x, this->sMatrix.y);
    
    this->contents.draw(0,0);
    
    if(this->selected) {
        
        this->manipulator->show(this->contents.getWidth(),
                                this->contents.getHeight());
    } else {
        
        this->manipulator->hide(this->contents.getWidth(),
                                this->contents.getHeight());
    }
    
    ofPopMatrix();
    
}

// ----------------------------------------------------------------------------
//
bool Manipulator::Picture::load() {
    return this->contents.load(this->imagePath);
}

// ----------------------------------------------------------------------------
//
void Manipulator::Picture::drawBorder() {
    this->selected = true;
}

// ----------------------------------------------------------------------------
//
void Manipulator::Picture::removeBorder() {
    this->selected = false;
}

// ----------------------------------------------------------------------------
//
bool Manipulator::Picture::isSelected() { 
    return this->selected;
}

// ----------------------------------------------------------------------------
//
using namespace std;
bool Manipulator::Picture::containsPoint(int x, int y) {
    
    bool status = false;

    ofPushMatrix();
    
    ofTranslate(this->tMatrix.x, this->tMatrix.y);
    ofRotate(this->theta);
    ofScale(this->sMatrix.x, this->sMatrix.y);
    
    status = this->manipulator->canPictureBeSelected(x - this->tMatrix.x,
                                                     y - this->tMatrix.y );
    
    ofPopMatrix();
    
    return status;
    
}

// ----------------------------------------------------------------------------
//
void Manipulator::Picture::translate(float tx, float ty) { 
    this->tMatrix = this->tMatrix + ofVec2f(tx, ty);
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






