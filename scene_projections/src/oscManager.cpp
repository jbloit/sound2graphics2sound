//
//  oscManager.cpp
//  scene_projections
//
//  Created by Julien Bloit on 21/08/14.
//
//

#include "oscManager.h"

oscManager* oscManager::m_pInstance = NULL;

oscManager* oscManager::Instance(){
    if (!m_pInstance)  // Only allow one instance of class to be generated.
        m_pInstance = new oscManager;
    return m_pInstance;
}

// --------------------------------------------------------------------------
oscManager::oscManager(){}

// --------------------------------------------------------------------------
void oscManager::setup(){
    // listen on the given port
    cout << "listening for osc messages on port " << OSC_RECEIVE_PORT << "\n";
    receiver.setup(OSC_RECEIVE_PORT);
}

// --------------------------------------------------------------------------
void oscManager::update(){
    // hide old messages
    for(int i = 0; i < OSC_NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // Check for vocal events
        if(m.getAddress() == "/v/onset"){
            ofNotifyEvent(vocalOnset, this);
        }
        if(m.getAddress() == "/v/loud"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(vocalLoudness, value , this);
        }
    }
    
}