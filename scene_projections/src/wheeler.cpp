//
//  wheeler.cpp
//  shissss
//
//  Created by julien@macmini on 10/15/14.
//
//

#include "wheeler.h"

using namespace std;

void wheeler::setup(){
    
    osc = oscManager::Instance();
    
    // notify Max of scene start
    ofxOscMessage m;
    m.setAddress("/wheeler/on");
    m.addIntArg(1);
    osc->sender.sendMessage(m);
    
    // Register event listeners
    ofAddListener(osc->vocalOnset, this, &wheeler::onVocalOnset);
    ofAddListener(osc->vocalLoudness, this, &wheeler::onVocalLoudness);
    ofAddListener(osc->vocalBrightness, this, &wheeler::onVocalBrightness);
    ofAddListener(osc->vocalNoisiness, this, &wheeler::onVocalNoisiness);
    ofAddListener(osc->vocalPitch, this, &wheeler::onVocalPitch);
    ofAddListener(osc->vocalClass, this, &wheeler::onVocalClass);
    
    ofAddListener(osc->percussionOnset, this, &wheeler::onPercussionOnset);
    ofAddListener(osc->percussionLoudness, this, &wheeler::onPercussionLoudness);
    ofAddListener(osc->percussionBrightness, this, &wheeler::onPercussionBrightness);
    ofAddListener(osc->percussionNoisiness, this, &wheeler::onPercussionNoisiness);
    ofAddListener(osc->percussionPitch, this, &wheeler::onPercussionPitch);
    
    ofAddListener(osc->piezo1, this, &wheeler::onPiezo1);
    ofAddListener(osc->piezo2, this, &wheeler::onPiezo2);
    ofAddListener(osc->piezo3, this, &wheeler::onPiezo3);
    ofAddListener(osc->piezo4, this, &wheeler::onPiezo4);
    
    ofRegisterKeyEvents(this);
	ofAddListener(ofworld.contactStartEvents, this, &wheeler::contactStart);
	ofAddListener(ofworld.contactEndEvents, this, &wheeler::contactEnd);

    // init vector capacity to avoid dynamic resizes
    grains.reserve(maxVocalSamples);
    stars.reserve(maxPercussionSamples);
}

// ------------------------------------------------------
// End scene and deallocate objects if needed. This is not a destructor, we want to
// be able to call it even when the object is not destroyed.
void wheeler::terminate(){
    
    ofUnregisterKeyEvents(this);
    ofRemoveListener(osc->vocalOnset, this, &wheeler::onVocalOnset);
    ofRemoveListener(osc->vocalLoudness, this, &wheeler::onVocalLoudness);
    ofRemoveListener(osc->vocalBrightness, this, &wheeler::onVocalBrightness);
    ofRemoveListener(osc->vocalNoisiness, this, &wheeler::onVocalNoisiness);
    ofRemoveListener(osc->vocalPitch, this, &wheeler::onVocalPitch);
    ofRemoveListener(osc->vocalClass, this, &wheeler::onVocalClass);
    
    ofRemoveListener(osc->percussionOnset, this, &wheeler::onPercussionOnset);
    ofRemoveListener(osc->percussionLoudness, this, &wheeler::onPercussionLoudness);
    ofRemoveListener(osc->percussionBrightness, this, &wheeler::onPercussionBrightness);
    ofRemoveListener(osc->percussionNoisiness, this, &wheeler::onPercussionNoisiness);
    ofRemoveListener(osc->percussionPitch, this, &wheeler::onPercussionPitch);
    
    ofRemoveListener(osc->piezo1, this, &wheeler::onPiezo1);
    ofRemoveListener(osc->piezo2, this, &wheeler::onPiezo2);
    ofRemoveListener(osc->piezo3, this, &wheeler::onPiezo3);
    ofRemoveListener(osc->piezo4, this, &wheeler::onPiezo4);
    
    ofRemoveListener(ofworld.contactStartEvents, this, &wheeler::contactStart);
	ofRemoveListener(ofworld.contactEndEvents, this, &wheeler::contactEnd);
    grains.clear();
    stars.clear();
    axle.destroy();
    
    // notify Max of scene end
    ofxOscMessage m;
    m.setAddress("/wheeler/on");
    m.addIntArg(0);
    osc->sender.sendMessage(m);
}

