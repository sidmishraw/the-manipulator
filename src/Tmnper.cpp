//
//  Tmnper.cpp
//  Tmnper
//
//  Created by Sidharth Mishra on 2/22/18.
//  Copyright © 2018 Sidharth Mishra. All rights reserved.
//

#include "Tmnper.hpp"

/**
 * Saves the contents into a `.tmpr` file.
 */
using namespace std;
bool Tmnper::saveIntoTmpr(string fileName, string contents) {
    
    if(fileName.length() == 0 || !regex_match(fileName, regex(".*\\.tmpr"))) return false;
    
    ofstream out;
    
    try {
        
        out.open(fileName); /* --- open the file handle --- */
        
        out << contents << endl;
        
        if(out.is_open()) out.close(); /* ---- close the file handle------- */
        
        return true;
        
    } catch(...) {
        
        cout << "Failed to write the contents to disk -- tmpr file couldn't be created." << endl;
        if(out.is_open()) out.close();
        return false;
        
    }
}

/**
 * Loads the contents from a `.tmpr` file.
 */
using namespace std;
string Tmnper::loadFromTmpr(string fileName) {
    
    if(fileName.length() == 0 || !regex_match(fileName, regex(".*\\.tmpr"))) return string("");
    
    ifstream in;
    
    try {
        
        in.open(fileName);
        
        string contents;
        
        string str; // temp
        
        while(in >> str) {
            if (str != "") contents += str + string("\n"); // append
        }
        
        if(in.is_open()) in.close();
        
        return contents;
        
    } catch(...) {
        
        if(in.is_open()) in.close();
        cout << "Couldn't load from the .tmpr file" << endl;
        return string("");
        
    }
    
}
