//
//  Canvas.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Canvas.hpp"
#include "ofMain.h"


bool Manipulator::Canvas::addPicture(std::string filePath) {
    auto pic = Picture(filePath);
    if(pic.load()) {
        this->pictures.push_back(pic);
        return true;
    }
    return false;
}


void Manipulator::Canvas::render() {
    std::for_each(this->pictures.begin(),this->pictures.end(),
                  [this](Picture pic) {
                      pic.render();
                  });
}

bool Manipulator::Canvas::saveToDisk(std::string fileName) {
    try {
        ofSaveScreen(fileName + ".png");
        return true;
    } catch(...) {
        return false;
    }
}


