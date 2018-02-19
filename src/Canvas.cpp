//
//  Canvas.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#include "Canvas.hpp"


bool Manipulator::Canvas::addPicture(string filePath) {
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

