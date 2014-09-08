#include "ofApp.h"


// Extern variables have to be defined once and only once.
ofxBox2d ofworld;

//--------------------------------------------------------------
void ofApp::setup(){
    
    osc = oscManager::Instance(); // get pointer to osc singleton instance
    
    osc->setup();
	ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	ofworld.init();
	ofworld.setGravity(0, 10);
	ofworld.createBounds();
	ofworld.setFPS(30.0);
	ofworld.registerGrabbing();
    
    gui.setup();
    gui.add(proj_on.setup("projections", false));
    
    showMenu = true;
    
    previousProjToggle = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    osc->update();
    ofworld.update();
    
    // detect projection scene toggle-on event
    if (proj_on && !previousProjToggle) {
        proj.setup();
        previousProjToggle = true;
    }
    // detect projection scene toggle-off event
    if (!proj_on && previousProjToggle) {
        proj.terminate();
        previousProjToggle = false;
    }
    if (proj_on) proj.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    if( showMenu ){
		gui.draw();
	}
    
    if (proj_on) proj.draw();
    
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
