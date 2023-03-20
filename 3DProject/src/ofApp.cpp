#include "ofApp.h"
#include "Utility.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	torusMesh.load("torus.ply");
	normalShader.load("mesh.vert", "normal_vis.frag");
	diffuseShader.load("mesh.vert", "diffuse.frag");
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

	Utility::DirectionalLight dirLight;
	dirLight.direction = normalize(vec3(0, -1, 0));
	dirLight.color = vec3(1, 1, 1);
	dirLight.intensity = 1.0f;

	cam.position = vec3(0, 0, 1);
	cam.rotation = radians(90.0f);
	cam.fov = radians(fov);
	float aspect = 1024.0f / 768.0f;
	//mat4 model = scale(vec3(0.5, 0.5, 0.5));
	mat4 model = rotate(1.0f, vec3(1, 1, 1)) * scale(vec3(0.5, 0.5, 0.5));
	mat4 view = inverse(translate(cam.position));
	mat4 proj = ortho(-aspect, aspect, -1.0f, 1.0f, 0.0f, 10.0f);
	mat4 perspProj = perspective(cam.fov, aspect, 0.01f, 10.0f);
	mat4 orthoMVP = proj * view * model;
	mat4 perspMVP = perspProj * view * model;
	mat3 normalMatrix = transpose(inverse(mat3(model)));

	// rotating torus and showing an overhead view
	cam.position = vec3(0, 0.75f, 1.0f);
	float cAngle = radians(-45.0f);
	vec3 right = vec3(1, 0, 0);
	view = inverse(translate(cam.position) * rotate(cAngle, right));
	model = rotate(radians(90.0f), right) * scale(vec3(0.5, 0.5, 0.5));
	mat4 normalMatrixDiffuse = transpose(inverse(mat3(model)));
	mat4 perspDiffuseMVP = perspProj * view * model;

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
		case 3:
			MVP = perspDiffuseMVP;
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
	else if (usingDiffuse) {
		diffuseShader.begin();
		diffuseShader.setUniformMatrix4f("mvp", MVP);
		if (mode == 3) {
			diffuseShader.setUniformMatrix3f("normal", normalMatrixDiffuse);
		}
		else {
			diffuseShader.setUniformMatrix3f("normal", normalMatrix);
		}
		diffuseShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
		diffuseShader.setUniform3f("lightDir", Utility::getLightDirection(dirLight));
		diffuseShader.setUniform3f("lightCol", Utility::getLightColor(dirLight));
		torusMesh.draw();
		diffuseShader.end();
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
		mode = (mode + 1) % 4;
	}

	if (key == ofKey::OF_KEY_LEFT) {
		if (mode - 1 < 0) {
			mode = 2;
		}
		else {
			mode = (mode - 1) % 4;
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

	if (key == ofKey::OF_KEY_LEFT_CONTROL) {
		if (usingDiffuse) {
			usingDiffuse = false;
		}
		else {
			usingDiffuse = true;
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
