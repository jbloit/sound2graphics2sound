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
    Star(){
        cout << "star constructor\n";
        setPhysics(1.5f, 0.7, 1.5);
        float radius = 20.f;
        addTriangle(ofVec2f(radius ,0), ofVec2f(radius * cos(2*PI/3.f),radius*sin(2*PI/3.f)), ofVec2f(radius * cos(4*PI/3.f),radius*sin(4*PI/3.f)));
        
//        addTriangle(ofVec2f(ofRandom(223, 33),200), ofVec2f(44,65), ofVec2f(23,78));
    }
    // Create user data with an id
	void dataSetup(int starId) {
        setData(new StarData());
        StarData * myStarData = (StarData*) getData();
        myStarData->starId = starId;
        myStarData->bHit = false;
	}
    
    void update(){
        
    }
    
    void draw(){
    	if(body == NULL) {
            ofLog(OF_LOG_ERROR, "ofxBox2dPolygon::draw body null\n");
            return;
        }
        ofPushMatrix();
        ofTranslate(getPosition());
        ofRotate(getRotation(), 0, 0, 1);
        ofFill();
        ofSetColor(255,255,255);
        mesh.draw(ofGetFill()==OF_OUTLINE?OF_MESH_WIREFRAME:OF_MESH_FILL);
        ofPopMatrix();
    }
};


#endif /* defined(__shissss__Star__) */
