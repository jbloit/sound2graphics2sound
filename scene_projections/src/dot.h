//
//  dot.h
//  scene_projections
//
//  Created by Julien Bloit on 28/08/14.
//
//

#ifndef __scene_projections__dot__
#define __scene_projections__dot__

#include <iostream>
#include "ofxBox2d.h"
#include "_projectGlobals.h"

// Dot blob, with star-shaped skeleton
class dot{

public:
    void setup(float _x, float _y, float _radius);
    void update();
    void draw(bool _drawSkeleton);

    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

private:
    float nucleus_x;
    float nucleus_y;
    float radius;
    int numberOfNodes;
    ofxBox2dCircle nucleus;                         // center
    vector <ofPtr<ofxBox2dCircle> >	nodes;          // default box2d circles
	vector <ofPtr<ofxBox2dJoint> > joints;			// joints
};



#endif /* defined(__scene_projections__dot__) */
