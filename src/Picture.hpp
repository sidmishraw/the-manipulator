//
//  Picture.hpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//
#pragma once

#ifndef Picture_hpp
#define Picture_hpp

#include "ObedientObj.hpp"
#include "ofMain.h"

namespace Manipulator {
    
    using namespace std;
    class Picture :public ObedientObj{
        
        /**
         * The path of the image.
         */
        string imagePath;
        
        /**
         * The contents of the picture.
         */
        ofImage contents;
        
        /**
         * The border of the picture when it is selected.
         */
        ofRectangle border;
        
    public:
        
        /**
         * Makes a new picture with the image located at the filePath on disk.
         */
        Picture(string filePath);
        
        /**
         * Draws the picture on the canvas.
         */
        void render();
        
        /**
         * Attempts to load the image from the disk.
         */
        bool load();
        
        // checks if the point is inside the image.
        bool containsPoint(int x, int y);
        
        /**
         * Checks if the Picture is selected.
         */
        bool isSelected();
        
        /**
         * Draws the border of the picture.
         */
        void drawBorder();
        
        /**
         * Hides the border of the Picture when it is no longer selected.
         */
        void removeBorder();
        
        /**
         * Translates the Picture -- 2D.
         */
        void translate(float tx, float ty);
        
        /* -------------------------- SERIALIZATION ------------------------- */
        
        /**
         * Serializes the Picture into a string with only the features that matter.
         * imagePath, translation vector, scale vector, and rotation angle.
         */
        string toString();
        
        /**
         * Deserializes the Picture setting this picture object to its saved state.
         */
        void fromString(string contents);
        /* -------------------------- SERIALIZATION ------------------------- */
    };
    
}
#endif /* Picture_hpp */