// ------------------------------------------------------
void wheeler::update(){
    
    // manage scene behavior here

    
}

// ------------------------------------------------------
void wheeler::draw(){
    
    // Axle
        axle.draw();
    
    // Grains
    for(int i=0; i<grains.size(); i++) {
        grains[i].get()->draw();
    }

    // Stars
    for (int i=0; i<stars.size(); i++){
        stars[i].get()->draw();
    }
    
}

#pragma mark vocal callbacks

// ------------------------------------------------------
void wheeler::onVocalOnset(int& value){
    addGrain(value);
}

// ------------------------------------------------------
void wheeler::onVocalLoudness(float& value){
    
}
// ------------------------------------------------------
void wheeler::onVocalBrightness(float& value){
    
}
// ------------------------------------------------------
void wheeler::onVocalNoisiness(float& value){
    
}
// ------------------------------------------------------
void wheeler::onVocalPitch(float& value){
    
}
// ------------------------------------------------------
void wheeler::onVocalClass(int& value){

}

#pragma mark percussion callbacks
// ------------------------------------------------------
void wheeler::onPercussionOnset(int& value){

}
// ------------------------------------------------------
void wheeler::onPercussionBrightness(float &value){
    
}
// ------------------------------------------------------
void wheeler::onPercussionNoisiness(float &value){
    
}
// ------------------------------------------------------
void wheeler::onPercussionLoudness(float &value){
    
}
// ------------------------------------------------------
void wheeler::onPercussionPitch(float &value){
    
    
}
#pragma mark piezo pickup callbacks
// ------------------------------------------------------
void wheeler::onPiezo1(int &value){

}
// ------------------------------------------------------
void wheeler::onPiezo2(int &value){
    
}
// ------------------------------------------------------
void wheeler::onPiezo3(int &value){
    
}
// ------------------------------------------------------
void wheeler::onPiezo4(int &value){
    
}


#pragma mark keyboard callbacks
// ------------------------------------------------------
void wheeler::keyPressed(ofKeyEventArgs& args){
	if( args.key == 'o' ){
        int val = 0;
		onVocalOnset(val);
	}
    
    if( args.key == 'p' ){
        int val = 0;
		onPercussionOnset(val);
	}
    
    if( args.key == ' ' ){
        grains.clear();
        //        onPercOnset();
    }
    
    if( args.key == 's' ){
		drawSkeleton = !drawSkeleton;
	}
    
}
void wheeler::keyReleased(ofKeyEventArgs& args){
    
}

#pragma mark collision callbacks

//--------------------------------------------------------------
void wheeler::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
		
        // Determine which elements collided
        BaseUserData *dataA = (BaseUserData*) e.a->GetBody()->GetUserData();
        BaseUserData *dataB = (BaseUserData*) e.b->GetBody()->GetUserData();
        
        if (dataA && dataB){
            // grain-grain collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::blowpop_grain){
            }
            // grain-bounds collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::bounds){

            }
            // bounds-grain collision
            if (dataA->getType() == BaseUserData::bounds && dataB->getType() == BaseUserData::blowpop_grain){

            }

            // star-grain collision
            if (dataA->getType() == BaseUserData::blowpop_star && dataB->getType() == BaseUserData::blowpop_grain){

            }
            
            // star-star collision
            if (dataA->getType() == BaseUserData::blowpop_star && dataB->getType() == BaseUserData::blowpop_star){

            }
            
            // bounds-star collision
            if (dataA->getType() == BaseUserData::bounds && dataB->getType() == BaseUserData::blowpop_star){

                
            }
        }
	}
}

