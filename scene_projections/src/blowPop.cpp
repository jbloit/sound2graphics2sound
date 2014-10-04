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
    ofAddListener(osc->vocalPitch, this, &blowpop::onVocalPitch);
    ofAddListener(osc->vocalClass, this, &blowpop::onVocalClass);
    
    ofAddListener(osc->percussionOnset, this, &blowpop::onPercussionOnset);
    ofAddListener(osc->percussionLoudness, this, &blowpop::onPercussionLoudness);
    ofAddListener(osc->percussionBrightness, this, &blowpop::onPercussionBrightness);
    ofAddListener(osc->percussionNoisiness, this, &blowpop::onPercussionNoisiness);
    ofAddListener(osc->percussionPitch, this, &blowpop::onPercussionPitch);
    
    ofRegisterKeyEvents(this);
	ofAddListener(ofworld.contactStartEvents, this, &blowpop::contactStart);
	ofAddListener(ofworld.contactEndEvents, this, &blowpop::contactEnd);
    
    drawSkeleton = false;
    
    //// Scene elements
    // TODO: see if we want to push that to new class
    ofVec2f nucleusPos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    nucleus.setup(ofworld.getWorld(), nucleusPos, 8);
    
    // add custom data
    nucleus.setData(new NucleusData());
    NucleusData * myNucleusData = (NucleusData*) nucleus.getData();
    myNucleusData->bHit = false;
    
    focus = NULL;
    focusJoint = NULL;

    drawMembrane = true;
    
    doPop = false; // arm the pop() function

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
    ofRemoveListener(osc->vocalPitch, this, &blowpop::onVocalPitch);
    ofRemoveListener(osc->vocalClass, this, &blowpop::onVocalClass);
    
    ofRemoveListener(osc->percussionOnset, this, &blowpop::onPercussionOnset);
    ofRemoveListener(osc->percussionLoudness, this, &blowpop::onPercussionLoudness);
    ofRemoveListener(osc->percussionBrightness, this, &blowpop::onPercussionBrightness);
    ofRemoveListener(osc->percussionNoisiness, this, &blowpop::onPercussionNoisiness);
    ofRemoveListener(osc->percussionPitch, this, &blowpop::onPercussionPitch);
    
    ofRemoveListener(ofworld.contactStartEvents, this, &blowpop::contactStart);
	ofRemoveListener(ofworld.contactEndEvents, this, &blowpop::contactEnd);
    grains.clear();
    joints.clear();
    stars.clear();
    nucleus.destroy();
    
    // notify Max of scene end
    ofxOscMessage m;
    m.setAddress("/blowpop/on");
    m.addIntArg(0);
    osc->sender.sendMessage(m);
}

// ------------------------------------------------------
void blowpop::update(){

    cout << "grains size " << grains.size() << "\n";
    
    if (doPop) {
        pop();
        doPop = false;
    }
    
    // make stars gravitate around nucleus
    for(int i=0; i<stars.size(); i++) {
        stars[i].get()->update();
        
        if (stars[i].get()->doGravitate()){
            float mydistance = nucleus.getPosition().distance(stars[i].get()->getPosition());
            if (mydistance < 300) stars[i].get()->addRepulsionForce(nucleus.getPosition(), 2.f);
            else stars[i].get()->addAttractionPoint(nucleus.getPosition(), 1.f);
        }
    }
    
    // play grains when moving
    for(int i=0; i<grains.size(); i++) {
        grains[i].get()->update();
        if (grains[i].get()->changedDirection){
            playGrain(grains[i].get()->getId(), grains[i].get()->energy, 1.f/grains.size());
        }
        
        if (grains[i].get()->shouldRemove()){

            grains.erase(grains.begin()+i);
        }

    }
}

// ------------------------------------------------------
void blowpop::draw(){
    
    // Nucleus
    nucleus.draw();
    
    // Grains
    for(int i=0; i<grains.size(); i++) {
        grains[i].get()->draw();
    }
    
    // Membrane ( Hull around grains )
    if (grains.size()>2 && drawMembrane){
        vector<ofPoint> points, membrane;
        for (int i = 0; i<grains.size(); i++){
            points.push_back(ofPoint(grains[i]->getPosition()));
        }
        points.push_back(ofPoint(nucleus.getPosition()));
        membrane = hull.getHull(points);
        
        ofFill();
        ofSetColor(255, 255, 255, 100);
        ofBeginShape();
        for (int i = 0; i < membrane.size(); i++){
            if (i == 0){
                ofCurveVertex(membrane[0].x, membrane[0].y); // we need to duplicate 0 for the curve to start at point 0
                ofCurveVertex(membrane[0].x, membrane[0].y);; // we need to duplicate 0 for the curve to start at point 0
            } else if (i == membrane.size()-1){
                ofCurveVertex(membrane[i].x, membrane[i].y);
                ofCurveVertex(membrane[0].x, membrane[0].y);	// to draw a curve from pt N to pt 0
                ofCurveVertex(membrane[0].x, membrane[0].y);	// we duplicate the first point twice
            } else {
                ofCurveVertex(membrane[i].x, membrane[i].y);
            }
        }
        ofEndShape();
    }
    
    // Percussions star shapes
    for (int i=0; i<stars.size(); i++){
        stars[i].get()->draw();
    }
    
}

#pragma mark vocal callbacks

// ------------------------------------------------------
void blowpop::onVocalOnset(int& value){
    cout << "BLOWPOP - VOCAL ONSET, id: " << value << " \n";

    addGrain(value);
}

