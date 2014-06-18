//
//  4tetra.cpp
//  yunapp
//
//  Created by Jörg Plutôtes on 24/03/14.
//
//

#include "4tetra.h"

ftetra::ftetra(float _a){
    
    a = _a;
    
    for (int k = 0; k < 4; k++){
    for (int j = 0; j < 12; j++){
    for (int i = 0; i < 3; i++){
        stripV[j+k*12][i] = (tetraV[stripI[j]][i]+tetraOFF[k][i])*a;
        //cout << stripV[j][i] << "\n";
    }}}
    
    for (int k = 0; k < 4; k++){
    for (int j = 0; j < 4; j++){
        points.addVertex(ofVec3f(tetraV[k][0]+tetraOFF[j][0],
                                 tetraV[k][1]+tetraOFF[j][1],
                                 tetraV[k][2]+tetraOFF[j][2]));
    }}
    
    fbo.allocate(renderres, renderres);
    fbo.begin();
        ofClear(0,0,0,255);
    fbo.end();
    
    for (int i = 0; i < 24; i++){
        stripS[i] = 0;
    }

}

void ftetra::draw(float red, float green, float blue){
    ofSetLineWidth(8);
    ofSetColor(0,100);
    for (int i = 0; i < 24; i++){
        if (!stripS[i])
            ofLine(stripV[2*i][0], stripV[2*i][1], stripV[2*i][2],
                   stripV[2*i+1][0], stripV[2*i+1][1], stripV[2*i+1][2]);
    }
    ofSetLineWidth(6);
    ofSetColor(red,green,blue);
    for (int i = 0; i < 24; i++){
        if (stripS[i])
            ofLine(stripV[2*i][0], stripV[2*i][1], stripV[2*i][2],
                   stripV[2*i+1][0], stripV[2*i+1][1], stripV[2*i+1][2]);
    }
    //ofSetColor(255,0,0);
    //ofSetLineWidth(8);
    //glPointSize(20);
    //points.drawVertices();
}

void ftetra::render(float red, float green, float blue){
    

    ofPushStyle();
    ofEnableSmoothing();
     ofSetBackgroundColor(255,255,255);
    fbo.begin();
    
        ofClear(40, 43, 53, 255);
        ofSetupScreenOrtho(1024,1024,1024,-1024);
    ofBackground(100, 100, 100);
        ofPushMatrix();
            ofTranslate(renderres/2, renderres/2-220);
            ofScale(0.75, 0.75);
            ofRotateX(-90);
            draw(red, green, blue);
        ofPopMatrix();

        ofPushMatrix();
            ofTranslate(renderres/2-260, renderres/2+300);
            ofScale(0.4, 0.4);
            ofRotateX(15);
            //ofRotateY(ofGetElapsedTimef()*4);
            draw(red, green, blue);
        ofPopMatrix();

        ofPushMatrix();
            ofTranslate(renderres/2+260, renderres/2+300);
            ofScale(0.4, 0.4);
            ofRotateX(15);
            //ofRotateY(-ofGetElapsedTimef()*4);
            ofRotateY(180);
            draw(red, green, blue);
        ofPopMatrix();
    
    fbo.end();
    ofPopStyle();
}
