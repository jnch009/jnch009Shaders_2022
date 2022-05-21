#include "ofApp.h"

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

//--------------------------------------------------------------
void setVertexPosition(int vertex, glm::vec3 curPos, glm::vec3 amount) {
    triangle.setVertex(vertex, curPos + amount);
}

void determineDirection(glm::vec3 curPos, int key, int amount, int vertexToMove) {
    /* move 20 points upwards if keypress is down arrow*/
    if (key == 57359) {
        setVertexPosition(vertexToMove, curPos, glm::vec3(0, amount, 0));
    }

    /* move 20 points downwards if keypress is up arrow*/
    if (key == 57357) {
        setVertexPosition(vertexToMove, curPos, glm::vec3(0, -amount, 0));
    }

    /* move 20 points left if keypress is left arrow*/
    if (key == 57356) {
        setVertexPosition(vertexToMove, curPos, glm::vec3(-amount, 0, 0));
    }

    /* move 20 points right if keypress is right arrow*/
    if (key == 57358) {
        setVertexPosition(vertexToMove, curPos, glm::vec3(amount, 0, 0));
    }
}

void ofApp::keyPressed(int key){
    int vertex = 1;
    int amount = 20;
    glm::vec3 curPos = triangle.getVertex(vertex);
    determineDirection(curPos, key, amount, vertex);
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
