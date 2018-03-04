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
#include "Tmnper.hpp"

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
        bool addPicture(std::string filePath, float tx, float ty);
        
        //
        // The selection render pass using the color selection method
        //
        void beginSelectionRenderPass();
        void endSelectionRenderPass();
        
        /**
         * Renders the canvas, drawing the pictures, one at a time in the order they were added to it.
         */
        void render();
        
        /**
         * Saves the canvas composition to disk with the provided fileName.
         */
        bool saveCompositionToDisk(std::string fileName);
        
        /**
         * Manipulates the Picture depending on the mode of its manipulator:
         * - Scales/resizes the current - selected picture or the picture on the foreground.
         * - 2D translation of the foregroundPic. Does nothing if there is no foregroundPic or no selected pic.
         * - Computes the rotation by taking into account the delta w.r.t. the center of the
         * border of the selected picture.
         */
        void manipulatePicture(ofVec2f &delta);
        
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
        
        /**
         * Deletes the selected picture from the canvas.
         */
        void deletePicture();
        
        /* ------------------------------------------------------------ */
        
        /**
         * Saves the canvas state to disk with the provided fileName.
         */
        bool saveStateToDisk(std::string fileName);
        
        /**
         * Loads the canvas state from the disk.
         */
        void loadStateFromDisk(std::string fileName);
        
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
