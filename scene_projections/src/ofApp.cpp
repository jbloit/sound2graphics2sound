#include "ofApp.h"


// Extern variables have to be defined once and only once.
ofxBox2d ofworld;
ofVec2f percussionnistPosition;
ofVec2f vocalistPosition;
int maxVocalSamples;
int maxPercussionSamples;

//--------------------------------------------------------------
void ofApp::setup(){
    
    osc = oscManager::Instance(); // get pointer to osc singleton instance
    
    osc->setup();
	ofBackground(0);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	ofworld.init();
	ofworld.setGravity(0, 10);
	ofworld.createBounds();
    
	ofworld.setFPS(30.0);
	ofworld.registerGrabbing();
    ofworld.enableEvents();   // <-- turn on the event listener
    
    // init gui menu
    gui.setup();
    
    gui.add(proj_on.setup("projections", false));
    previousProjToggle = proj_on;
    
    gui.add(blowpop_on.setup("blowpop", false));
    previousProjToggle = blowpop_on;
    
    gui.add(gravity.setup( "gravity", 0, 0, 20 ));
    previousGravity = gravity;
    
    showMenu = true;
    
    // init players positions
    vocalistPosition = ofVec2f(30, ofGetHeight()/2);
    percussionnistPosition = ofVec2f(3*ofGetWidth()/4, ofGetHeight()/2);
    maxVocalSamples = 100;
    maxPercussionSamples = 500;
}

//--------------------------------------------------------------
void ofApp::update(){

    osc->update();
    ofworld.update();
    
    ///// -------------------- Scene selection
    ///// ----- projection
    // detect scene toggle-on event
    if (proj_on && !previousProjToggle) {
        proj.setup();
        previousProjToggle = true;
    }
    // detect scene toggle-off event
    if (!proj_on && previousProjToggle) {
        proj.terminate();
        previousProjToggle = false;
    }
    if (proj_on) proj.update();
    
    ///// ----- blowpop
    // detect scene toggle-on event
    if (blowpop_on && !previousBlowpopToggle) {
        blowpop.setup();
        previousBlowpopToggle = true;
    }
    // detect scene toggle-off event
    if (!blowpop_on && previousBlowpopToggle) {
        blowpop.terminate();
        previousBlowpopToggle = false;
    }
    if (blowpop_on) blowpop.update();

    if (gravity != previousGravity){
        ofworld.setGravity(0, gravity);
        previousGravity = gravity;
        cout << "gravity changed to: " << gravity << "\n";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if( showMenu ){
		gui.draw();
	}
    
    // draw scenes
    if (proj_on) proj.draw();
    if (blowpop_on) blowpop.draw();
    
    
	// draw the ground
	ofworld.drawGround();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'm' ){
		showMenu = !showMenu;
	}
    if( key == 'f' ){
		ofToggleFullscreen();
	}
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
