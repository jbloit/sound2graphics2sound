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
#define HOST "localhost"

#include <iostream>
#include "ofxOsc.h"

// Singleton class. See tutorial here http://www.yolinux.com/TUTORIALS/C++Singleton.html

class oscManager{
public:
    
    static oscManager* Instance();
    void setup();
    void update();

    // ----------- Events to dispatch to registered clients
    
    // Scene control
    ofEvent<int> blowpopToggle;
    
    // Vocal mic
    ofEvent<int> vocalOnset;
    ofEvent<float> vocalLoudness;
    ofEvent<float> vocalBrightness;
    ofEvent<float> vocalNoisiness;
    ofEvent<float> vocalPitch;
    ofEvent<int> vocalClass;
    
    // Percussion mic
    ofEvent<int> percussionOnset;
    ofEvent<float> percussionLoudness;
    ofEvent<float> percussionBrightness;
    ofEvent<float> percussionNoisiness;
    ofEvent<float> percussionPitch;
    
    
    ofEvent<int> piezo1; // onset for piezo pickup
    ofEvent<int> piezo2; // onset for piezo pickup
    ofEvent<int> piezo3; // onset for piezo pickup
    ofEvent<int> piezo4; // onset for piezo pickup
    

    // allow client objects to call the sender directly
    ofxOscSender sender;
    
private:
    
    oscManager();
    oscManager(oscManager const&){};            // copy constructor is private
    oscManager& operator=(oscManager const&){}; // assignment operator is private
    static oscManager* m_pInstance;             // the unique instance
    
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[OSC_NUM_MSG_STRINGS];
    float timers[OSC_NUM_MSG_STRINGS];
    
    
    
};

#endif /* defined(__scene_projections__oscManager__) */
