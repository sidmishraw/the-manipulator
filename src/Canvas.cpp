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
#include <memory>
#include <sstream>


Manipulator::Canvas::Canvas() {
    this->currentDepth = 1; // start the depth at 0 and it is always going to decrease
    this->selectionDepth = 1; // start the depth at 0 and it is always going to decrease
}

bool Manipulator::Canvas::addPicture(std::string filePath) {
    //# ================================================
    
    auto pic = std::make_shared<Manipulator::Picture>(filePath); // the shared pointer for ARC -- :D
    
    //# ================================================
    if(pic->load()) {
        this->currentDepth --;
        this->pictures[this->currentDepth] = pic;
        return true;
    }
    //# ================================================
    
    return false;
}

void Manipulator::Canvas::render() {
    std::for_each(this->pictures.rbegin(),
                  this->pictures.rend(),
                  [this](std::pair<int, std::shared_ptr<Manipulator::Picture>> entry) {
                      entry.second->render(); // render the pictures one at a time, overlaying as they were added
                  });
}

bool Manipulator::Canvas::saveCompositionToDisk(std::string fileName) {
    try {
        auto currTime = std::time(nullptr);
        fileName = std::regex_replace(
                                      fileName.append(std::asctime(std::localtime(&currTime))),
                                      std::regex("\\s"),
                                      "_");
        ofSaveScreen(fileName + ".png");
        return true;
    } catch(...) {
        return false;
    }
}

void Manipulator::Canvas::scalePicture(float sx, float sy) {
    return;
}

void Manipulator::Canvas::selectForegroundPicture() {
    this->foregroundPic = this->pictures[this->currentDepth];
    this->foregroundPic->drawBorder();
}

void Manipulator::Canvas::deselectForegroundPicture() {
    this->foregroundPic = this->pictures[this->currentDepth];
    this->foregroundPic->removeBorder();
}

void Manipulator::Canvas::selectPictureAt(int x, int y) {
    try {
        
        //# =======================================================
        this->selectionDepth = 1; // reset the selectionDepth with every click!
                                  // the selectionDepth will always be the minimum value -- least since it is -ve
                                  // for eg: -2 > -1 > 0
        if(this->foregroundPic.get() != nullptr) {
            this->foregroundPic.reset(); // reset the foregroundPic
        }
        //# =======================================================
        
        //# ================================== Selection =========================
        std::for_each(this->pictures.rbegin(), // since the comparator is by default less<int> = (l,r)-> l < r
                      this->pictures.rend(),
                      [this, x, y](std::pair<int, std::shared_ptr<Manipulator::Picture>> entry) {
                          auto pic = entry.second; // the pic
                          if(pic->containsPoint(x, y)) {
                              
                              //# ==================================
                              if(pic->isSelected()) {
                                  pic->removeBorder(); // deselect hte picture
                                  this->foregroundPic.reset(); // reset the shared pointer so that it points to no picture
                                  this->selectionDepth = 1; // reset the selection depth
                                  return;
                              }
                              //# ==================================
                              
                              //# =========================================
                              if(entry.first < this->selectionDepth) {
                                  // if the picture is over another image
                                  // then select the image with smaller z-index -- topmost image
                                  this->foregroundPic = pic;
                                  this->selectionDepth = entry.first; // update the selectionDepth
                              }
                              //# =========================================
                          } else {
                              pic->removeBorder(); // if the selection click was not for this Picture
                                                   // it should not be selected by mistake!
                          }
                      });
        //# ================================== Selection =========================
        
        //# ============================================================================
        
        if (this->foregroundPic.get() != nullptr) this->foregroundPic->drawBorder(); // draw the border of the foremost picture only~
        
        ///# ============================================================================
    } catch(...) {
        std::cout << "OOPS! Couldn't select the picture at x =" << x << ", y = " << y << std::endl;
    }
}

