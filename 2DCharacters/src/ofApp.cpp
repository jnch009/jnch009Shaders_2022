#include "ofApp.h"
#include "functions.h"
#include "Transformation.h"
using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();

	Func.buildMesh(charMesh, 0.1, 0.2, glm::vec3(0.0, -0.25, 0.0));
	Func.buildMesh(backgroundMesh, 1, 1, glm::vec3(0.0, 0.0, 0.5));
	Func.buildMesh(cloudMesh, 0.25, 0.17, glm::vec3(0.0, 0.0, 0.0));
	Func.buildMesh(sunMesh, 1, 1, glm::vec3(0.0, 0.0, 0.4));

	shader.load("general.vert", "alphaTest.frag");
	cloudShader.load("general.vert", "cloud.frag");
	spritesheetShader.load("spritesheet.vert", "alphaTest.frag");
	sunShader.load("general.vert", "cloud.frag");

	alienImg.load("alien.png");
	bgImg.load("forest.png");
	cloudImg.load("cloud.png");
	sunImg.load("sun.png");
	alienSprite.load("walk_sheet.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 0.4 * ofGetLastFrameTime();
	Transformation transformation;
	glm::vec3 charScale = glm::vec3(1, 1, 1);
	float charRotate = 0.0f;
	glm::vec3 charTranslate = charPos;

	if (walkRight)
	{
		charPos += glm::vec3(speed, 0, 0);
		// Easy way:
		//charTransform = Func.buildMatrix(charPos, charRotate, charScale);
		
		// Hard way:
		transformation.setTranslate(charPos);
		charTransform = Func.updateTransformation(charTranslate, charRotate, charScale, transformation);
	}
	else if (walkLeft) {
		charPos -= glm::vec3(speed, 0, 0);
		//Easy way by building an entirely new matrix:
		//charTransform = Func.buildMatrix(charPos, charRotate, charScale);
		
		//Hard way:
		transformation.setTranslate(charPos);
		charTransform = Func.updateTransformation(charTranslate, charRotate, charScale, transformation);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	static float frame = 0.0;
	frame = (frame > 10) ? 0.0 : frame += 0.3;
	glm::vec2 spriteSize = glm::vec2(0.28, 0.19);
	glm::vec2 spriteFrame = glm::vec2((int)frame % 3, (int)frame / 3);

	// Blend not needed here because fully opaque/transparent
	ofDisableBlendMode();
	// Enable depth testing for opaque mesh
	ofEnableDepthTest();

	cam.position = vec3(-1, 0, 0);
	mat4 view = Func.buildViewMatrix(cam);

	spritesheetShader.begin();
	spritesheetShader.setUniformMatrix4f("view", view);
	spritesheetShader.setUniform2f("size", spriteSize);
	spritesheetShader.setUniform2f("offset", spriteFrame);
	spritesheetShader.setUniformTexture("tex", alienSprite, 0);
	spritesheetShader.setUniformMatrix4f("model", charTransform);
	charMesh.draw();
	spritesheetShader.end();

	shader.begin();
	// used for the static alien image
	/*shader.setUniformTexture("tex", alienImg, 0);
	charMesh.draw();*/

	shader.setUniformTexture("tex", bgImg, 0);
	shader.setUniformMatrix4f("transform", mat4());
	// The bg moves to the middle because it initially starts at
	// x-coordinate -1. Moving the camera by 1 means -1+1 = 0 (middle)
	// I thought for some reason it would move all the way to the right.
	shader.setUniformMatrix4f("view", view);
	backgroundMesh.draw();

	shader.end();

	// disable depth testing for translucent meshes
	ofDisableDepthTest();
	// Add alpha blending to make cloud translucent
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);

	// matrices
	Transformation transformationA;
	vec3 translationA = vec3(-0.55, 0, 0);
	vec3 scaleA = vec3(1.5, 1, 1);
	float rotationA = 0.0f;
	transformationA.setTranslate(translationA);
	transformationA.setScale(scaleA);
	transformationA.setRotate(rotationA);

	static float rotation = 1.0f;
	rotation += 1.0f * ofGetLastFrameTime();
	transformationA.setRotate(rotation);

	mat4 transformB = Func.buildMatrix(vec3(-0.5, 0.6, 0), 0.5f, vec3(2, 1, 1));
	cloudShader.begin();
	//cloud frag shader
	cloudShader.setUniformTexture("tex", cloudImg, 0);
	cloudShader.setUniformMatrix4f("transform", mat4());
	cloudShader.setUniformMatrix4f("view", view);

	// cloud transformation matrix A
	cloudShader.setUniformMatrix4f("transform", 
		Func.updateTransformation(translationA, rotationA, scaleA, transformationA));
	cloudMesh.draw();

	// cloud transformation matrix B
	cloudShader.setUniformMatrix4f("transform", transformB);
	cloudMesh.draw();
	cloudShader.end();

	sunShader.begin();
	// Add additive blending for sun
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	sunShader.setUniformTexture("tex", sunImg, 0);
	sunShader.setUniformMatrix4f("transform", mat4());
	sunMesh.draw();
	sunShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ofKey::OF_KEY_RIGHT) {
		walkRight = true;
	}

	else if (key == ofKey::OF_KEY_LEFT) {
		walkLeft = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ofKey::OF_KEY_RIGHT) {
		walkRight = false;
	}

	else if (key == ofKey::OF_KEY_LEFT) {
		walkLeft = false;
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

//--------------------------------------------------------------