//
//  Tmnper.hpp
//  Tmnper
//
//  Created by Sidharth Mishra on 2/22/18.
//  Copyright © 2018 Sidharth Mishra. All rights reserved.
//

#pragma once /* ---- include this header file only once ---- */

#ifndef Tmnper_hpp
#define Tmnper_hpp


#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <regex>
#include <memory>

namespace Tmnper {
    
    /**
     * Saves the contents into a `.tmpr` file.
     */
    using namespace std;
    bool saveIntoTmpr(string fileName, string contents);
    
    /**
     * Loads the contents from a `.tmpr` file.
     */
    using namespace std;
    string loadFromTmpr(string fileName);
}



#endif /* Tmnper_hpp */
