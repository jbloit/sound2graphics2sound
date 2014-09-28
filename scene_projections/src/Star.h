//
//  Star.h
//  shissss
//
//  Created by Julien Bloit on 25/09/14.
//
//

#ifndef __shissss__Star__
#define __shissss__Star__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"
#include "BaseUserData.h"

// Custom user data
class StarData : public BaseUserData{
public:
    StarData();
	int	 starId;
	bool bHit;
};
inline StarData::StarData(){
	m_type = blowpop_star;
}

// A Custom Particle extending the box2d circle
class Star : public ofxBox2dPolygon {
	
public:
    // Create user data with an id
	void setId(int starId) {
        setData(new StarData());
        StarData * myStarData = (StarData*) getData();
        myStarData->starId = starId;
        myStarData->bHit = false;
	}
    
//	void draw() {
//		StarData* theData = (GraStarDatainData*)getData();
//		if(theData) {
//			float radius = getRadius();
//			ofPushMatrix();
//			ofTranslate(getPosition());
//			ofRotateZ(getRotation());
//			ofSetColor(255);
//			ofFill();
//			ofCircle(0, 0, radius);
//			ofPopMatrix();
//		}
//	}
};


#endif /* defined(__shissss__Star__) */
