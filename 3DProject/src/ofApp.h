#pragma once

#include "ofMain.h"
#include "Utility.h"
#include "ofxGui.h"

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

		ofxFloatSlider radius;
		ofxPanel gui;

		ofMesh torusMesh;
		ofShader uvShader;
		ofShader normalShader;
		ofShader diffuseShader;
		ofShader rimShader;
		ofShader rimAndDirShader;
		ofShader specularShader;

		Utility::CameraData cam;
		int mode = 0;
		bool usingNormals = false;
		bool usingDiffuse = false;
		bool usingRim = false;
		bool usingRimAndDir = false;
		bool usingSpec = false;
		std::vector<bool*> shadersToDisable;
		glm::mat4 MVP;
		float fov = 100.0f;
		bool increaseFov = false;
		bool decreaseFov = false;
};
