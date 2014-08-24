//
//  oscManager.h
//  scene_projections
//
//  Created by Julien Bloit on 21/08/14.
//
//

#ifndef __scene_projections__oscManager__
#define __scene_projections__oscManager__

// OSC ports
#define OSC_RECEIVE_PORT 12345
#define OSC_SEND_PORT 54321
#define OSC_NUM_MSG_STRINGS 20

#include <iostream>
#include "ofxOsc.h"

// Singleton class

class oscManager{
public:
    
    static oscManager* Instance();
    void setup();
    void update();

    // Events to dispatch to registered clients
    ofEvent<void> vocalOnset;
    ofEvent<float> vocalLoudness;
    ofEvent<float> vocalBrightness;
    ofEvent<float> vocalNoisiness;
    ofEvent<float> vocalPitch;
    ofEvent<int> vocalClass;
    
private:
    
    oscManager();
    static oscManager* m_pInstance; // the unique instance
    
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[OSC_NUM_MSG_STRINGS];
    float timers[OSC_NUM_MSG_STRINGS];
    
};

#endif /* defined(__scene_projections__oscManager__) */
