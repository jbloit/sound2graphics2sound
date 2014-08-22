#include "ofApp.h"


ofxBox2d ofworld; // an extern variable has to be defined once and only once.

//--------------------------------------------------------------
void ofApp::setup(){

    osc.setup();
	ofBackground(30, 30, 130);

    
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	ofworld.init();
	ofworld.setGravity(0, 10);
	ofworld.createBounds();
	ofworld.setFPS(30.0);
	ofworld.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update(){

    osc.update();
    ofworld.update();
    proj.update();
}


//--------------------------------------------------------------
void ofApp::draw(){

    proj.draw();
    
	// draw the ground
	ofworld.drawGround();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'c') {
        proj.addCircle();
		
	}
	
	if(key == 'b') {
        proj.addBox();
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
