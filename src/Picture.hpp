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
    
    class Picture :protected ObedientObj{
        
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
         * True if the picture was selected, else false.
         */
        bool isSelected();
        
        /**
         * Attempts to load the image from the disk.
         */
        bool load();
    };
    
}
#endif /* Picture_hpp */
