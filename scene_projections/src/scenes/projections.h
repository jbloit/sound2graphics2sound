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

class projections{

public:
    
    void setup();
    void update();
    void draw();
    void listen();
    void onVocalOnset();

private:
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
	vector	  <ofPtr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects
    
    void addCircle();
    void addBox();
};


#endif /* defined(__scene_projections__projections__) */
