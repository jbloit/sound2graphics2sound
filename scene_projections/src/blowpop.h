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
    
    // Piezo pickup events
    void onPiezo1(int& value);
    void onPiezo2(int& value);
    void onPiezo3(int& value);
    void onPiezo4(int& value);
    
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
    ofxBox2dJoint * focusJoint;
    
    void addGrain(int grainId);
    void playGrain(int grainId, float rate=1.f, float amplitude=1.f);
    void playStar(int grainId, float rate=1.f, float amplitude=1.f);
    void starResonnator(int starId, float energy, float x, float y);
    
    void pop();                                     // POP!
    bool doPop;
    bool popped; 
    
    bool blowOut;   // if true, apply force from left to right
    
    bool drawMembrane;                              // membrane around grains
    
    vector <ofPtr<Star> > stars;                    // percussion stars
    void addStar(int starId);
    
	// this is the function for contacts
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

    
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
