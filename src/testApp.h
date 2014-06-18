#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxUI.h"
#include "ofxProcessFFT.h"
#include "ofxNetwork.h"
#include "4tetra.h"
#include "Fenster.h"
#include "ofxFensterManager.h"
#include "ofxSyphon.h"
#include "ofMain.h"
#include "ofxBeat.h"
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
       // void secondFbo();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxTimeline timeline;
        void bangFired(ofxTLBangEventArgs& args);
        void subbangFired(ofxTLBangEventArgs& args);
        void guiEvent(ofxUIEventArgs &e);
        vector<ofxTimeline*> sublines;
    
        ofxUICanvas *gui;
        ofxUIBiLabelSlider *tslide;
        ofxUILabel *tlabel;
        float duration;
        ofxUIBiLabelSlider *vslide;
        ofxUILabel *vlabel;
        int maxfftsend;
        float maxVolume;
    
        ProcessFFT fft;
        float maxfft;
        ofFbo fbo;
        //float maxfftsend;
    
        ofxXmlSettings XML;
        string message;
        int sets;
        string Strip;
        void xml();
    
        ofColor c;
        int red;
        int green;
        int blue;
        float brightnessOne;
        float brightnessTwo;
    
        ofxTCPClient tcpClient;
    
        ftetra *pyra;
        //CustomWindow window;
        ofFbo secondWindowFbo;
        Fenster window;
        ofxSyphonServer mySyphonServer;
    
        ofxBeat beat;
        void audioReceived(float*, int, int);

 
    };


