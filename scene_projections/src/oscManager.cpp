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
    
    // open an outgoing connection to HOST:PORT
	sender.setup(HOST, OSC_SEND_PORT);
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
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(vocalOnset, value, this);
        }
        if(m.getAddress() == "/v/loud"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(vocalLoudness, value , this);
        }
        if(m.getAddress() == "/v/bright"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(vocalBrightness, value , this);
        }
        if(m.getAddress() == "/v/noise"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(vocalNoisiness, value , this);
        }
        if(m.getAddress() == "/v/f0"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(vocalPitch, value , this);
        }
        if(m.getAddress() == "/v/class"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(vocalClass, value , this);
        }
        
        // Check for percussion events
        if(m.getAddress() == "/p/onset"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(percussionOnset, value, this);
        }
        if(m.getAddress() == "/p/loud"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(percussionLoudness, value , this);
        }
        if(m.getAddress() == "/p/bright"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(percussionBrightness, value , this);
        }
        if(m.getAddress() == "/p/noise"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(percussionNoisiness, value , this);
        }
        if(m.getAddress() == "/p/f0"){
            float value = m.getArgAsFloat(0);
            ofNotifyEvent(percussionPitch, value , this);
        }

        // Check for piezo pickup onsets
        if(m.getAddress() == "/piezo1/onset"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(piezo1, value, this);
        }
        if(m.getAddress() == "/piezo2/onset"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(piezo2, value, this);
        }
        if(m.getAddress() == "/piezo3/onset"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(piezo3, value, this);
        }
        if(m.getAddress() == "/piezo4/onset"){
            int value = m.getArgAsInt32(0);
            ofNotifyEvent(piezo4, value, this);
        }
        
    }
    
}