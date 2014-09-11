//
//  projections.cpp
//  scene_projections
//
//  Created by Julien Bloit on 22/08/14.
//
//

#include "projections.h"

using namespace std;


void projections::setup(){
    
    osc = oscManager::Instance();
    
    // Register event listeners
    ofAddListener(osc->vocalOnset, this, &projections::onVocalOnset);
    ofAddListener(osc->vocalLoudness, this, &projections::onVocalLoudness);
    ofAddListener(osc->vocalBrightness, this, &projections::onVocalBrightness);
    ofAddListener(osc->vocalNoisiness, this, &projections::onVocalNoisiness);
    
    ofRegisterKeyEvents(this);
    
    drawSkeleton = false;
    
}

// ------------------------------------------------------
// End scene and deallocate objects if needed. This is not a destructor, we want to
// be able to call it even when the object is not destroyed.
void projections::terminate(){
    
    ofUnregisterKeyEvents(this);
    ofRemoveListener(osc->vocalOnset, this, &projections::onVocalOnset);
    ofRemoveListener(osc->vocalLoudness, this, &projections::onVocalLoudness);
    ofRemoveListener(osc->vocalBrightness, this, &projections::onVocalBrightness);
    ofRemoveListener(osc->vocalNoisiness, this, &projections::onVocalNoisiness);
    
    circles.clear();
    boxes.clear();
    dots.clear();
}


// ------------------------------------------------------
void projections::update(){
    for(int i=0; i<dots.size(); i++) {
		dots[i].get()->update();
	}
}

// ------------------------------------------------------
void projections::draw(){
    
//    cout << "global value " << globals::Instance()->getValue() << " \n";
    
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
void projections::onVocalOnset(int& value){
    cout << "vocal onset event received in projections id : " << value << "\n";
    addDot();
    addBox();
}
// ------------------------------------------------------
void projections::onVocalLoudness(float& value){
    cout << "vocal loudness event received in projections : " << value << " \n";
    
    

}
// ------------------------------------------------------
void projections::onVocalBrightness(float& value){
    cout << "vocal brightness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void projections::onVocalNoisiness(float& value){
    cout << "vocal noisiness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void projections::onVocalPitch(float& value){
    cout << "vocal pitch event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void projections::onVocalClass(int& value){
    cout << "vocal class event received in projections : " << value << " \n";
}

// ------------------------------------------------------
void projections::keyPressed(ofKeyEventArgs& args){
	if( args.key == 'o' ){
        int val = 0;
		onVocalOnset(val);
	}
    
    if( args.key == 's' ){
		drawSkeleton = !drawSkeleton;
	}
    
    if( args.key == ' ' ){
		drawSkeleton = !drawSkeleton;
	}
    
}
void projections::keyReleased(ofKeyEventArgs& args){

}


# pragma mark private
// ------------------------------------------------------
void projections::addCircle(){
    float r = ofRandom(4, 20);
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, r);
}
// ------------------------------------------------------
void projections::addBox(){
    float w = ofRandom(4, 20);
    float h = ofRandom(4, 20);
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    boxes.back().get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, w, h);
}

// ------------------------------------------------------
void projections::addDot(){
    float x = ofGetWidth()/4;
    float y = ofGetHeight()/2;
    float radius = ofRandom(30, 200);
    dots.push_back(ofPtr<dot>(new dot));
    dots.back().get()->setup(x, y, radius);
}


