//
//  oscManager.cpp
//  scene_projections
//
//  Created by Julien Bloit on 21/08/14.
//
//

#include "oscManager.h"

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
        
        // check for mouse moved message
        if(m.getAddress() == "/v/onset"){
            cout << "Received vocal onset\n";
            
            ofNotifyEvent(vocalOnset, this);
        }

        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % OSC_NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        
    }
    
}