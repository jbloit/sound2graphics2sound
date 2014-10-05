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
    bool gravitate; // should the star gravitate around nucleus
};
inline StarData::StarData(){
	m_type = blowpop_star;
}

// A Custom Particle extending the box2d circle
class Star : public ofxBox2dPolygon {
	
public:
    Star(){
        cout << "star constructor\n";
        setPhysics(1.5f, 0.7, 1.5);
        float radius = 20.f;
        addTriangle(ofVec2f(radius ,0), ofVec2f(radius * cos(2*PI/3.f),radius*sin(2*PI/3.f)), ofVec2f(radius * cos(4*PI/3.f),radius*sin(4*PI/3.f)));

    }
    // Create user data with an id
	void dataSetup(int starId) {
        setData(new StarData());
        myStarData = (StarData*) getData();
        myStarData->starId = starId;
        myStarData->bHit = false;
        myStarData->gravitate = true;
        
        energy = 0.f;
        isMoving = true;
        wasMoving = true;
        
	}
    
    void update(){
        
        energy = log( 1 + getVelocity().lengthSquared() );
        if (energy < 0.2f) isMoving = false; else isMoving = true;
        wasMoving = isMoving;
        
    }

    void draw(){
    	if(body == NULL) {
            ofLog(OF_LOG_ERROR, "ofxBox2dPolygon::draw body null\n");
            return;
        }
        
        float alpha = MAX(30, 50 * energy);
        alpha = MIN(255, alpha);
        ofPushMatrix();
        ofTranslate(getPosition());
        ofRotate(getRotation(), 0, 0, 1);
        ofFill();
        ofSetColor(alpha);
        mesh.draw(ofGetFill()==OF_OUTLINE?OF_MESH_WIREFRAME:OF_MESH_FILL);
        ofPopMatrix();
    }
    
    bool doGravitate(){
        return myStarData->gravitate;
    }
    
    void setGravitate(bool state){
        myStarData->gravitate = state;
    }
    
    bool isMoving;
    float energy;
    
private:
    StarData * myStarData;  // we need this data object, because that's all we have available during a collision event.
    bool wasMoving;
};


#endif /* defined(__shissss__Star__) */
