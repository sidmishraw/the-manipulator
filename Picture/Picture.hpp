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
#include "PManipulator.hpp"

#include <memory>

namespace Manipulator {
    
    //
    // PICTURE
    // -------------
    // A picture on the Canvas. This picture is intelligent and allows itself to
    // be manipulated by the user!
    //
    using namespace std;
    using namespace Manipulator;
    class Picture : public ObedientObj {
        
        //
        // The path of the image.
        //
        string imagePath;
        
        //
        //The contents of the picture.
        //
        ofImage contents;
        
        //
        // The border of the picture when it is selected.
        // The manipulator for this picture
        //
        shared_ptr<PManipulator> manipulator;
        
        //
        // Store the rendering matrix with all its transformations in
        // order to check mouse pointer locations.
        //
        ofMatrix4x4 renderMat;
        
        //
        // Applies the transformations to the renderMat
        //
        void transform();
        
        //
        // flag signifying if the pass is for selection
        //
        bool isSelectionRenderPass;
        
    public:
        
        //
        // get isSelectionRenderPass flag
        //
        bool getIsSelectionRenderPass() {
            
            return this->isSelectionRenderPass;
        }
        
        //
        // set isSelectionRenderPass flag
        //
        void setIsSelectionRenderPass(bool f) {
            
            this->isSelectionRenderPass = f;
        }
        
        //
        // Makes a new picture with the image located at the filePath on disk.
        //
        Picture(string filePath, float tx, float ty);
        
        //
        // Draws the picture on the canvas.
        //
        void render();
        
        //
        // Attempts to load the image from the disk.
        //
        bool load();
        
        //
        // Checks if the point is inside the image.
        //
        bool containsPoint(float x, float y);
        
        //
        // Checks if the Picture is selected.
        //
        bool isSelected();
        
        //
        // Draws the border of the picture.
        //
        void drawBorder();
        
        //
        // Hides the border of the Picture when it is no longer selected.
        //
        void removeBorder();
        
        //
        // Processes the delta, manipulating itself depending on the mode of
        // the manipulator!
        //
        void processDelta(ofVec2f &delta);
        
        //
        // Resets the picture to its initial state, bringing it to its
        // initial location, scaling, and rotation.
        //
        void reset();
        
        ///-------------------------- SERIALIZATION ------------------------- //
        
        //
        // Serializes the Picture into a string with only the features that matter.
        // imagePath, translation vector, scale vector, and rotation angle.
        //
        string toString();
        
        //
        // Deserializes the Picture setting this picture object to its saved state.
        //
        void fromString(string contents);
        ///-------------------------- SERIALIZATION ------------------------- //
    };
    
    //
    // Makes a new Picture with the saved state.
    //
    using namespace std;
    shared_ptr<Manipulator::Picture> restore_picture(string savedContents);
}
#endif ///Picture_hpp //
