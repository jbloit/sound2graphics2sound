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

    void update();
    void draw();
    void listen();
    
// this should be private once we have callback system in place
    void addCircle();
    void addBox();

private:
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
	vector	  <ofPtr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects
};


#endif /* defined(__scene_projections__projections__) */
