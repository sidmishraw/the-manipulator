//
//  Canvas.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Canvas.hpp"
#include "ofMain.h"
#include <string>
#include <regex>


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
        auto currTime = std::time(nullptr);
        fileName = std::regex_replace(fileName.append(std::asctime(std::localtime(&currTime))), std::regex("\\s"), "_");
        ofSaveScreen(fileName + ".png");
        return true;
    } catch(...) {
        return false;
    }
}


