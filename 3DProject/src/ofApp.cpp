#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	torusMesh.load("torus.ply");
	uvShader.load("passthrough.vert", "uv_vis.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;

	// Orthographic Projection start
	cam.position = vec3(0, 0, 1);
	cam.rotation = radians(100.0f);
	float aspect = 1920.0f / 1080.0f;
	mat4 model = rotate(1.0f, vec3(1, 1, 1)) * scale(vec3(0.5, 0.5, 0.5));
	mat4 view = inverse(translate(cam.position));
	mat4 proj = ortho(-aspect, aspect, -1.0f, 1.0f, 0.0f, 10.0f);
	mat4 orthoMVP = proj * view * model;
	// Orthographic Projection end

	switch (mode)
	{
		case 0:
			MVP = mat4();
			break;
		case 1:
			MVP = orthoMVP;
			break;
		default:
			MVP = mat4();
	}

	uvShader.begin();
	uvShader.setUniformMatrix4f("mvp", MVP);
	torusMesh.draw();
	uvShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ofKey::OF_KEY_SHIFT) {
		mode = (mode + 1) % 2;
	}
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
