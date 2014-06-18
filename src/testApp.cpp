#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowPosition(0, 0);
	ofSetWindowTitle("Sequencer");
	ofxFensterManager::get()->setupWindow(&window);
    
    //setup the second window class
   
    
    ofBackground(255*.15);
    ofSetVerticalSync(true);
	ofEnableSmoothing();
    glEnable(GL_DEPTH_TEST);
    
    duration = 15;
    gui = new ofxUICanvas(0,(ofGetHeight()-220),(ofGetWidth()-10),60);
    gui->setFont("GUI/SourceCodePro-Bold.otf");
    tslide = gui->addBiLabelSlider("Duration", "Duration in sec", "600", 0.0, 600.0, &duration);
    vslide = gui->addBiLabelSlider("maxVolume", "VolumeTreshold", "1600", 1.0, 1600, &maxVolume);
    tslide->setColorBack(ofColor(50,0,0,20));
    tslide->setColorFill(ofColor(52,175,195,100));
    tslide->setColorFillHighlight(ofColor(52,175,195,100));
   
    vslide->setColorBack(ofColor(50,0,0,20));
    vslide->setColorFill(ofColor(52,175,195,100));
    vslide->setColorFillHighlight(ofColor(52,175,195,100));
    gui->addWidgetDown(new ofxUIMultiImageToggle(8, 8, false, "GUI/toggle.png", "Audio"));
    tlabel = tslide->getRightLabel();
    vlabel = vslide->getRightLabel();
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    ofxTimeline::removeCocoaMenusFromGlut("timeline");
    
    timeline.setup();
	timeline.setDurationInSeconds(duration);
    timeline.setLoopType(OF_LOOP_NORMAL);
    
    //cout<<val<<endl;
    timeline.addFlags("StartStop Subtimeline");
    timeline.addColors("Farben");
    timeline.setFrameBased(true);
    ofAddListener(timeline.events().bangFired, this, &testApp::bangFired);
    
    for(int i = 0; i < 2; i++){
        ofxTimeline* t = new ofxTimeline();
		t->setup();
        t->setSpacebarTogglePlay(false);
        t->setDurationInSeconds(duration);
        t->addFlags("preset Set " +ofToString(i));
        t->addCurves("preset Brightness " + ofToString(i));
        t->setWidth(ofGetWidth());
        t->setLoopType(OF_LOOP_NORMAL);
        sublines.push_back(t);
    }
    ofAddListener(sublines[0]->events().bangFired, this, &testApp::subbangFired);
    ofAddListener(sublines[1]->events().bangFired, this, &testApp::subbangFired);
    
    
    //xml Presets
    if( XML.loadFile("mySettings.xml") ){
		message = "mySettings.xml loaded!";
	}else{
		message = "unable to load mySettings.xml check data/ folder";
	}
    
    //XML.pushTag("Set");
    sets = XML.getNumTags("Set");
    //XML.popTag();
    
     //cout<<"xml presets:"<<sets<<endl;
    
    //fft auto Brightness
    fft.setup();
    fft.setNormalize(false);
    fbo.allocate(ofGetWidth(),ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0,0,0,0);
    fbo.end();
    //firstWindowFbo.allocate(800,600, GL_RGBA);
    //firstWindowFbo.begin();
    //ofClear(0,0,0,0);
    //firstWindowFbo.end();
    
 //  bool connected = tcpClient.setup("192.168.240.1", 5555);
    pyra = new ftetra(2);
    secondWindowFbo.allocate(600,600);
    secondWindowFbo.begin();
    ofClear(255,255,255, 0);
    secondWindowFbo.end();
   // ofSetFrameRate(20);
 
   
}

