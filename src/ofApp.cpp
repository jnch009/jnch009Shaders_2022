#include "ofApp.h"
#include "utility/utilities.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING
//--------------------------------------------------------------

void ofApp::setup() {
    quad.addVertex(glm::vec3(-1, -1, 0));
    quad.addVertex(glm::vec3(-1, 1, 0));
    quad.addVertex(glm::vec3(1, 1, 0));
    quad.addVertex(glm::vec3(1, -1, 0));

    quad.addColor(ofDefaultColorType(1, 0, 0, 1)); //red
    quad.addColor(ofDefaultColorType(0, 1, 0, 1)); //green
    quad.addColor(ofDefaultColorType(0, 0, 1, 1)); //blue
    quad.addColor(ofDefaultColorType(1, 1, 1, 1)); //white

    ofIndexType indices[6] = { 0,1,2,2,3,0 };
    quad.addIndices(indices, 6);

    shader.load("first_vertex.vert", "first_fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniform4f("fragCol", triangleColor);
    quad.draw();
    shader.end();
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

//--------------------------------------------------------------
void ofApp::updateColor(glm::vec4 color) {
    triangleColor = color;
}
