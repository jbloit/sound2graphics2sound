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
    ofVec2f position;
    bool toRemove;
    float radius;
};

inline GrainData::GrainData(){
	m_type = blowpop_grain;
}

// A Custom Particle extending the box2d circle
class Grain : public ofxBox2dCircle {
	
public:
    // Create user data with an id
	void dataSetup(int grainId) {
        setData(new GrainData());
        myGrainData = (GrainData*) getData();
        myGrainData->grainId = grainId;
        myGrainData->bHit = false;
        myGrainData->position = getPosition();
        myGrainData->toRemove = false;
        myGrainData->radius = getRadius();

        changedDirection =false;
        energy = 0.f;
        isMoving = true;
        wasMoving = true;
	}
    
    void update(){

        energy = log( 1 + getVelocity().lengthSquared() );
        
        if (energy < 0.2f) isMoving = false; else isMoving = true;
        
        if (isMoving != wasMoving)
            changedDirection = true;
        else changedDirection = false;
        
        wasMoving = isMoving;
        
        
        // auto shrink and kill
        setRadius(getRadius() - 0.01);
        if (getRadius() < 1.f) myGrainData->toRemove = true;
        
        myGrainData->position = getPosition();
        myGrainData->radius = getRadius();
    }

	void draw() {
        
        float radius = getRadius();
        float alpha = MAX(100, 255 * energy);
        
        ofPushMatrix();
        ofTranslate(getPosition());
        ofRotateZ(getRotation());

        ofSetColor(alpha,255,255, alpha);   // velocity --> brightness
        ofFill();
        ofCircle(0, 0, radius);
        ofPopMatrix();
		
	}
    
    int getId(){
        if (myGrainData != NULL){
            return myGrainData->grainId;
        }
    }
    
    bool shouldRemove(){
        return myGrainData->toRemove;
    }

    bool changedDirection;
    bool isMoving;
    float energy;
    int objectId;
    
private:
    GrainData * myGrainData;  // we need this data object, because that's all we have available during a collision event.
    bool wasMoving;
};



#endif /* defined(__shissss__Grain__) */