//--------------------------------------------------------------
void testApp::update(){
    timeline.setDurationInSeconds(duration);
    sublines[0]->setDurationInSeconds(duration);
    sublines[1]->setDurationInSeconds(duration);
    brightnessOne = sublines[0]->getValue("preset Brightness 0");
    brightnessTwo = sublines[1]->getValue("preset Brightness 1");
    
    fft.update();
    fft.setVolumeRange(maxVolume);
    maxfft = pow(3,fft.getLowVal());
	maxfft = maxfft/maxVolume*20;
    if(maxfftsend==0)
    {maxfft=1;}
    else if(maxfftsend==1)
    {maxfft=maxfft/100;
       bool range = ofInRange(maxfft,0.0,1);
       if(range==0)
       {maxfft=brightnessOne;}
        }
    
    

    c = timeline.getColor("Farben");
    red = (int)c.r * brightnessOne * maxfft;
    green = (int)c.g * brightnessOne * maxfft;
    blue = (int)c.b * brightnessOne * maxfft;
    
    //cout<<sets<<red<<"    "<<green<<"   "<<blue<<endl;
    
    vslide->setColorFill(ofColor(red,green,blue,200));
    
    fbo.begin();
    ofClear(0,0,0,0);
    fft.drawBars();
    fbo.end();
    //pyra->render(red,green,blue);
   //wenster-> colr(c);
   
    
    //cout<<"stripCode"<<"  "<< Strip<<endl;
    int nled=0;
    if(tcpClient.isConnected()) {
        string str = tcpClient.receive(); // did anything come in
    }
    
    char cmd[18];
    sprintf(cmd, "LED/%d/%d/%d/%d",0,red,green,blue);
    tcpClient.send(cmd);
    //int nled=1;
    cout<<cmd<<endl;
    if(tcpClient.isConnected()) {
        string str = tcpClient.receive(); // did anything come in
    }
    
    /*
    char cmmd[18];
    sprintf(cmmd, "LED/%d/%d/%d/%d",1,red,green,blue);
    tcpClient.send(cmmd);
    */
    secondWindowFbo.begin();
    ofClear(0);
    pyra->render(red,green,blue);
    pyra->fbo.draw(0, 0, 600, 600);
    secondWindowFbo.end();
    secondWindowFbo.draw(0,0);
    
   // beat.update(ofGetElapsedTimeMillis());

}
//--------------------------------------------------------------
void testApp::draw(){
    
  
    
    mySyphonServer.publishTexture(&secondWindowFbo.getTextureReference());
    
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 3), ofGetWidth()-50, ofGetHeight()-10);
    ofDrawBitmapString(ofToString(maxfft, 3), 0, ofGetHeight()-10);
    ofDrawBitmapString(ofToString(sets, 3), ofGetWidth()/2, ofGetHeight()-10);

    //firstWindowFbo.begin();
    //ofClear(0);
    timeline.draw();
    //firstWindowFbo.end();
    //firstWindowFbo.draw(0,0,800,60);
    
    sublines[0]->setOffset(timeline.getBottomLeft());
    
    //we need to offset all the timelines below the one above it, with a 10 pixel buffer
    for(int i = 0; i < sublines.size(); i++){
        if(i != 0){
            sublines[i]->setOffset(sublines[i-1]->getBottomLeft() + ofVec2f(0, 10));
        }
        sublines[i]->draw();
    }
   
     fbo.draw(0,ofGetHeight()-220,ofGetWidth(),200);
     //secondWindowFbo.draw(724,468,300,300);
 }

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //reset the sub timelines when you hit play
	if(key ==  ' '){
        for(int i = 0; i < sublines.size(); i++){
            sublines[i]->stop();
            sublines[i]->setCurrentTimeSeconds(0);
        }
    }
    
    /*if(key=='q'){
        fft.setVolumeRange(100);
        fft.setNormalize(false);
    }
    if(key=='r'){
        fft.setNormalize(true);
    }*/
}
//--------------------------------------------------------------
void testApp::audioReceived(float* input, int bufferSize, int nChannels) {
    beat.audioReceived(input, bufferSize, nChannels);
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();

    if(name == "Duration")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		duration = slider->getScaledValue();
        char val[5];
        sprintf(val,"%d",(int)duration);
        tlabel->setLabel(val);
	}
    else if(name == "maxVolume")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		maxVolume = slider->getScaledValue();
        char val[5];
        sprintf(val,"%d",(int)maxVolume);
        vlabel->setLabel(val);
	}
    else if(name == "Audio")
    {
        ofxUIMultiImageToggle  *ImTogg = (ofxUIMultiImageToggle *) e.widget;
        maxfftsend = ImTogg->getValue();
       
    }
}
//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
    
    
    //This is our own custom flag protocol to enslave playback
    //on the sub timelines
    //a flag that is start 3 or stop 2 will start and stop those timelines
    
	vector<string> command = ofSplitString(bang.flag, " ");
    if(command.size() == 2){
        int trackIndex = ofToInt(command[1]);
        if(trackIndex >= 0 && trackIndex < sublines.size()){
            if(command[0] == "start"){
                sublines[trackIndex]->play();
            }
            else if(command[0] == "stop"){
                sublines[trackIndex]->stop();
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::subbangFired(ofxTLBangEventArgs& bang){
    vector<string> subcommandone = ofSplitString(bang.flag," ");
    
        int subTrackIndex = ofToInt(subcommandone[0]);
    
        int numSet = XML.getNumTags("Set");
        XML.pushTag("Set", subTrackIndex);
        Strip = XML.getValue("X", "");
        XML.popTag();
      for (int i = 0; i < 23; i++){
        
        
        pyra->stripS[i] = 0;
      }
        for (int i = 0; i < 23; i++){
            Strip = Strip[i];
            bool StripS = ofToBool(Strip);
          
            cout<<StripS<<endl;
       
            pyra->stripS[i] = StripS;
        }
    
}
//--------------------------------------------------------------
void testApp::xml(){
   
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
