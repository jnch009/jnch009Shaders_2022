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
	rimShader.load("rimLight.vert", "rimLight.frag");
	rimAndDirShader.load("rimLight.vert", "rimAndDir.frag");
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

	ofDrawBitmapStringHighlight("Left/Right arrow: change MVP matrix\nUp/Down arrow: zoom in/out\nTab: Normals\nLeft Ctrl: Diffuse\nF1: Rim", 
		vec2(0, 10), 
		ofColor::white, 
		ofColor::black);

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
	// transforming the model matrix to handle non-uniformly scaled objects
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

	// TODO: move this into utility?
	Utility::UniformVariableData uniforms;
	if (usingNormals) {
		uniforms.mvp = MVP;
		uniforms.normal = normalMatrix;
		Utility::useNormalShader(normalShader, torusMesh, uniforms);
	}
	else if (usingDiffuse) {
		uniforms.mvp = MVP;
		if (mode == 3) {
			uniforms.normal = normalMatrixDiffuse;
		}
		else {
			uniforms.normal = normalMatrix;
		}
		uniforms.meshCol = glm::vec3(1, 0, 0);
		uniforms.lightCol = Utility::getLightColor(dirLight);
		uniforms.lightDir = Utility::getLightDirection(dirLight);
		Utility::useDiffuseShader(diffuseShader, torusMesh, uniforms);
	}
	else if (usingRim) {
		uniforms.mvp = MVP;
		uniforms.normal = normalMatrixDiffuse;
		uniforms.model = model;
		uniforms.meshCol = glm::vec3(1, 1, 1);
		uniforms.cameraPos = cam.position;
		Utility::useRimShader(rimShader, torusMesh, uniforms);
	}
	else {
		//TODO: extract this
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
			mode = 3;
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
		Utility::setShaderMode(usingNormals);

		Utility::setShaderMode(usingRim, true);
		Utility::setShaderMode(usingDiffuse, true);
	}

	if (key == ofKey::OF_KEY_LEFT_CONTROL) {
		Utility::setShaderMode(usingDiffuse);

		Utility::setShaderMode(usingNormals, true);
		Utility::setShaderMode(usingRim, true);
	}

	if (key == ofKey::OF_KEY_F1) {
		Utility::setShaderMode(usingRim);

		Utility::setShaderMode(usingNormals, true);
		Utility::setShaderMode(usingDiffuse, true);
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
