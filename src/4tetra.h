//
//  4tetra.h
//  yunapp
//
//  Created by Jörg Plutôtes on 24/03/14.
//
//

#ifndef _4_TETRA
#define _4_TETRA

#include "ofMain.h"


class ftetra {
    
public:
    
    // edge length
    float a;
    
    // tetrahedron vertices
    //float tetraV[4][3] = {{0,-100,71},{0,100,71},{100,0,-71},{-100,0,-71}};
    //float tetraV[4][3] = {{0,71,-100},{0,71,100},{100,-71,0},{-100,-71,0}};
    float tetraV[4][3] = {{0,-153,0},{0,51,144},{-125,51,-72},{125,51,-72}};
    
    // tetrahedorn offsets
    //float tetraOFF[4][3] = {{0,0,0},{0,200,0},{100,100,-142},{-100,100,-142}};
    //float tetraOFF[4][3] = {{0,0,0},{0,0,200},{100,-142,100},{-100,-142,100}};
    //float tetraOFF[4][3] = {{0,0,0},{0,204,144},{-125,204,-72},{125,204,-72}};
    float tetraOFF[4][3] = {{0,-102,0},{0,102,144},{-125,102,-72},{125,102,-72}};
    
    // 4 tetras strip vertices
    float stripV[48][3];
    
    // strip indices
    int stripI[12] = {0,1,0,2,0,3,1,2,2,3,3,1};
    
    // strip switches
    bool stripS[24];
    
    // constructor
    ftetra(float _a);
    
    // functions
    void render(float red, float green, float blue);
    void draw(float red, float green, float blue);
    
    // FBO for rendering
    ofFbo fbo;
    int renderres = 1024;
    
    ofMesh points;
    ofEasyCam cam;
};

#endif