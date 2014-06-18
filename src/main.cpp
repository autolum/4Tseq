#include "ofMain.h"
#include "testApp.h"
#include "ofxFensterManager.h"
//#include "ofAppGlutWindow.h"
//========================================================================
int main( ){
	ofxFensterManager::setup(1024,768,OF_WINDOW);			// <-------- setup the GL context
   //ofSetupOpenGL(ofxFensterManager::get(), 1024, 768, OF_WINDOW);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
