//
//  _projectGlobals.h
//  scene_projections
//
//  Created by Julien Bloit on 21/08/14.
//
//

#ifndef scene_projections__projectGlobals_h
#define scene_projections__projectGlobals_h

#include "ofxBox2D.h"
#include "ofMain.h"
// An extern variable can be declared multiple times, (so we can include that file in many others)
// but defined once and only once (we do that in ofApp.cpp)

extern ofxBox2d ofworld;
extern ofVec2f percussionnistPosition;
extern ofVec2f vocalistPosition;
extern int maxVocalSamples;             // should be reflected in Max patch when counting onsets
extern  int maxPercussionSamples;       // should be reflected in Max patch when counting onsets
#endif
