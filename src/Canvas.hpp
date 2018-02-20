//
//  Canvas.hpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <vector>
#include "Picture.hpp"

namespace Manipulator {
    
    /**
     * The canvas where the pictures are drawn.
     */
    class Canvas {
        
        /**
         * All the pictures added to the canvas.
         */
        std::vector<Picture> pictures;
        
    public:
        
        /**
         * Adds the picture at the filePath to the canvas, if not added returns false.
         */
        bool addPicture(std::string filePath);
        
        /**
         * Renders the canvas, drawing the pictures, one at a time in the order they were added to it.
         */
        void render();
        
        /**
         * Saves the canvas composition to disk with the provided fileName.
         */
        bool saveToDisk(std::string fileName);
    };
}

#endif /* Canvas_hpp */
