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
    
    //// Scene elements
    // TODO: see if we want to push that to new class
    nucleus_x = ofGetWidth()/2;
    nucleus_y = ofGetHeight()/2;
    
    nucleus.setup(ofworld.getWorld(), nucleus_x, nucleus_y, 8);
    
    focus = NULL;
    
    
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
    
    grains.clear();
    nucleus.destroy();
    
}


// ------------------------------------------------------
void blowpop::update(){
    
}

// ------------------------------------------------------
void blowpop::draw(){
    
    cout << "global value " << globals::Instance()->getValue() << " \n";
    
    nucleus.draw();
    for(int i=0; i<grains.size(); i++) {
        grains[i].get()->draw();
    }
    
}

#pragma mark callbacks

// ------------------------------------------------------
void blowpop::onVocalOnset(){
//    cout << "vocal onset event received in projections\n";

    addGrain();
//    addDot();
//    addBox();
}

// ------------------------------------------------------
void blowpop::onVocalLoudness(float& value){

    // make focus grain grow
    float growfactor = 1;
    if (focus != NULL){
        float currentRadius =  focus->getRadius();
        currentRadius += growfactor * value;
        focus->setRadius(currentRadius);
    }
    
    
}
// ------------------------------------------------------
void blowpop::onVocalBrightness(float& value){
//    cout << "vocal brightness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalNoisiness(float& value){
//    cout << "vocal noisiness event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalPitch(float& value){
//    cout << "vocal pitch event received in projections : " << value << " \n";
}
// ------------------------------------------------------
void blowpop::onVocalClass(int& value){
//    cout << "vocal class event received in projections : " << value << " \n";
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
void blowpop::addGrain(){
    float r = 1.f;
    grains.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    grains.back().get()->setPhysics(3.0, 0.53, 0.1);
    grains.back().get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, r);
    grains.back().get()->addAttractionPoint(nucleus.getPosition(), 100.f);
    
    // now connect circle to the nucleus
    ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
    joint.get()->setup(ofworld.getWorld(), nucleus.body, grains.back().get()->body);
    joint.get()->setLength(25);
    joints.push_back(joint);
    
    focus = grains.back().get();

}


