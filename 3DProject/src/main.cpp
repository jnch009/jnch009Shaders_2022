#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLWindowSettings glSettings;
	glSettings.setSize(1920, 1080);
	glSettings.windowMode = OF_WINDOW;
	glSettings.setGLVersion(4, 1);
	ofCreateWindow(glSettings);
	ofSetBackgroundColor(0, 0, 0);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
