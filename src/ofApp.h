#pragma once

#include "ofMain.h"

#include "Canvas.hpp"

class ofApp : public ofBaseApp{
    
    /**
     * The canvas
     */
    Manipulator::Canvas canvas;
    
    /**
     * A command or control action is in progress.
     */
    bool metaActionInProgress;
    
    /**
     * A flag indicating that a mouse drag is in progress. For protection against accidental clicks :D
     */
    bool dragInProgress;
    
    /**
     * The exact point where the mouse button was pressed to start the drag.
     */
    ofPoint theDragStarterPt;
    
    //
    // The delta vector for movement.
    //
    ofVec2f dragDelta;
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
};
