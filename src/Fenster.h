//
//  Fenster.h
//  timeline
//
//  Created by autolum on 09.04.14.
//
//
#ifndef timeline_Fenster_h
#define timeline_Fenster_h
#include "ofxFensterManager.h"
#include "ofxSyphon.h"

class Fenster : public ofxFenster{
public:
	void setup();
    //void update();
    void draw();
   
    ofxSyphonClient mClient;

   // int green;
   // int blue;
    //secondFbo *test;
};
#endif