void Manipulator::Canvas::cyclePicturesUp() {
    if(this->foregroundPic.get() != nullptr) {
        if((this->selectionDepth - 1) < this->currentDepth) return; // already at top, can't move it any-more
        auto temp = this->pictures[this->selectionDepth - 1]; // swap with the picture just above it
        this->pictures[this->selectionDepth - 1] = this->foregroundPic;
        this->pictures[this->selectionDepth] = temp;
        this->selectionDepth = this->selectionDepth - 1;
    }
}

void Manipulator::Canvas::cyclePicturesDown() {
    if(this->foregroundPic.get() != nullptr) {
        if((this->selectionDepth + 1) > 0) return; // already at bottom, can't move it any-more
        auto temp = this->pictures[this->selectionDepth + 1];
        this->pictures[this->selectionDepth + 1] = this->foregroundPic;
        this->pictures[this->selectionDepth] = temp;
        this->selectionDepth = this->selectionDepth + 1;
    }
}

void Manipulator::Canvas::translatePicture(float tx, float ty) { 
    if(this->foregroundPic.get() == nullptr) return; // no picture has been selected, so cannot translate :D
    this->foregroundPic->translate(tx, ty); // translate the picture -- delegated to the foreground picture!
}

/* ------------------------------------------------------------ */
using namespace std;
string Manipulator::Canvas::toString() {
    string contents;
    
    /* ------------------------------- */
    for_each(this->pictures.rbegin(),
             this->pictures.rend(),
             [this, &contents](std::pair<int, std::shared_ptr<Manipulator::Picture>> entry) {
                 contents += string("###\n") + entry.second->toString();
             });
    /* ------------------------------- */
    
    return contents;
}

using namespace std;
void Manipulator::Canvas::fromString(string contents) {
    
    /* ------ reset the currentDepth and selectionDepth ------- */
    this->currentDepth = 1;
    this->selectionDepth = 1;
    /* ------ reset the currentDepth and selectionDepth ------- */
    
    /* ------ clear the pictures map ------- */
    this->pictures.clear();
    /* ------ clear the pictures map ------- */
    
    istringstream cstream(contents); // the contents stream
    
    string tmp; // for reading into
    string savedContents; // string buffer
    
    shared_ptr<Manipulator::Picture> tmpPicture; // pointer to a temporary picture being created
    
    /* --------------------------sstream reader------------------------------------- */
    while(cstream >> tmp) {
        /*--------------------------------------------------------------------*/
        if(tmp == "###") {
            /* --------- saved contents ----------------- */
            if(savedContents != "") {
                
                this->currentDepth --;
                this->pictures[this->currentDepth] = Manipulator::restore_picture(savedContents);
                savedContents = string(""); // reset the saved contents since it is the
                                            // beginning of a new picture's saved data
            }
            /* --------- saved contents ----------------- */
        } else {
            savedContents += tmp + string("\n"); // restoring the \n that is eaten by the stream
        }
        /*--------------------------------------------------------------------*/
    }
    if(savedContents != "") {
        // last remaining picture
        this->currentDepth --;
        this->pictures[this->currentDepth] = Manipulator::restore_picture(savedContents);
        savedContents = string(""); // reset the saved contents since it is the
                                    // beginning of a new picture's saved data
    }
    /* ---------------------------------sstream reader----------------------------- */
    
}

bool Manipulator::Canvas::saveStateToDisk(std::string fileName) {
    try {
        auto currTime = std::time(nullptr);
        fileName = std::regex_replace(
                                      fileName.append(std::asctime(std::localtime(&currTime))),
                                      std::regex("\\s"),
                                      "_");
        Tmnper::saveIntoTmpr(fileName + ".tmpr", this->toString()); // save state to disk
        return true;
    } catch(...) {
        return false;
    }
}

void Manipulator::Canvas::loadStateFromDisk(std::string fileName) {
    this->fromString(Tmnper::loadFromTmpr(fileName));
}


/* ------------------------------------------------------------ */









