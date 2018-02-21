//
//  Picture.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Picture.hpp"

Manipulator::Picture::Picture(string filePath):Manipulator::ObedientObj() {
    this->imagePath = filePath;
    this->selected = false; // default is not selected
}

void Manipulator::Picture::render() {
    ofPushMatrix(); // backup the current coordinate system
                    //    ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0); // bring the (0,0) to the center of the viewport
    
    //#===================================================
    ofSetColor(255, 255, 255, 255); // transparent
    
    this->contents.draw(this->tMatrix.x, this->tMatrix.y); // draw asper the translation matrix
    
    this->border = ofRectangle(this->tMatrix.x, this->tMatrix.y,
                               this->contents.getWidth(),
                               this->contents.getHeight()); // the border of the Picture is a rectangle
    
    if(this->selected) {
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofSetLineWidth(3.0);
    } else {
        ofSetColor(255, 255, 255, 255);
        ofNoFill();
        ofSetLineWidth(0);
    }
    
    ofDrawRectangle(this->border);
    //#===================================================
    
    ofPopMatrix(); // restore the original coordinate system
}

bool Manipulator::Picture::load() {
    return this->contents.load(this->imagePath);
}

void Manipulator::Picture::drawBorder() {
    this->selected = true;
}

void Manipulator::Picture::removeBorder() {
    this->selected = false;
}

bool Manipulator::Picture::isSelected() { 
    return this->selected;
}

bool Manipulator::Picture::containsPoint(int x, int y) { 
    return this->border.inside(x, y);
}

void Manipulator::Picture::translate(float tx, float ty) { 
    this->tMatrix = this->tMatrix + ofVec2f(tx, ty);
}