//--------------------------------------------------------------
void wheeler::contactEnd(ofxBox2dContactArgs &e) {
    //    if(e.a != NULL && e.b != NULL) {
    //
    //        // Determine which elements collided
    //        BaseUserData *dataA = (BaseUserData*) e.a->GetBody()->GetUserData();
    //        BaseUserData *dataB = (BaseUserData*) e.b->GetBody()->GetUserData();
    //
    //        if (dataA && dataB){
    //
    //            // star-grain collision
    //            if (dataA->getType() == BaseUserData::blowpop_star && dataB->getType() == BaseUserData::blowpop_grain){
    //                cout << "$--* star-grain collision " << endl;
    //
    //            }
    //        }
    //	}
}

# pragma mark behavior
// ------------------------------------------------------
// Trigger the grain's sonic behavior
void wheeler::grainDrone(int grainId, float radius, float x, float y){
    ofxOscMessage m;
    m.setAddress("/wheeler/droneVox");
    m.addFloatArg(radius);
    m.addFloatArg(2.f * x / ofGetWidth() - 1.f ); // panning
    m.addFloatArg( -y / ofGetHeight() + 1.f);     // normalized filter freq 0-1
    m.addIntArg(grainId);
    osc->sender.sendMessage(m);
}
// ------------------------------------------------------
// Trigger the grain's sound
void wheeler::playGrain(int grainId,float amplitude){
    // play grain
    ofxOscMessage m;
    m.setAddress("/wheeler/playVox");
    m.addFloatArg(amplitude);
    m.addIntArg(grainId);
    osc->sender.sendMessage(m);
}

// ------------------------------------------------------
// Trigger the star's sonic behavior
void wheeler::starDrone(int starId, float energy, float x, float y){
    ofxOscMessage m;
    m.setAddress("/wheeler/droneDrum");
    m.addFloatArg(energy);
    m.addFloatArg(2.f * x / ofGetWidth() - 1.f ); // panning
    m.addFloatArg( -y / ofGetHeight() + 1.f);     // normalized filter freq 0-1
    m.addIntArg(starId);
    osc->sender.sendMessage(m);
}
// ------------------------------------------------------
// Trigger the star's sound
void wheeler::playStar(int grainId, float rate, float amplitude){
    // play grain
    ofxOscMessage m;
    m.setAddress("/wheeler/playDrum");
    m.addIntArg(grainId);
    //    m.addFloatArg(rate);
    //    m.addFloatArg(amplitude);
    osc->sender.sendMessage(m);
}


// ------------------------------------------------------
void wheeler::addGrain(int grainId){
    
    // remove focus from previous grains
    for (int i = 0; i<grains.size(); i++){
        grains[i].get()->hasFocus = false;
    }
    
    // Create grain
    float r = 5.f;
    ofPtr<Grain> grain = ofPtr<Grain>(new Grain);
    grain.get()->setPhysics(0.0, 0.6, 0.5);
    ofVec2f position = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    grain.get()->setup(ofworld.getWorld(), position, r);
    //    grain.get()->addAttractionPoint(nucleus.getPosition(), 100.f);
    
    // add custom data
    grain.get()->dataSetup(grainId);
    grains.push_back(grain);
    
    //    // now connect circle to the nucleus
    //    ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
    //    joint.get()->setup(ofworld.getWorld(), nucleus.body, grains.back().get()->body);
    //    joint.get()->setLength(5);
    //    joints.push_back(joint);
    
    
    //    focusJoint = joints.back().get();
}

// percussion polygons
void wheeler::addStar(int starId){
    ofPtr<Star> star = ofPtr<Star>(new Star);
    star.get()->create(ofworld.getWorld());
    star.get()->setPosition(ofVec2f(ofRandom(ofGetWidth()), 10.f));
    star.get()->dataSetup(starId);
    
    if (stars.size() > maxPercussionSamples) removeRandomStar();
    stars.push_back(star);
}

void wheeler::removeRandomStar(){
    // Randomly delete a star
    int numStars = stars.size();
    if (numStars > 0){
        int i = int(ofRandom(numStars));
        cout << " --- DELETE STAR " << i << "\n";
        starDrone(stars[i].get()->getId(), 0.f, ofGetWidth()/2, ofGetHeight()/2); // turn off volume
        stars.erase(stars.begin()+i);
    }
}


