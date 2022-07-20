#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();

	buildMesh(charMesh, 0.1, 0.2, glm::vec3(0.0, -0.24, 0.0));
	buildMesh(backgroundMesh, 1, 1, glm::vec3(0.0, 0.0, 0.5));
	buildMesh(cloudMesh, 0.25, 0.17, glm::vec3(-0.55, 0.0, 0.0));
	buildMesh(sunMesh, 1, 1, glm::vec3(0.0, 0.0, 0.4));

	shader.load("uv_passthrough.vert", "alphaTest.frag");
	cloudShader.load("uv_passthrough.vert", "cloud.frag");

	alienImg.load("alien.png");
	bgImg.load("forest.png");
	cloudImg.load("cloud.png");
	sunImg.load("sun.png");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Blend not needed here because fully opaque/transparent
	ofDisableBlendMode();
	// Enable depth testing for opaque mesh
	ofEnableDepthTest();
	shader.begin();

	shader.setUniformTexture("tex", alienImg, 0);
	charMesh.draw();
	shader.setUniformTexture("tex", bgImg, 0);
	backgroundMesh.draw();

	shader.end();

	// disable depth testing for translucent meshes
	ofDisableDepthTest();
	// Add alpha blending to make cloud translucent
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);
	cloudShader.begin();

	cloudShader.setUniformTexture("tex", cloudImg, 0);
	cloudMesh.draw();

	// Add additive blending for sun
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	cloudShader.setUniformTexture("tex", sunImg, 0);
	sunMesh.draw();

	cloudShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::buildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos)
{
	float verts[] = { -w + pos.x, -h + pos.y, pos.z,
		-w + pos.x, h + pos.y, pos.z,
		w + pos.x, h + pos.y, pos.z,
		w + pos.x, -h + pos.y, pos.z };

	float uvs[] = { 0,0, 0,1, 1,1, 1,0 };
	for (int i = 0; i < 4; ++i) {
		int idx = i * 3;
		int uvIdx = i * 2;
		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvIdx], uvs[uvIdx + 1]));
	}

	ofIndexType indices[6] = { 0,1,2,2,3,0 };
	mesh.addIndices(indices, 6);
}