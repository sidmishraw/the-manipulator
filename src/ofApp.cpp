#include "ofApp.h"

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
    this->canvas.render(); // render the canvas
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
void ofApp::keyReleased(int key){
    
    switch(key) {
            
        case 's': {
            if (!this->metaActionInProgress) return; // META ACTION NOT IN PROGRESS
            this->canvas.saveToDisk(std::string("temp-img_"));
        }
            
        case OF_KEY_COMMAND:
        case OF_KEY_CONTROL:{
            // Command on Mac and Ctrl on windows enable meta actions :D
            this->metaActionInProgress = false;
            return;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
    std::for_each(dragInfo.files.begin(),
                  dragInfo.files.end(),
                  [this](std::string filePath){
                      this->canvas.addPicture(filePath);
                  });
}
