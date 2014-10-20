//
//  wheeler.h
//  shissss
//
//  Created by julien@macmini on 10/15/14.
//
//

#ifndef __shissss__wheeler__
#define __shissss__wheeler__

#include <iostream>
#include "ofxBox2D.h"
#include "_projectGlobals.h"
#include "globals.h"
#include "oscManager.h"
#include "BaseUserData.h"
#include "Grain.h"
#include "Star.h"
#include "Axle.h"

class wheeler{
    
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
    
    // Piezo pickup callbacks
    void onPiezo1(int& value);
    void onPiezo2(int& value);
    void onPiezo3(int& value);
    void onPiezo4(int& value);
    
    // keyboard callbacks
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    

    
private:
    // utils
    oscManager * osc; // pointer to osc the singleton class
    
    // sound control
    void playGrain(int grainId, float amplitude=1.f);
    void grainDrone(int starId, float energy, float x, float y);
    void playStar(int grainId, float rate=1.f, float amplitude=1.f);
    void starDrone(int starId, float energy, float x, float y);
    
    // scene elements
    ofPtr<Axle> axle;
    vector <ofPtr<Grain> >	grains;
    vector <ofPtr<Star> > stars;
    
    // scene behavior
    void addGrain(int grainId);
    void addStar(int starId);
    void removeRandomStar();
    bool drawSkeleton;
    
    // collision callbacks
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

};

#endif /* defined(__shissss__wheeler__) */
