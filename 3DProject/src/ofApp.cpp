#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	torusMesh.load("torus.ply");
	normalShader.load("mesh.vert", "normal_vis.frag");
	uvShader.load("passthrough.vert", "uv_vis.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 50 * ofGetLastFrameTime();
	if (increaseFov) {
		if (fov > 140) {
			fov = 140;
		}
		else {
			fov = fov + speed;
		}
	}
	else if (decreaseFov) {
		if (fov < 50) {
			fov = 50;
		}
		else {
			fov = fov - speed;
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;

	cam.position = vec3(0, 0, 1);
	cam.rotation = radians(90.0f);
	cam.fov = radians(fov);
	float aspect = 1024.0f / 768.0f;
	//mat4 model = scale(vec3(0.5, 0.5, 0.5));
	mat4 model = rotate(1.0f, vec3(1, 1, 1)) * scale(vec3(0.5, 0.5, 0.5));
	mat4 view = inverse(translate(cam.position));
	mat4 proj = ortho(-aspect, aspect, -1.0f, 1.0f, 0.0f, 10.0f);
	mat4 perspProj = perspective(cam.fov, aspect, 0.25f, 10.0f);
	mat4 orthoMVP = proj * view * model;
	mat4 perspMVP = perspProj * view * model;
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	switch (mode)
	{
		case 0:
			MVP = mat4();
			break;
		case 1:
			MVP = orthoMVP;
			break;
		case 2:
			MVP = perspMVP;
			break;
		default:
			MVP = mat4();
	}

	if (usingNormals) {
		normalShader.begin();
		normalShader.setUniformMatrix4f("mvp", MVP);
		normalShader.setUniformMatrix3f("normal", normalMatrix);
		torusMesh.draw();
		normalShader.end();
	}
	else {
		uvShader.begin();
		uvShader.setUniformMatrix4f("mvp", MVP);
		torusMesh.draw();
		uvShader.end();
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ofKey::OF_KEY_RIGHT) {
		mode = (mode + 1) % 3;
	}

	if (key == ofKey::OF_KEY_LEFT) {
		if (mode - 1 < 0) {
			mode = 2;
		}
		else {
			mode = (mode - 1) % 3;
		}
	}

	if (key == ofKey::OF_KEY_UP) {
		increaseFov = true;
	}

	if (key == ofKey::OF_KEY_DOWN) {
		decreaseFov = true;
	}

	if (key == ofKey::OF_KEY_TAB) {
		if (usingNormals) {
			usingNormals = false;
		}
		else {
			usingNormals = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ofKey::OF_KEY_UP) {
		increaseFov = false;
	}

	if (key == ofKey::OF_KEY_DOWN) {
		decreaseFov = false;
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

}
