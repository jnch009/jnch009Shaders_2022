#include "ofApp.h"
#include "utility/utilities.h"
#include "meshes/meshData.h"

//IMPORTANT: DO NOT HARDCODE ANYTHING
//--------------------------------------------------------------

//GOAL: Let's create a quadrant (DONE)

ofMesh topLeft;
ofMesh topRight;
ofMesh bottomLeft;
ofMesh bottomRight;

void ofApp::setup() {
    MeshData meshData;
    vector<glm::vec2> texCoords = meshData.texCoords;

    // Don't forget, these can be easily defined in a text file!!!
    ofApp::setupMesh(topLeft, meshData.topLeft, texCoords);
    ofApp::setupMesh(topRight, meshData.topRight, texCoords);
    ofApp::setupMesh(bottomLeft, meshData.bottomLeft, texCoords);
    ofApp::setupMesh(bottomRight, meshData.bottomRight, texCoords);
    ofApp::setupMesh(quad, meshData.quad, texCoords);

    // disabling support of pixel coordinates in favor of UV coordinates
    ofDisableArbTex();

    // disable alpha blending
    ofDisableAlphaBlending();

    img.load("parrot.png");
    img.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

    img2.load("checker.jpg");
    img2.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

    loadShader(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    /*shader.begin();
    shader.setUniform4f("fragCol", triangleColor);
    shader.setUniformTexture("parrotTex", img, 0);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("brightness", 0.5f);
    quad.draw();
    shader.end();*/

    shader.begin();
    shader.setUniformTexture("parrotTex", img, 0);
    shader.setUniformTexture("checkerboard", img2, 1);
    quad.draw();
    shader.end();

    // drawing quadrants
    //shader.begin();
    //shader.setUniform4f("fragCol", triangleColor);
    //shader.setUniformTexture("parrotTex", img, 0);
    //shader.setUniform1f("time", ofGetElapsedTimef());

    //shader.setUniform1f("brightness", 0.5f);
    ////shader.setUniform4f("uvColor", glm::vec4(-0.5, -0.5, -0.5, 1));
    //shader.setUniform4f("uvMulColor", glm::vec4(-0.5, -0.5, -0.5, 1));
    //topLeft.draw();
    //
    //shader.setUniform1f("brightness", 0.7f);
    ////shader.setUniform4f("uvColor", glm::vec4(0.25, 0.25, 1, 1));
    //shader.setUniform4f("uvMulColor", glm::vec4(0.25, 0.25, 1, 1));
    //topRight.draw();
    //
    //shader.setUniform1f("brightness", 0.2f);
    ////shader.setUniform4f("uvColor", glm::vec4(1, 0, 0, 1));
    //shader.setUniform4f("uvMulColor", glm::vec4(1, 0, 0, 1));
    //bottomLeft.draw();
    //
    //shader.setUniform1f("brightness", 3.0f);
    ////shader.setUniform4f("uvColor", glm::vec4(0.5, 0.5, 0.5, 1));
    //shader.setUniform4f("uvMulColor", glm::vec4(0.5, 0.5, 0.5, 1));
    //bottomRight.draw();
    //shader.end();
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

//--------------------------------------------------------------
void ofApp::setupMesh(ofMesh& mesh, vector<glm::vec3> vertices, vector<glm::vec2> texCoords) { 
    for (int i = 0; i < vertices.size(); i++) {
        mesh.addVertex(vertices[i]);
        mesh.addTexCoord(texCoords[i]);
    }

    // Might not always be 6
    // Keeping this static for now, but it shouldn't be
    // The index buffer will depend on what structure you want
    // The order of the vertices most likely will be defined in a text file as well
    const int indexSize = 6;
    ofIndexType indices[indexSize] = {
        0,1,2,2,3,0,
    };
    mesh.addIndices(indices, indexSize);
}

/*Shaders*/
void ofApp::loadShader(int shaderToLoad) {
    switch (shaderToLoad) {
        case 1:
            shader.load("first_vertex.vert", "first_fragment.frag");
            break;
        case 2:
            shader.load("uv_passthrough.vert", "uv_vis.frag");
            break;
        case 3:
            shader.load("uv_passthrough.vert", "texture.frag");
            break;
        case 4:
            shader.load("scrolling_uv.vert", "texture.frag");
            break;
        case 5:
            shader.load("scrolling_uv.vert", "brightness.frag");
            break;
        case 6:
            shader.load("uv_passthrough.vert", "brightness.frag");
            break;
        case 7:
            shader.load("uv_passthrough.vert", "colorUV.frag");
            break;
        default:
            shader.load("uv_passthrough.vert", "mix.frag");
    }
}
