//
//  blowpop.cpp
//  shissss
//
//  Created by Julien Bloit on 09/09/14.
//
//

#include "blowpop.h"
#include <typeinfo>  //for 'typeid'

using namespace std;

void blowpop::setup(){
    
    osc = oscManager::Instance();
    
    // notify Max of scene start
    ofxOscMessage m;
    m.setAddress("/blowpop/on");
    m.addIntArg(1);
    osc->sender.sendMessage(m);
    
    // Register event listeners
    ofAddListener(osc->vocalOnset, this, &blowpop::onVocalOnset);
    ofAddListener(osc->vocalLoudness, this, &blowpop::onVocalLoudness);
    ofAddListener(osc->vocalBrightness, this, &blowpop::onVocalBrightness);
    ofAddListener(osc->vocalNoisiness, this, &blowpop::onVocalNoisiness);
    ofRegisterKeyEvents(this);
	ofAddListener(ofworld.contactStartEvents, this, &blowpop::contactStart);
	ofAddListener(ofworld.contactEndEvents, this, &blowpop::contactEnd);
    
    drawSkeleton = false;
    
    //// Scene elements
    // TODO: see if we want to push that to new class
    nucleus_x = ofGetWidth()/2;
    nucleus_y = ofGetHeight()/2;
    nucleus.setup(ofworld.getWorld(), nucleus_x, nucleus_y, 8);
    
    // add custom data
    nucleus.setData(new NucleusData());
    NucleusData * myNucleusData = (NucleusData*) nucleus.getData();
    myNucleusData->bHit = false;
    
    
    
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
    ofRemoveListener(ofworld.contactStartEvents, this, &blowpop::contactStart);
	ofRemoveListener(ofworld.contactEndEvents, this, &blowpop::contactEnd);
    grains.clear();
    joints.clear();
    nucleus.destroy();
    
    // notify Max of scene end
    ofxOscMessage m;
    m.setAddress("/blowpop/on");
    m.addIntArg(0);
    osc->sender.sendMessage(m);
    
}


// ------------------------------------------------------
void blowpop::update(){
    
}

// ------------------------------------------------------
void blowpop::draw(){
    
//    cout << "global value " << globals::Instance()->getValue() << " \n";
    
    nucleus.draw();
    for(int i=0; i<grains.size(); i++) {
        grains[i].get()->draw();
    }
    
}

#pragma mark callbacks

// ------------------------------------------------------
void blowpop::onVocalOnset(int& value){
    cout << "BLOWPOP - VOCAL ONSET, id: " << value << " \n";

    addGrain(value);
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
        int val = 0;
		onVocalOnset(val);
	}
    
    if( args.key == 's' ){
		drawSkeleton = !drawSkeleton;
	}
    
    if( args.key == ' ' ){
        destroyJoints();
    }
    
}
void blowpop::keyReleased(ofKeyEventArgs& args){
    
}


//--------------------------------------------------------------
void blowpop::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
		
        // Determine which elements collided
        BaseUserData *dataA = (BaseUserData*) e.a->GetBody()->GetUserData();
        BaseUserData *dataB = (BaseUserData*) e.b->GetBody()->GetUserData();
        
        if (dataA && dataB){
            // grain-grain collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::blowpop_grain){
                cout << "*--* grain-grain collision " << endl;
            }
            // grain-bounds collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::bounds){
                cout << "*--_ grain-bounds collision " << endl;
                GrainData * myGrain = (GrainData*) dataA;
                playGrain(myGrain->grainId);
            }
            // bounds-grain collision
            if (dataA->getType() == BaseUserData::bounds && dataB->getType() == BaseUserData::blowpop_grain){
                cout << "_--* bounds-grain collision " << endl;
                GrainData * myGrain = (GrainData*) dataB;
                playGrain(myGrain->grainId);
            }
            // nucleus-grain collision
            if (dataA->getType() == BaseUserData::blowpop_nucleus && dataB->getType() == BaseUserData::blowpop_grain){
                cout << ".--* nucleus-grain collision " << endl;
//                destroyJoints();
            }
        }
	}
}

//--------------------------------------------------------------
void blowpop::contactEnd(ofxBox2dContactArgs &e) {
//	if(e.a != NULL && e.b != NULL) {
//		
//		SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//		SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//		
//		if(aData) {
//			aData->bHit = false;
//		}
//		
//		if(bData) {
//			bData->bHit = false;
//		}
//	}
}


# pragma mark private
// ------------------------------------------------------
// Trigger the grain's sound
void blowpop::playGrain(int grainId){
    // play grain
    ofxOscMessage m;
    m.setAddress("/blowpop/play");
    m.addIntArg(grainId);
    osc->sender.sendMessage(m);
}
// ------------------------------------------------------
void blowpop::addGrain(int grainId){
    
    // Create grain
    float r = 1.f;
    ofPtr<Grain> grain = ofPtr<Grain>(new Grain);
    grain.get()->setPhysics(3.0, 0.53, 0.1);
    grain.get()->setup(ofworld.getWorld(), ofGetWidth()/2.f, ofGetHeight()/2.f, r);
    grain.get()->addAttractionPoint(nucleus.getPosition(), 100.f);
    
    // add custom data
    grain.get()->setId(grainId);
    grains.push_back(grain);
    
    // now connect circle to the nucleus
    ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
    joint.get()->setup(ofworld.getWorld(), nucleus.body, grains.back().get()->body);
    joint.get()->setLength(25);
    joints.push_back(joint);
    
    focus = grains.back().get();

}

// remove all joints from nucleus to grains
void blowpop::destroyJoints(){
    for(int i=0; i<joints.size(); i++) {
        joints[i].get()->destroy();
    }
    joints.clear();
}


