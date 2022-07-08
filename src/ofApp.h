#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	ofMesh quad;
	ofShader shader;
	ofImage img;
	ofImage img2;
	glm::vec4 triangleColor = glm::vec4(1, 0, 0, 1);
	float brightness = 1.0f;

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
		void updateColor(glm::vec4 newColor);
		void setupMesh(ofMesh& mesh, vector<glm::vec3> vertices, vector<glm::vec2> texCoords);
		void loadShader(int shaderToLoad);
};
