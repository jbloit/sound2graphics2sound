//
//  dot.cpp
//  scene_projections
//
//  Created by Julien Bloit on 28/08/14.
//
//

#include "dot.h"
#include "ofMath.h"

void dot::setup(float _x, float _y){
    
    nucleus_x = _x;
    nucleus_y = _y;
    
    nucleus.setup(ofworld.getWorld(), 20, ofGetHeight()/2, 4);
    
    // First we add nodes
    numberOfNodes = (int) ofRandom(2, 6);
	for (int i=0; i<numberOfNodes; i++) {
		ofPtr<ofxBox2dCircle> node = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		node.get()->setPhysics(3.0, 0.53, 0.1);
		node.get()->setup(ofworld.getWorld(), nucleus_x + ofRandom(-30,30), nucleus_y + ofRandom(-30,30), 8);
		nodes.push_back(node);
	}
    
    // now connect each circle with a joint
	for (int i=0; i<nodes.size(); i++) {
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
        joint.get()->setup(ofworld.getWorld(), nucleus.body, nodes[i].get()->body);
		joint.get()->setLength(25);
		joints.push_back(joint);
	}
    cout << "new dot with " << numberOfNodes << " nodes\n";
}

void dot::update(){
// TODO: add ALIVE_CHECK code here

}

void dot::draw(){
	ofSetHexColor(0xf2ab01);
	nucleus.draw();
	
	for(int i=0; i<nodes.size(); i++) {
		ofFill();
		ofSetHexColor(0x01b1f2);
		nodes[i].get()->draw();
	}
	
	for(int i=0; i<joints.size(); i++) {
		ofSetHexColor(0x444342);
		joints[i].get()->draw();
	}
}



