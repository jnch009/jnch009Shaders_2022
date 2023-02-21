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

		struct CameraData {
			glm::vec3 position;
			float rotation;
			float fov;
		};

		ofMesh torusMesh;
		ofShader uvShader;
		ofShader normalShader;
		CameraData cam;
		int mode = 0;
		bool usingNormals = false;
		glm::mat4 MVP;
		float fov = 90.0f;
		bool increaseFov = false;
		bool decreaseFov = false;
};
