#include "ofApp.h"
#include "utility/utilities.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING
//--------------------------------------------------------------

//GOAL: Let's create a quadrant
//1. create a function that will make a quad on demand
//We need to be able to pass vertices to it
//You could turn quad into an array of ofMesh (more specifically 4)
//Then afterwards, create a class that contains an ofMesh, ofImage and brightness value

void ofApp::setup() {
    // Don't forget, these can be easily defined in a text file!!!
    //TOP LEFT
    quad.addVertex(glm::vec3(-1, 0, 0));
    quad.addVertex(glm::vec3(-1, 1, 0));
    quad.addVertex(glm::vec3(0, 1, 0));
    quad.addVertex(glm::vec3(0, 0, 0));

    //TOP RIGHT
    quad.addVertex(glm::vec3(0, 0, 0));
    quad.addVertex(glm::vec3(0, 1, 0));
    quad.addVertex(glm::vec3(1, 1, 0));
    quad.addVertex(glm::vec3(1, 0, 0));

    //BOTTOM LEFT
    quad.addVertex(glm::vec3(-1, -1, 0));
    quad.addVertex(glm::vec3(-1, 0, 0));
    quad.addVertex(glm::vec3(0, 0, 0));
    quad.addVertex(glm::vec3(0, -1, 0));

    //BOTTOM RIGHT
    quad.addVertex(glm::vec3(0, -1, 0));
    quad.addVertex(glm::vec3(0, 0, 0));
    quad.addVertex(glm::vec3(1, 0, 0));
    quad.addVertex(glm::vec3(1, -1, 0));

    for (int i = 0; i < quadrants; i++) {
        quad.addTexCoord(glm::vec2(0, 0)); // black/origin (bottom left)
        quad.addTexCoord(glm::vec2(0, 1)); // green/top left
        quad.addTexCoord(glm::vec2(1, 1)); // yellow/top right
        quad.addTexCoord(glm::vec2(1, 0)); // red/bottom right
    }

    // 4 quads * 6 edges
    ofIndexType indices[4*6] = { 
        0,1,2,2,3,0,
        4,5,6,6,7,4,
        8,9,10,10,11,8,
        12,13,14,14,15,12
    };
    quad.addIndices(indices, 4*6);

    /*Shaders*/

    // Shaders outputting a colored right triangle
    //shader.load("first_vertex.vert", "first_fragment.frag");
    
    // Fragment shader outputting UVs as Color Data
    //shader.load("uv_passthrough.vert", "uv_vis.frag");

    // Fragment shader outputting texture data
    shader.load("uv_passthrough.vert", "texture.frag");

    // Fragment shader outputting texture data, but scrolled
    //shader.load("scrolling_uv.vert", "texture.frag");

    // Fragment shader updating the brightness
    //shader.load("scrolling_uv.vert", "brightness.frag");

    // disabling support of pixel coordinates in favor of UV coordinates
    ofDisableArbTex();

    // disable alpha blending
    ofDisableAlphaBlending();

    img.load("parrot.png");
    img.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniform4f("fragCol", triangleColor);
    shader.setUniformTexture("parrotTex", img, 0);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("brightness", brightness);
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
