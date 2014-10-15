//
//  Axle.h
//  shissss
//
//  Created by julien@macmini on 10/15/14.
//
//

#ifndef __shissss__Axle__
#define __shissss__Axle__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"
#include "BaseUserData.h"

// Custom user data
class AxleData : public BaseUserData{
public:
    AxleData();
	int	 elementId;
	bool bHit;
    float energy;
};
inline AxleData::AxleData(){
	m_type = axle;
}

// A Custom Particle extending the box2d circle
class Axle : public ofxBox2dCircle {
	
public:
    Axle(){
        cout << "Axle constructor\n";

    }
    // Create user data with an id
	void dataSetup(int elementId) {
        setData(new AxleData());
        myData = (AxleData*) getData();
        myData->elementId = elementId;

        energy = 0.f;
        isMoving = true;
        wasMoving = true;
        
	}
    
    void update(){
        
        energy = log( 1 + getVelocity().lengthSquared() );
        if (energy < 0.2f) isMoving = false; else isMoving = true;
        wasMoving = isMoving;
        myData->energy = energy;
        
    }
    
//    void draw(){
//        float radius = getRadius();
//        float alpha = MAX(100, 255 * energy);
//        
//        ofPushMatrix();
//        ofTranslate(getPosition());
//        ofRotateZ(getRotation());
//        
//        if (hasFocus) ofSetColor(alpha, 0,0);
//        else ofSetColor(alpha,255,255, alpha);   // velocity --> brightness
//        ofFill();
//        ofCircle(0, 0, radius);
//        ofPopMatrix();
//    }
 
    
    int getId(){
        return myData->elementId;
    }
    
    bool isMoving;
    float energy;
    
private:
    AxleData * myData;  // we need this data object, because that's all we have available during a collision event.
    bool wasMoving;
};


#endif /* defined(__shissss__Axle__) */
