//
//  projections.h
//  scene_projections
//
//  Created by Julien Bloit on 22/08/14.
//
//

#ifndef __scene_projections__projections__
#define __scene_projections__projections__

#include <iostream>
#include "ofxBox2D.h"
#include "_projectGlobals.h"
#include "globals.h"
#include "oscManager.h"

class projections{

public:
    
    void setup();
    void update();
    void draw();
    void listen();
    
    void onVocalOnset();
    void onVocalLoudness(float& value);
    void onVocalBrightness(float& value);
    void onVocalNoisiness(float& value);
    void onVocalPitch(float& value);
    void onVocalClass(int& value);


private:
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
	vector	  <ofPtr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects
    
    void addCircle();
    void addBox();
    
    oscManager * osc; // pointer to osc the singleton class
};


#endif /* defined(__scene_projections__projections__) */
