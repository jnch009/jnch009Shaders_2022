#include "ofApp.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING
//--------------------------------------------------------------

glm::vec4 triangleColor = glm::vec4(1, 0.25, 1, 0.45);

void ofApp::setup() {
    triangle.addVertex(glm::vec3(-1.0f, 1.0f, 0.0f));
    triangle.addVertex(glm::vec3(-1.0f, -1.0f, 0.0f));
    triangle.addVertex(glm::vec3(1.0f, -1.0f, 0.0f));

    triangle.addColor(ofFloatColor(1.0f, 0.0f, 0.0f, 1.0f));
    triangle.addColor(ofFloatColor(0.0f, 1.0f, 0.0f, 1.0f));
    triangle.addColor(ofFloatColor(0.0f, 0.0f, 1.0f, 1.0f));

    shader.load("first_vertex.vert", "first_fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniform4f("fragCol", triangleColor);
    triangle.draw();
    shader.end();
}

//--------------------------------------------------------------
void determineColor(int key) {
    /* rgb(1,0,1,1) if keypress is down arrow*/
    if (key == 57359) {
        triangleColor = glm::vec4(1, 0, 1, 1);
    }

    /* rgb(1,1,1,0.25) if keypress is up arrow*/
    if (key == 57357) {
        triangleColor = glm::vec4(1, 1, 1, 0.25);
    }

    /* rgb(1,1,0,1) if keypress is left arrow*/
    if (key == 57356) {
        triangleColor = glm::vec4(1, 1, 0, 1);
    }

    /* rgb(0,1,1,0.5) if keypress is right arrow*/
    if (key == 57358) {
        triangleColor = glm::vec4(0, 1, 1, 0.5);
    }
}

// update uniform color on keypress
void ofApp::keyPressed(int key){
    determineColor(key);
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
