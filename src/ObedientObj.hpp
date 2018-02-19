//
//  ObedientObj.hpp
//  the-manipulator
//
//  Created by Sidharth Mishra on 2/18/18.
//
#pragma once

#ifndef ObedientObj_hpp
#define ObedientObj_hpp

#include "ofMain.h"

namespace Manipulator {
    
    /**
     * The ever so manipulatable object. Manipulate it like some sick
     * overlord (^v^)__;
     */
    class ObedientObj {
        
    protected:
        
        /**
         *  2D translation matrix.
         */
        ofVec2f tMatrix;
        
        /**
         * 2D scaling matrix.
         */
        ofVec2f sMatrix;
        
        /**
         * 2D rotation angle.
         */
        float theta;
        
        /**
         * flag true when the object is selected.
         */
        bool isSelected;
    };
    
}

#endif /* ObedientObj_hpp */

