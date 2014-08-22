#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    osc.setup();
	ofBackground(30, 30, 130);

    
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	world.init();
	world.setGravity(0, 10);
	world.createBounds();
	world.setFPS(30.0);
	world.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update(){

    osc.update();
    world.update();

}


//--------------------------------------------------------------
void ofApp::draw(){
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].get()->draw();
	}
    
	// draw the ground
	world.drawGround();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(world.getWorld(), mouseX, mouseY, r);
		
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(world.getWorld(), mouseX, mouseY, w, h);
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
