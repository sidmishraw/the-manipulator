//
//  PManipulator.hpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/27/18.
//
#pragma once

#ifndef PManipulator_hpp
#define PManipulator_hpp

#include <stdio.h>
#include <memory>

#include "ofMain.h"
#include "ObedientObj.hpp"

namespace Manipulator {
    
    // Rotate and Uniform - Scale
    // Translate
    // Non Uniform Scale
    enum ManipulatorMode {
        RS, T, S
    };
    
    
    /**
     * The picture manipulator. This will trap the incoming
     * events to the picture and manipulate them!
     */
    using namespace std;
    using namespace Manipulator;
    class PManipulator {
        
        ManipulatorMode mode;
        
        // The rectangular border that shows the space of the manipulator
        ofRectangle border;
        
        //  ------- for uniform scaling
        ofRectangle topLeftCorner;
        ofRectangle topRightCorner;
        ofRectangle bottomLeftCorner;
        ofRectangle bottomRightCorner;
        //  ------- for uniform scaling
        
        // ------- for non-uniform scaling
        ofRectangle top;
        ofRectangle left;
        ofRectangle bottom;
        ofRectangle right;
        // ------- for non-uniform scaling
        
        // -------- mode selection hit-boxes
        ofRectangle hitboxes[3][3];
        
        // Renders the manipulator itself.
        void render(bool isSelected, float w, float h);
        
    public:
        
        /* ----------------------- Selection/Deselection ------------ */
        // Tests if the point (x,y) lies within the manipulator so that it can
        // be selected.
        bool canPictureBeSelected(float x, float y);
        
        // Draws the Manipulator on the screen signalling that the
        // picture is selected.
        void show(float w, float h);
        
        // Hides the manipulator on the screen - signifies that the
        // picture is no longer selected.
        void hide(float w, float h);
        /* ----------------------- Selection/Deselection ------------ */
    };
}


#endif /* PManipulator_hpp */
