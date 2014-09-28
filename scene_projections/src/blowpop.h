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
#include "Grain.h"
#include "Hull.h"
#include "Star.h"

class blowpop{
    
public:
    
    void setup();
    void update();
    void draw();
    void listen();
    void terminate();
    
    // Vocal events callbacks
    void onVocalOnset(int& value);
    void onVocalLoudness(float& value);
    void onVocalBrightness(float& value);
    void onVocalNoisiness(float& value);
    void onVocalPitch(float& value);
    void onVocalClass(int& value);
    
    // Percussion events callbacks
    void onPercussionOnset(int& value);
    void onPercussionLoudness(float& value);
    void onPercussionBrightness(float& value);
    void onPercussionNoisiness(float& value);
    void onPercussionPitch(float& value);
    
    //
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    
private:
    
    float nucleus_x;
    float nucleus_y;
    float radius;
    int numberOfNodes;
    ofxBox2dCircle nucleus;                         // center of vocal cluster
    vector <ofPtr<Grain> >	grains;                 // vocal grains
    vector <ofPtr<ofxBox2dJoint> > joints;
    ofxBox2dCircle * focus;                         // pointer to element that currently has focus
    void addGrain(int grainId);
    void playGrain(int grainId);
    
    vector <ofPtr<Star> > stars;                    // percussion stars
    
	// this is the function for contacts
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    
    void destroyJoints();
    
    bool drawSkeleton;
    
    oscManager * osc; // pointer to osc the singleton class
    
    Hull hull;
};

// ---------------------------------- Class(es) for user data attached to physical objects

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
