//
//  Grain.h
//  shissss
//
//  Created by Julien Bloit on 24/09/14.
//
//

#ifndef __shissss__Grain__
#define __shissss__Grain__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"
#include "BaseUserData.h"

// Custom user data
class GrainData : public BaseUserData{
public:
    GrainData();
	int	 grainId;
	bool bHit;
};
inline GrainData::GrainData(){
	m_type = blowpop_grain;
}


// A Custom Particle extending the box2d circle
class Grain : public ofxBox2dCircle {
	
public:
    // Create user data with an id
	void setId(int grainId) {
        setData(new GrainData());
        GrainData * myGrainData = (GrainData*) getData();
        myGrainData->grainId = grainId;
        myGrainData->bHit = false;
	}

	void draw() {
		GrainData* theData = (GrainData*)getData();
		if(theData) {
			float radius = getRadius();
			ofPushMatrix();
			ofTranslate(getPosition());
			ofRotateZ(getRotation());
			ofSetColor(255);
			ofFill();
			ofCircle(0, 0, radius);
			ofPopMatrix();
		}
	}
};



#endif /* defined(__shissss__Grain__) */
