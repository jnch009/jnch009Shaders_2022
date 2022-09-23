#pragma once

#include "ofMain.h"

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
		void buildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos);
		
		ofMesh charMesh;
		ofMesh backgroundMesh;
		ofMesh cloudMesh;
		ofMesh sunMesh;
		
		ofShader shader;
		ofShader cloudShader;
		ofShader spritesheetShader;

		ofImage alienImg;
		ofImage alienSprite;
		ofImage bgImg;
		ofImage cloudImg;
		ofImage sunImg;

		bool walkRight;
		glm::vec3 charPos;
};