//
//  Hull.h
//  shissss
//
//  Created by Julien Bloit on 24/09/14.
//
//

#ifndef __shissss__Hull__
#define __shissss__Hull__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"

class Hull {
public:
    vector<ofPoint> getHull(vector<ofPoint> points);
    bool isRightTurn(ofPoint a, ofPoint b, ofPoint c);
    vector<ofPoint> hull, points;
    ofPoint h1,h2,h3;
    int currentPoint,direction;
};



#endif /* defined(__shissss__Hull__) */