// ------------------------------------------------------
void blowpop::onVocalLoudness(float& value){
    // make focus grain grow / or make it further away from nucleus
    float grainGrowfactor = 0.2;
    if (focus != NULL){
        float currentRadius =  focus->getRadius();
        currentRadius += grainGrowfactor * value;
        focus->setRadius(currentRadius);
    }
    
    float jointGrowFactor = 2.f;
    if (focusJoint != NULL){
        float currentLength =  focusJoint->getLength();
        currentLength += jointGrowFactor * value;
        focusJoint->setLength(currentLength);
    }
    
}
// ------------------------------------------------------
void blowpop::onVocalBrightness(float& value){

}
// ------------------------------------------------------
void blowpop::onVocalNoisiness(float& value){

}
// ------------------------------------------------------
void blowpop::onVocalPitch(float& value){

}
// ------------------------------------------------------
void blowpop::onVocalClass(int& value){

}

#pragma mark percussion callbacks
// ------------------------------------------------------
void blowpop::onPercussionOnset(int& value){
    cout << "percussion onset : " << value << " \n";
    addStar(value);
}
// ------------------------------------------------------
void blowpop::onPercussionBrightness(float &value){

}
// ------------------------------------------------------
void blowpop::onPercussionNoisiness(float &value){

}
// ------------------------------------------------------
void blowpop::onPercussionLoudness(float &value){

}
// ------------------------------------------------------
void blowpop::onPercussionPitch(float &value){

}

#pragma mark keyboard callbacks
// ------------------------------------------------------
void blowpop::keyPressed(ofKeyEventArgs& args){
	if( args.key == 'o' ){
        int val = 0;
		onVocalOnset(val);
	}

    if( args.key == 'p' ){
        int val = 0;
		onPercussionOnset(val);
	}

    
    if( args.key == ' ' ){
//        onPercOnset();
    }
    
    if( args.key == 's' ){
		drawSkeleton = !drawSkeleton;
	}
    
    if( args.key == ' ' ){
        doPop = true;
    }
    
}
void blowpop::keyReleased(ofKeyEventArgs& args){
    
}

#pragma mark collision callbacks

//--------------------------------------------------------------
void blowpop::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
		
        // Determine which elements collided
        BaseUserData *dataA = (BaseUserData*) e.a->GetBody()->GetUserData();
        BaseUserData *dataB = (BaseUserData*) e.b->GetBody()->GetUserData();
        
        if (dataA && dataB){

            // grain-grain collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::blowpop_grain){
//                cout << "*--* grain-grain collision " << endl;
            }
            // grain-bounds collision
            if (dataA->getType() == BaseUserData::blowpop_grain && dataB->getType() == BaseUserData::bounds){
//                cout << "*--_ grain-bounds collision " << endl;
//                GrainData * myGrain = (GrainData*) dataA;
//                playGrain(myGrain->grainId);
            }
            // bounds-grain collision
            if (dataA->getType() == BaseUserData::bounds && dataB->getType() == BaseUserData::blowpop_grain){
                cout << "_--* bounds-grain collision " << endl;
                GrainData * myGrain = (GrainData*) dataB;
                playGrain(myGrain->grainId, 1, 1/grains.size());
                
                // did collide with side walls?
                if ((myGrain->position.x - 10 * myGrain->radius) <= 0 || myGrain->position.x + 10 * myGrain->radius >= ofGetWidth()) {
                    myGrain->toRemove = true;
                    
                }
            }
            // nucleus-grain collision
            if (dataA->getType() == BaseUserData::blowpop_nucleus && dataB->getType() == BaseUserData::blowpop_grain){
//                cout << ".--* nucleus-grain collision " << endl;
//                destroyJoints();
            }
            // star-grain collision
            if (dataA->getType() == BaseUserData::blowpop_star && dataB->getType() == BaseUserData::blowpop_grain){
//                cout << "$--* star-grain collision " << endl;
                doPop = true;
            }
            
        }
	}
}

//--------------------------------------------------------------
void blowpop::contactEnd(ofxBox2dContactArgs &e) {
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
// Trigger the grain's sound
void blowpop::playGrain(int grainId, float rate, float amplitude){
    // play grain
    ofxOscMessage m;
    m.setAddress("/blowpop/play");
    m.addIntArg(grainId);
    m.addFloatArg(rate);
    m.addFloatArg(amplitude);
    osc->sender.sendMessage(m);
}
// ------------------------------------------------------
void blowpop::addGrain(int grainId){
    
    // Create grain
    float r = 1.f;
    ofPtr<Grain> grain = ofPtr<Grain>(new Grain);
    grain.get()->setPhysics(3.0, 0.6, 0.5);
    grain.get()->setup(ofworld.getWorld(), vocalistPosition, r);
    grain.get()->addAttractionPoint(nucleus.getPosition(), 100.f);
    
    // add custom data
    grain.get()->dataSetup(grainId);
    grains.push_back(grain);
    
    // now connect circle to the nucleus
    ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
    joint.get()->setup(ofworld.getWorld(), nucleus.body, grains.back().get()->body);
    joint.get()->setLength(5);
    joints.push_back(joint);
    
    focus = grains.back().get();
    focusJoint = joints.back().get();
}

// percussion polygons
void blowpop::addStar(int starId){
    ofPtr<Star> star = ofPtr<Star>(new Star);
    star.get()->create(ofworld.getWorld());
    star.get()->setPosition(percussionnistPosition);
    star.get()->dataSetup(starId);
    stars.push_back(star);
}

// Pop the grape of grains!
void blowpop::pop(){
    for(int i=0; i<joints.size(); i++) {
        joints[i].get()->destroy();
    }
    
    for (int i=0; i<stars.size(); i++){
        stars[i].get()->setGravitate(false);
    }
    joints.clear();
    drawMembrane = false;
    focusJoint = NULL;
    focus = NULL;
}

