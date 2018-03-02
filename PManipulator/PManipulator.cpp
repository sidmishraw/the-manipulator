//
//  PManipulator.cpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/27/18.
//

#include "PManipulator.hpp"

#include <memory>
#include <iostream>

// ----------------------------------------------------------------------------
//
using namespace Manipulator;
void PManipulator::show(float w, float h) {
    this->render(true, w, h);
}

// ----------------------------------------------------------------------------
//
using namespace Manipulator;
void PManipulator::hide(float w, float h) {
    this->render(false, w, h);
}

// ----------------------------------------------------------------------------
//
using namespace Manipulator;
using namespace std;
void PManipulator::render(bool isSelected, float w, float h) {
    
    this->border = ofRectangle(0, 0, w, h);
    
    int rw = 5; // affordance width
    int rh = 5; // affordance height
    
    this->topLeftCorner     = ofRectangle(0 - (rw / 2.0)        , 0 - (rh / 2.0)        , rw, rh);
    this->topRightCorner    = ofRectangle(0 + w - (rw / 2.0)    , 0 - (rh / 2.0)        , rw, rh);
    this->bottomLeftCorner  = ofRectangle(0 - (rw / 2.0)        , 0 + h - (rh / 2.0)    , rw, rh);
    this->bottomRightCorner = ofRectangle(0 + w - (rw / 2.0)    , 0 + h - (rh / 2.0)    , rw, rh);
    
    this->top       = ofRectangle(0 + (w / 2.0) - (rw / 2.0)    , 0 - (rh / 2.0)                , rw, rh);
    this->left      = ofRectangle(0 - (rw / 2.0)                , 0 + (h / 2.0) - (rh / 2.0)    , rw, rh);
    this->bottom    = ofRectangle(0 + (w / 2.0) - (rw / 2.0)    , 0 + h - (rh / 2.0)            , rw, rh);
    this->right     = ofRectangle(0 + w - (rw / 2.0)            , 0  + (h / 2.0) - (rh / 2.0)   , rw, rh);
    
    float hbw = w / 3.0; // hitbox width
    float hbh = h / 3.0; // hitbox height
    
    // for T mode
    this->hitboxes[1][1] = ofRectangle((w / 8.0)        , (h / 8.0)         , (w / 4.0)     , (h / 4.0));
    
    // for RS mode
    this->hitboxes[0][0] = ofRectangle(0 * (hbw / 2.0)  , 0 * (hbh / 2.0)   , (hbw / 2.0)   , (hbh / 2.0));
    this->hitboxes[2][2] = ofRectangle(5 * (hbw / 2.0)  , 5 * (hbh / 2.0)   , (hbw / 2.0)   , (hbh / 2.0));
    this->hitboxes[0][2] = ofRectangle(0 * (hbw / 2.0)  , 5 * (hbh / 2.0)   , (hbw / 2.0)   , (hbh / 2.0));
    this->hitboxes[2][0] = ofRectangle(5 * (hbw / 2.0)  , 0 * (hbh / 2.0)   , (hbw / 2.0)   , (hbh / 2.0));
    
    // for S mode
    this->hitboxes[0][1] = ofRectangle(hbw              , 0                 , hbw           , (hbh / 2.0));
    this->hitboxes[1][0] = ofRectangle(0                , hbh               , (hbw / 2.0)   , hbh        );
    this->hitboxes[2][1] = ofRectangle(hbw              , 5 * (hbh / 2.0)   , hbw           , (hbh / 2.0));
    this->hitboxes[1][2] = ofRectangle(5 * (hbw / 2.0)  , hbh               , (hbw / 2.0)   , hbh        );
    
    if(!isSelected) {
        return;
    }
    
    cout << "Mode = " << this -> mode << endl;
    
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
    };
}

// ----------------------------------------------------------------------------
//
using namespace std;
bool PManipulator::canPictureBeSelected(float x, float y) {
    
    bool status = false;
    
    for (int i = 0; i < 3;  i++) {
        
        for(int j = 0; j < 3; j++) {
            
            if(this->hitboxes[i][j].inside(x, y)) {
        
                if ((i == j) && (i == 1)) {
                    
                    // translate mode
                    this->mode  = ManipulatorMode::T;
                    
                } else if (abs(i - j) == 1) {
                    
                    // non-uniform scale mode
                    this->mode = ManipulatorMode::S;
                    
                } else {
                    
                    // uniform scale mode
                    this->mode = ManipulatorMode::RS;
                }
                
                status      = true;
            }
        }
    }

    if (!status) {
    
        if (this->topLeftCorner.inside(x, y)
            || this->topRightCorner.inside(x, y)
            || this->bottomLeftCorner.inside(x, y)
            || this->bottomRightCorner.inside(x, y)) {
    
            this->mode = ManipulatorMode::RS;
            status = true;
    
        } else if (this->top.inside(x, y)
                   || this->bottom.inside(x, y)
                   || this->left.inside(x, y)
                   || this->right.inside(x, y)) {
    
            this->mode = ManipulatorMode::S;
            status = true;
    
        } else if ( this->border.inside(x, y)) {
    
            this->mode = ManipulatorMode::T;
            status = true;
    
        } else {
    
            status = false;
        }
        
    }
    
    return status;
}


