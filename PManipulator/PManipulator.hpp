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
    
    // Self Note -----
    // Moving to the color-selection method -- intersection method is too clumsy.
    //
    
    /**
     * The picture manipulator. This will trap the incoming
     * events to the picture and manipulate them!
     */
    using namespace std;
    using namespace Manipulator;
    class PManipulator {
        
        //
        // Each manipulator has a unique render generated number -- fills the `R` field.
        //
        static unsigned char RENDER_GEN;
        
        //
        // The base color generated for this manipulator.
        //
        unsigned char baseR;
        
        // The mode in which the manipulator was selected.
        // The drag operations behave as per the mode the manipulator
        // is in. Similarly, the affordances change color depending on the
        // mode the manipulator is in.
        ManipulatorMode mode;
        
        //
        // Origin ? or the top left corner
        //
        ofPoint lc;
        
        //
        // Vector holding width and height
        //
        ofPoint rc;
        
        // ----- deprecated -- don't use ----
        // Render matrix to hold all the transformations
        //
        ofMatrix4x4* renderMat;
        
        //
        // The rectangular border that shows the space of the manipulator.
        //
        ofColor borderColor;
        ofRectangle border;
        
        //
        //  ------- for uniform scaling
        //
        ofColor topLeftCornerColor;
        ofRectangle topLeftCorner;
        
        ofColor topRightCornerColor;
        ofRectangle topRightCorner;
        
        ofColor bottomLeftCornerColor;
        ofRectangle bottomLeftCorner;
        
        ofColor bottomRightCornerColor;
        ofRectangle bottomRightCorner;
        //
        //  ------- for uniform scaling
        //
        
        //
        // ------- for non-uniform scaling
        //
        ofColor topColor;
        ofRectangle top;
        
        ofColor leftColor;
        ofRectangle left;
        
        ofColor bottomColor;
        ofRectangle bottom;
        
        ofColor rightColor;
        ofRectangle right;
        //
        // ------- for non-uniform scaling
        //
        
        //
        // -------- mode selection hit-boxes
        // There are 9 hitboxes.
        //
        // The hitboxes [0][0], [0][2], [2][0], and [2][2] change the mode to
        // Rotate+Uniform Scale or (RS).
        //
        // The hitboxes [0][1], [1][0], [1][2], and [2][1] change the mode to
        // Non-uniform scale or (S).
        //
        // The hitbox [1][1] changes the mode to Translate or (T).
        ofColor hitboxColors[3][3];
        ofRectangle hitboxes[3][3];
        
        //
        // --------- rst-hitboxes (rotate, scale, translate)
        // This bitmap shows how the negative and postive deltas behaves when
        // uniform scaling or rotating, or translating, or non-uniform scaling.
        //
        // a/00 - top left    , b/01 - top          , c/02 - top right
        // d/10 - left        , e/11 - translate    , f/12 - right
        // g/20 - bottom left , h/21 - bottom       , i/22 - bottom right
        bool rsthb[3][3];
        
        //
        // Renders the manipulator itself.
        //
        void render(bool isSelected, float w, float h);
        
        // ----- Monkey patching! -------
        // Constructs the components of the manipulator -- borders, etc
        //
        void constructComponents();
        
    public:
        
        //
        // Creates the manipulator -- sticks to the picture like a shadow!
        // p -- initial x coord
        // q -- initial y coord
        // w -- width
        // h -- height
        PManipulator(float p, float q, float w, float h);
        
        //
        // for debugging
        //
        ofPoint getBorderCorner();
        
        //
        // For rotation -- computing the angle with respect to the center of
        // this manipulator.
        //
        ofVec2f getBorderCenter();
        
        //
        // Render the color selection mask for manipulator selection.
        //
        void renderSelectionPass();
        
        //------- deprecated -- don't use
        // Sets the render matrix for this manipulator
        //
        void setRenderMat(ofMatrix4x4* m);
        
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
        
        //
        // Gets the mode that the manipulator is currently in.
        //
        ManipulatorMode getMode();
        
        //
        // Gets the rst-hitboxes index that lighted up with a hit.
        // returns the '\0' char if none found!
        //
        char getHitBoxIndex();
    };
}


#endif /* PManipulator_hpp */
