#include "ofApp.h"
#include "functions.h"
#include "Transformation.h"
using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();

	Func.buildMesh(charMesh, 0.1, 0.2, glm::vec3(0.0, -0.25, 0.0));
	Func.buildMesh(backgroundMesh, 1, 1, glm::vec3(0.0, 0.0, -0.5));
	Func.buildMesh(cloudMesh, 0.25, 0.17, glm::vec3(0.0, 0.0, 0.0));
	Func.buildMesh(sunMesh, 1, 1, glm::vec3(0.0, 0.0, -0.4));

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
		if (charPos.x < 0.9) {
			charPos += glm::vec3(speed, 0, 0);
		}
		else {
			charPos = glm::vec3(0.9f, 0, 0);
		}
		
		// Easy way:
		charTransform = Func.buildMatrix(charPos, charRotate, charScale);
		
		// Hard way:
		/*transformation.setTranslate(charPos);
		charTransform = Func.updateTransformation(charTranslate, charRotate, charScale, transformation);*/
	}
	else if (walkLeft) {
		if (charPos.x > -0.9) {
			charPos -= glm::vec3(speed, 0, 0);
		}
		else {
			charPos = glm::vec3(-0.9f, 0, 0);
		}
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

	cam.position = vec3(0, 0, 0);
	mat4 view = Func.buildViewMatrix(cam);
	proj = glm::ortho(-1.33f, 1.33f, -1.0f, 1.0f, 0.0f, 10.0f);
	model = mat4();

	if (charPos.y >= 0.75) {
		jump = false;
	}

	if (jump) {
		charPos += glm::vec3(0, 0.02, 0);
		charTransform = Func.buildMatrix(charPos, 0.0f, glm::vec3(1, 1, 1));
	} else if (!jump && charPos.y > 0) {
		charPos -= glm::vec3(0, 0.02, 0);
		charTransform = Func.buildMatrix(charPos, 0.0f, glm::vec3(1, 1, 1));
	}

	// SpritesheetShader begins
	spritesheetShader.begin();
	spritesheetShader.setUniformMatrix4f("view", view);
	spritesheetShader.setUniform2f("size", spriteSize);
	spritesheetShader.setUniform2f("offset", spriteFrame);
	spritesheetShader.setUniformTexture("tex", alienSprite, 0);
	spritesheetShader.setUniformMatrix4f("model", charTransform);
	spritesheetShader.setUniformMatrix4f("proj", proj);
	charMesh.draw();
	spritesheetShader.end();
	// SpritesheetShader ends

	// background shader begins
	shader.begin();
	// used for the static alien image
	/*shader.setUniformTexture("tex", alienImg, 0);
	charMesh.draw();*/

	shader.setUniformTexture("tex", bgImg, 0);
	// The bg moves to the middle because it initially starts at
	// x-coordinate -1. Moving the camera by 1 means -1+1 = 0 (middle)
	// I thought for some reason it would move all the way to the right.
	shader.setUniformMatrix4f("view", view);
	shader.setUniformMatrix4f("model", model);
	shader.setUniformMatrix4f("proj", proj);
	backgroundMesh.draw();

	shader.end();
	// background shader ends

	// disable depth testing for translucent meshes
	ofDisableDepthTest();
	// Add alpha blending to make cloud translucent
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);

	// matrices
	// cloud shader begins
	cloudShader.begin();
	//cloud frag shader
	cloudShader.setUniformTexture("tex", cloudImg, 0);
	cloudShader.setUniformMatrix4f("view", view);
	cloudShader.setUniformMatrix4f("proj", proj);

	// cloud transformation matrix A
	mat4 translationA = translate(vec3(-0.55, 0, 0));
	mat4 scaleA = scale(vec3(1.5, 1, 1));
	static float rotation = 1.0f;
	rotation += 1.0f * ofGetLastFrameTime();

	mat4 transformA = translationA * scaleA;
	mat4 ourRotation = rotate(rotation, vec3(0, 0, 1.0));
	// Scale -> Translate -> -Translate -> NEW ROTATE -> Translate
	mat4 newMatrix = translationA * ourRotation * inverse(translationA);
	cloudShader.setUniformMatrix4f("model", newMatrix * transformA);
	cloudMesh.draw();

	// cloud transformation matrix B
	mat4 transformB = Func.buildMatrix(vec3(0.6, 0.6, 0), 0.5f, vec3(0.75, 1, 1));
	cloudShader.setUniformMatrix4f("model", transformB);
	cloudMesh.draw();
	cloudShader.end();

	// cloud shader ends

	// sun shader begins
	sunShader.begin();
	// Add additive blending for sun
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	
	sunShader.setUniformTexture("tex", sunImg, 0);
	sunShader.setUniformMatrix4f("model", model);
	sunShader.setUniformMatrix4f("view", view);
	sunShader.setUniformMatrix4f("proj", proj);

	sunMesh.draw();
	sunShader.end();
	// sun shader ends
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ofKey::OF_KEY_RIGHT) {
		walkRight = true;
	}

	else if (key == ofKey::OF_KEY_LEFT) {
		walkLeft = true;
	}

	else if (key == ofKey::OF_KEY_SHIFT) {
		jump = true;
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