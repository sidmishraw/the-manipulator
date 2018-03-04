#include "ofApp.h"
#include <regex>
#include <string>
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    this->metaActionInProgress = false;
    ofSetBackgroundColor(0, 0, 0); // set the background to black!
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    
    ofPushMatrix();
        ofTranslate(ofGetWindowWidth() - fpsStr.size() * 10.0, ofGetWindowHeight() - 18);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(fpsStr, 0, 0);
    ofPopMatrix();
    
    ofPushMatrix();
        //        ofSetColor(255, 0, 128);
        //        ofNoFill();
        //        ofDrawCircle(this->f, 50.0);
        this->canvas.render(); // render the canvas
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) {
            
        case OF_KEY_COMMAND:
        case OF_KEY_CONTROL:{
            this->metaActionInProgress = true;
            break;
        }
    }
}

//--------------------------------------------------------------
using namespace std;
void ofApp::keyReleased(int key){
    
    switch(key) {
            
        case 'a': {
            this->canvas.selectForegroundPicture(); // testing selection of foreground picture and border
            return;
        }
            
        case 'd': {
            this->canvas.deselectForegroundPicture();
            return;
        }
            
        case 's': {
            if (!this->metaActionInProgress) return; // META ACTION NOT IN PROGRESS
            this->canvas.saveCompositionToDisk(std::string("temp-img_")); // save canvas image composition
            this->canvas.saveStateToDisk(std::string("canvas-saved-state_")); // save canvas state
        }
            
        case OF_KEY_COMMAND:
        case OF_KEY_CONTROL:{
            // Command on Mac and Ctrl on windows enable meta actions :D
            this->metaActionInProgress = false;
            return;
        }
            
        case OF_KEY_UP: {
            this->canvas.cyclePicturesUp();
            return;
        }
            
        case OF_KEY_DOWN: {
            this->canvas.cyclePicturesDown();
            return;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    this->dragInProgress = true;
    
    auto currentPoint = ofPoint(x, y);
    this->dragDelta = currentPoint - this->theDragStarterPt;
    
    this->canvas.manipulatePicture(this->dragDelta);
    
    this->theDragStarterPt = currentPoint; // updating the dragStarter point
                                           // to the current position -- for the next motion segment!
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    this->theDragStarterPt = ofPoint(x, y); // drag is starting ------+++
    
    if(!this->dragInProgress) {
        
        // initiate the colorSelection render pass
        this->canvas.beginSelectionRenderPass();
    } else {
        
        this->canvas.endSelectionRenderPass();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if(this->dragInProgress) {
        
        this->dragInProgress = false; // drag motion has ended
        
        this->canvas.endSelectionRenderPass();
        
        return;
    }
    
    this->canvas.selectPictureAt(x, y); // select the picture at the (x, y) point
    
    this->canvas.endSelectionRenderPass();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
    std::for_each(dragInfo.files.begin(),
                  dragInfo.files.end(),
                  //
                  // -----------------------------------------
                  [this, &dragInfo](std::string filePath) {
                      
                      if(filePath.length() == 0
                         || !regex_match(filePath, regex(".*\\.tmpr")))  {
                          
                           // process the dropped image file
                          this->canvas.addPicture(filePath,
                                                  dragInfo.position.x,
                                                  dragInfo.position.y);
                          
                      } else {
                          
                          // restore from the dropped saved file
                          this->canvas.loadStateFromDisk(filePath);
                          
                      }
                  }
                  // -----------------------------------------
                  //
    );
}
