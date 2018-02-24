//
//  Canvas.hpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <memory>
#include <map>
#include "Picture.hpp"

namespace Manipulator {
    
    /**
     * The canvas where the pictures are drawn.
     */
    using namespace std;
    class Canvas {
        
        /**
         * All the pictures added to the canvas.
         * I feel that having a map with Z-Index makes it easier for me to implement
         * the selected image movement thingy!
         */
        std::map<int,std::shared_ptr<Manipulator::Picture>> pictures;
        
        // denotes the z-depth?
        int currentDepth;
        
        // pointer to the foreground picture.
        std::shared_ptr<Manipulator::Picture> foregroundPic;
        
        // the depth of the selected picture
        int selectionDepth;
        
    public:
        
        /**
         * Initializes the canvas with initial properties.
         */
        Canvas();
        
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
        
        /**
         * Scales/resizes the current - selected picture or the picture on the foreground.
         */
        void scalePicture(float sx, float sy);
        
        /**
         * 2D translation of the foregroundPic. Does nothing if there is no foregroundPic or no selected pic.
         */
        void translatePicture(float tx, float ty);
        
        /**
         * Selects the picture on the foreground.
         */
        void selectForegroundPicture();
        
        /**
         * De-Selects the picture on the foreground.
         */
        void deselectForegroundPicture();
        
        /**
         * Selects the picture at the specified (x,y) co-ordinate if possible.
         */
        void selectPictureAt(int x, int y);
        
        /**
         * Moves the selected image up in the z. (-ve)
         */
        void cyclePicturesUp();
        
        /**
         * Moves the selected image down in the z. (+ve)
         */
        void cyclePicturesDown();
        
        /* ------------------------------------------------------------ */
        
        /**
         * Serializes the contents of the Canvas into a string to be saved onto disk.
         */
        string toString();
        
        /**
         * De-serializes the contents of the string restoring the canvas.
         */
        void fromString(string contents);
        /* ------------------------------------------------------------ */
    };
}

#endif /* Canvas_hpp */
