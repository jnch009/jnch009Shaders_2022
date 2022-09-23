#include "ofApp.h"
#include "functions.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();

	Func.buildMesh(charMesh, 0.1, 0.2, glm::vec3(0.0, -0.25, 0.0));
	Func.buildMesh(backgroundMesh, 1, 1, glm::vec3(0.0, 0.0, 0.5));
	Func.buildMesh(cloudMesh, 0.25, 0.17, glm::vec3(0.0, 0.0, 0.0));
	Func.buildMesh(sunMesh, 1, 1, glm::vec3(0.0, 0.0, 0.4));

	shader.load("uv_passthrough.vert", "alphaTest.frag");
	cloudShader.load("cloudVert.vert", "cloud.frag");
	spritesheetShader.load("spritesheet.vert", "alphaTest.frag");
	sunShader.load("uv_passthrough.vert", "cloud.frag");

	alienImg.load("alien.png");
	bgImg.load("forest.png");
	cloudImg.load("cloud.png");
	sunImg.load("sun.png");
	alienSprite.load("walk_sheet.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	float speed = 0.4 * ofGetLastFrameTime();
	if (walkRight)
	{
		charPos += glm::vec3(speed, 0, 0);
	}
	else if (walkLeft) {
		charPos -= glm::vec3(speed, 0, 0);
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

	spritesheetShader.begin();
	spritesheetShader.setUniform2f("size", spriteSize);
	spritesheetShader.setUniform2f("offset", spriteFrame);
	spritesheetShader.setUniformTexture("tex", alienSprite, 0);
	spritesheetShader.setUniform3f("translation", charPos);
	charMesh.draw();
	spritesheetShader.end();

	shader.begin();
	// used for the static alien image
	/*shader.setUniformTexture("tex", alienImg, 0);
	charMesh.draw();*/

	shader.setUniformTexture("tex", bgImg, 0);
	backgroundMesh.draw();

	shader.end();

	// disable depth testing for translucent meshes
	ofDisableDepthTest();
	// Add alpha blending to make cloud translucent
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);

	// matrices
	using namespace glm;
	mat4 transformA = Func.buildMatrix(vec3(-0.55, 0, 0), 0, vec3(1.5, 1, 1));
	mat4 transformB = Func.buildMatrix(vec3(0.4, 0.2, 0), 1.0f, vec3(1, 1, 1));

	cloudShader.begin();
	//cloud frag shader
	cloudShader.setUniformTexture("tex", cloudImg, 0);

	// cloud transformation matrix A
	cloudShader.setUniformMatrix4f("transform", transformA);
	cloudMesh.draw();

	// cloud transformation matrix B
	cloudShader.setUniformMatrix4f("transform", transformB);
	cloudMesh.draw();
	cloudShader.end();

	sunShader.begin();
	// Add additive blending for sun
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	cloudShader.setUniformTexture("tex", sunImg, 0);
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