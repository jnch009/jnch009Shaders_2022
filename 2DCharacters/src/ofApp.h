#pragma once

#include "ofMain.h"
#include "functions.h"
#include "structs.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		functions Func;

		ofMesh charMesh;
		ofMesh backgroundMesh;
		ofMesh cloudMesh;
		ofMesh sunMesh;
		
		ofShader shader;
		ofShader cloudShader;
		ofShader spritesheetShader;
		ofShader sunShader;

		ofImage alienImg;
		ofImage alienSprite;
		ofImage bgImg;
		ofImage cloudImg;
		ofImage sunImg;

		bool walkRight;
		bool walkLeft;
		glm::vec3 charPos;
		glm::mat4 charTransform;

		CameraData cam;

		glm::mat4 proj;
		glm::mat4 model;
};