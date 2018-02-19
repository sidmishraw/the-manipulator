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
   * The commands for Canvas.
   */
  enum Command {
    CYCLE_IMG_UP,
    CYCLE_IMG_DOWN
  };
  
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
    bool addPicture(string filePath);
    
    /**
     * Renders the canvas, drawing the pictures, one at a time in the order they were added to it.
     */
    void render();
    
    /**
     * Processes the command, effectively making Canvas the command processor.
     */
    bool commandProcessor(Command command);
  };
}

#endif /* Canvas_hpp */
