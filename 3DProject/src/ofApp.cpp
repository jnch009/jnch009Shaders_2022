#include "ofApp.h"
#include "Utility.h"

//--------------------------------------------------------------
void ofApp::setup(){
	shadersToDisable.push_back(&usingDiffuse);
	shadersToDisable.push_back(&usingRim);
	shadersToDisable.push_back(&usingRimAndDir);
	shadersToDisable.push_back(&usingNormals);
	shadersToDisable.push_back(&usingSpec);

	ofDisableArbTex();
	ofEnableDepthTest();
	torusMesh.load("torus.ply");
	normalShader.load("mesh.vert", "normal_vis.frag");
	diffuseShader.load("mesh.vert", "diffuse.frag");
	uvShader.load("passthrough.vert", "uv_vis.frag");
	rimShader.load("rimLight.vert", "rimLight.frag");
	rimAndDirShader.load("rimLight.vert", "rimAndDir.frag");
	specularShader.load("rimLight.vert", "specular.frag");
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

	ofDrawBitmapStringHighlight("Left/Right arrow: change MVP matrix\nUp/Down arrow: zoom in/out\nTab: Normals\nLeft Ctrl: Diffuse\nF1: Rim\nF2: Rim+Dir", 
		vec2(0, 10), 
		ofColor::white, 
		ofColor::black);

	Utility::DirectionalLight dirLight;
	dirLight.direction = normalize(vec3(1, -1, 0));
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

	view = inverse(translate(cam.position)
		* rotate(cAngle, right));

	model = rotate(radians(90.0f), right) * 
		scale(vec3(0.5, 0.5, 0.5));
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
	else if (usingRimAndDir) {
		uniforms.mvp = MVP;
		uniforms.normal = normalMatrixDiffuse;
		uniforms.model = model;
		uniforms.meshCol = glm::vec3(1, 0, 0);
		uniforms.cameraPos = cam.position;
		uniforms.lightCol = Utility::getLightColor(dirLight);
		uniforms.lightDir = Utility::getLightDirection(dirLight);
		Utility::useRimAndDirShader(rimAndDirShader, torusMesh, uniforms);
	}
	else if (usingSpec) {
		uniforms.mvp = MVP;
		uniforms.normal = normalMatrixDiffuse;
		uniforms.model = model;
		uniforms.meshCol = glm::vec3(1, 0, 0);
		uniforms.cameraPos = cam.position;
		uniforms.lightCol = Utility::getLightColor(dirLight);
		uniforms.lightDir = Utility::getLightDirection(dirLight);

		specularShader.begin();
		specularShader.setUniformMatrix4f("mvp", uniforms.mvp);
		specularShader.setUniformMatrix3f("normal", uniforms.normal);
		specularShader.setUniformMatrix4f("model", uniforms.model);
		specularShader.setUniform3f("cameraPos", uniforms.cameraPos);
		specularShader.setUniform3f("lightDir", uniforms.lightDir);
		specularShader.setUniform3f("lightCol", uniforms.lightCol);
		specularShader.setUniform3f("meshSpecCol", glm::vec3(1,1,1));
		specularShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
		//specularShader.setUniform3f("ambientCol", glm::vec3(0.5, 0.5, 0.5));
		specularShader.setUniform3f("ambientCol", glm::vec3(0.75, 0.25, 0.25));

		// TODO: add new screen with green mesh
		// TODO: extract out this code until Utility.cpp
		// TODO: (hard) add the ability to update ambientCol values through a GUI or UI 
		// here is a resource: https://openframeworks.cc/learning/01_basics/how_to_create_slider/

		torusMesh.draw();
		specularShader.end();
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
		Utility::setShaderMode(usingNormals, shadersToDisable);
	}

	if (key == ofKey::OF_KEY_LEFT_CONTROL) {
		Utility::setShaderMode(usingDiffuse, shadersToDisable);
	}

	if (key == ofKey::OF_KEY_F1) {
		Utility::setShaderMode(usingRim, shadersToDisable);
	}

	if (key == ofKey::OF_KEY_F2) {
		Utility::setShaderMode(usingRimAndDir, shadersToDisable);
	}

	if (key == ofKey::OF_KEY_F3) {
		Utility::setShaderMode(usingSpec, shadersToDisable);
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
