//
//  blowpop.cpp
//  shissss
//
//  Created by Julien Bloit on 09/09/14.
//
//

#include "blowpop.h"


using namespace std;

void blowpop::setup(){
    
    osc = oscManager::Instance();
    
    // Register event listeners
    ofAddListener(osc->vocalOnset, this, &blowpop::onVocalOnset);
    ofAddListener(osc->vocalLoudness, this, &blowpop::onVocalLoudness);
    ofAddListener(osc->vocalBrightness, this, &blowpop::onVocalBrightness);
    ofAddListener(osc->vocalNoisiness, this, &blowpop::onVocalNoisiness);
    
    ofRegisterKeyEvents(this);
    
    drawSkeleton = false;
    
}

// ------------------------------------------------------
// End scene and deallocate objects if needed. This is not a destructor, we want to
// be able to call it even when the object is not destroyed.
void blowpop::terminate(){
    
    ofUnregisterKeyEvents(this);
    ofRemoveListener(osc->vocalOnset, this, &blowpop::onVocalOnset);
    ofRemoveListener(osc->vocalLoudness, this, &blowpop::onVocalLoudness);
    ofRemoveListener(osc->vocalBrightness, this, &blowpop::onVocalBrightness);
    ofRemoveListener(osc->vocalNoisiness, this, &blowpop::onVocalNoisiness);
    
    circles.clear();
    boxes.clear();
    dots.clear();
}


// ------------------------------------------------------
void blowpop::update(){
    for(int i=0; i<dots.size(); i++) {
		dots[i].get()->update();
	}
}

// ------------------------------------------------------
void blowpop::draw(){
    
    cout << "global value " << globals::Instance()->getValue() << " \n";
    
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
    
    for(int i=0; i<dots.size(); i++) {
		dots[i].get()->draw(drawSkeleton);
	}
}

#pragma mark callbacks

// ------------------------------------------------------
void blowpop::onVocalOnset(){
    cout << "vocal onset event received in projections\n";
    addDot();
    addBox();
}
// ------------------------------------------------------
void blowpop::onVocalLoudness(float& value){
    cout << "vocal loudness event received in projections : " << value << " \n";
    
    
    
}
// ------------------------------------------------------
void blowpop::onVocalBrightness(float& value){
    cout << "vocal brightness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalNoisiness(float& value){
    cout << "vocal noisiness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalPitch(float& value){
    cout << "vocal pitch event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalClass(int& value){
    cout << "vocal class event received in projections : " << value << " \n";
}

// ------------------------------------------------------
void blowpop::keyPressed(ofKeyEventArgs& args){
	if( args.key == 'o' ){
		onVocalOnset();
	}
    
    if( args.key == 's' ){
		drawSkeleton = !drawSkeleton;
	}
    
    if( args.key == ' ' ){
		drawSkeleton = !drawSkeleton;
	}
    
}
void blowpop::keyReleased(ofKeyEventArgs& args){
    
}


# pragma mark private
// ------------------------------------------------------
void blowpop::addCircle(){
    float r = ofRandom(4, 20);
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, r);
}
// ------------------------------------------------------
void blowpop::addBox(){
    float w = ofRandom(4, 20);
    float h = ofRandom(4, 20);
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    boxes.back().get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, w, h);
}

// ------------------------------------------------------
void blowpop::addDot(){
    float x = ofGetWidth()/4;
    float y = ofGetHeight()/2;
    float radius = ofRandom(30, 200);
    dots.push_back(ofPtr<dot>(new dot));
    dots.back().get()->setup(x, y, radius);
}


