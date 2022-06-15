#include "ofApp.h"
#include "utility/utilities.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING
//--------------------------------------------------------------

void ofApp::setup() {
    quad.addVertex(glm::vec3(-1, -1, 0));
    quad.addVertex(glm::vec3(-1, 1, 0));
    quad.addVertex(glm::vec3(1, 1, 0));
    quad.addVertex(glm::vec3(1, -1, 0));

    quad.addTexCoord(glm::vec2(0, 0)); // black/origin (bottom left)
    quad.addTexCoord(glm::vec2(0, 1)); // green/top left
    quad.addTexCoord(glm::vec2(1, 1)); // yellow/top right
    quad.addTexCoord(glm::vec2(1, 0)); // red/bottom right

    ofIndexType indices[6] = { 0,1,2,2,3,0 };
    quad.addIndices(indices, 6);

    // Shaders outputting a colored right triangle
    //shader.load("first_vertex.vert", "first_fragment.frag");
    
    // Fragment shader outputting UVs as Color Data
    //shader.load("uv_passthrough.vert", "uv_vis.frag");

    // Fragment shader outputting texture data
    /*shader.load("uv_passthrough.vert", "texture.frag");*/

    // Fragment shader outputting texture data, but scrolled
    shader.load("scrolling_uv.vert", "texture.frag");

    // disabling support of pixel coordinates in favor of UV coordinates
    ofDisableArbTex();
    img.load("parrot.png");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniform4f("fragCol", triangleColor);
    shader.setUniformTexture("parrotTex", img, 0);
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
