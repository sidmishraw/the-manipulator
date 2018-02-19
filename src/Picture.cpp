//
//  Picture.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Picture.hpp"

Manipulator::Picture::Picture(string filePath) {
    this->imagePath = filePath;
}

void Manipulator::Picture::render() {
    
    this->contents.draw(0, 0);
    
    this->border = ofRectangle(ofGetWidth()/2.0, ofGetHeight()/2.0, this->contents.getWidth(), this->contents.getHeight());
}

bool Manipulator::Picture::isSelected() {
    return this->ObedientObj::isSelected;
}

bool Manipulator::Picture::load() {
    return this->contents.load(this->imagePath);
}


