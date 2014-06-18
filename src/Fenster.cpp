//
//  fenster.cpp
//  timeline
//
//  Created by autolum on 09.04.14.
//
//

#include "Fenster.h"



void Fenster::setup(){
setWindowShape(600, 600);
setWindowPosition(310, 0);
setWindowTitle("Pyramidz");
    
    mClient.setup();
    }


void Fenster::draw(){
   
      mClient.draw(0, 0);
    
}
