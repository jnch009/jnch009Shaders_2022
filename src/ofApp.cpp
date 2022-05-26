#include "ofApp.h"
#include "utility/utilities.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING

ofMesh triangle;
//--------------------------------------------------------------
void ofApp::setup(){
    triangle.addVertex(glm::vec3(0.0, 0.0, 0.0));
    triangle.addVertex(glm::vec3(0.0, 768.0f, 0.0));
    triangle.addVertex(glm::vec3(1024.0, 768.0, 0.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    triangle.draw();
}

// update uniform color on keypress
void ofApp::keyPressed(int key){
    ofApp::updateColor(utilities::determineColor(key));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

}
