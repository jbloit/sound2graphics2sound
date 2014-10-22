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
#include "_projectGlobals.h"

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
        cout << "created axle\n";
        // add an anchor on the circle

    }
    
    // override setup to add an anchor and a joint
    void setup(b2World * b2dworld, float x, float y, float radius){
        ofxBox2dCircle::setup(b2dworld, x, y, radius);
        anchor.setPhysics(10, 0.001, 100);
        anchor.setup(ofworld.getWorld(), getPosition().x + getRadius(), getPosition().y, 50.f);
        joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
        joint->setup(ofworld.getWorld(), this->body, anchor.body, 0.8, 0.9, true);
        joint->setLength(150);
        
    }
    void setup(b2World * b2dworld, ofVec2f &pts, float radius) {
        setup(b2dworld, pts.x, pts.y, radius);
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
//        cout << "joint reaction force : " << joint->getReactionForce(0.1) << "\n";
        
    }
    
    void draw(){
        
        float radius = getRadius();
        float alpha = MAX(100, 255 * energy);
        
        ofPushMatrix();
            ofTranslate(getPosition());
            ofRotateZ(getRotation());
            ofSetColor(alpha,255,255, alpha);   // velocity --> brightness
            ofFill();
            ofCircle(0, 0, radius);
            ofSetColor(0);
            ofLine(0, 0, 0, radius);
        ofPopMatrix();
        
        ofSetColor(255,0,0);
        anchor.draw();
        ofSetColor(255);
        joint->draw();
        
    }
 
    
    int getId(){
        return myData->elementId;
    }
    
    ofxBox2dCircle anchor;
    bool isMoving;
    float energy;
    
private:

    ofPtr<ofxBox2dJoint> joint;
    AxleData * myData;  // we need this data object, because that's all we have available during a collision event.
    bool wasMoving;
};


#endif /* defined(__shissss__Axle__) */
