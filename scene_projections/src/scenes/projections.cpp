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
    
}

// ------------------------------------------------------
void projections::update(){

}

// ------------------------------------------------------
void projections::draw(){
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
}

// ------------------------------------------------------
void projections::onVocalOnset(){
    cout << "vocal onset event received in projections\n";
    addBox();
}
// ------------------------------------------------------
void projections::onVocalLoudness(float& value){
    cout << "vocal loudness event received in projections : " << value << " \n";

}

# pragma mark private
// ------------------------------------------------------
void projections::addCircle(){
    float r = ofRandom(4, 20);
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(ofworld.getWorld(), 0, 0, r);
}
// ------------------------------------------------------
void projections::addBox(){
    float w = ofRandom(4, 20);
    float h = ofRandom(4, 20);
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    boxes.back().get()->setup(ofworld.getWorld(), 0, 0, w, h);
}


