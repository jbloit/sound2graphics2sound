//
//  blowPop.h
//  shissss
//
//  Created by Julien Bloit on 09/09/14.
//
//

#ifndef __shissss__blowPop__
#define __shissss__blowPop__

#include <iostream>

#include <iostream>
#include "ofxBox2D.h"
#include "_projectGlobals.h"
#include "globals.h"
#include "oscManager.h"
#include "dot.h"
#include "BaseUserData.h"

class blowpop{
    
public:
    
    void setup();
    void update();
    void draw();
    void listen();
    void terminate();
    
    void onVocalOnset(int& value);
    void onVocalLoudness(float& value);
    void onVocalBrightness(float& value);
    void onVocalNoisiness(float& value);
    void onVocalPitch(float& value);
    void onVocalClass(int& value);
    
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    
private:
    
    float nucleus_x;
    float nucleus_y;
    float radius;
    int numberOfNodes;
    ofxBox2dCircle nucleus;                         // center of vocal cluster
    vector <ofPtr<ofxBox2dCircle> >	grains;         // default box2d circles
    vector <ofPtr<ofxBox2dJoint> > joints;
    ofxBox2dCircle * focus;                    // pointer to element that currently has focus
    
    void addGrain(int grainId);
    void playGrain(int grainId);
    
	// this is the function for contacts
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    
    void destroyJoints();
    
    bool drawSkeleton;
    
    oscManager * osc; // pointer to osc the singleton class
};

// ---------------------------------- Class(es) for user data attached to physical objects
class GrainData : public BaseUserData{
public:
    GrainData();
	int	 grainId;
	bool bHit;
};
inline GrainData::GrainData(){
	m_type = blowpop_grain;
}

class NucleusData : public BaseUserData{
public:
    NucleusData();
	int	 nucleusId;
	bool bHit;
};
inline NucleusData::NucleusData(){
	m_type = blowpop_nucleus;
}

#endif /* defined(__shissss__blowPop__) */
