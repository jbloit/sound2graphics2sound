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
    numberOfNodes = 4;
    float nodeX[4] = {0, 1, 0, -1 };
    float nodeY[4] = {1, 0, -1, 0};
	for (int i=0; i<numberOfNodes; i++) {
		ofPtr<ofxBox2dCircle> node = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		node.get()->setPhysics(3.0, 0.53, 0.1);
		node.get()->setup(ofworld.getWorld(), nucleus_x + nodeX[i] * 30, nucleus_y + nodeY[i] * 30, 8);
		nodes.push_back(node);
	}
    
    // now connect each circle to the nucleus
	for (int i=0; i<nodes.size(); i++) {
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
        joint.get()->setup(ofworld.getWorld(), nucleus.body, nodes[i].get()->body);
		joint.get()->setLength(25);
		joints.push_back(joint);
	}
    
    // and connect each circle to its neighbors
    for (int i=0; i<nodes.size(); i++) {
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
        if (i == nodes.size()-1){
            joint.get()->setup(ofworld.getWorld(), nodes[i].get()->body, nodes[0].get()->body);
        }
        else{
            joint.get()->setup(ofworld.getWorld(), nodes[i].get()->body, nodes[i+1].get()->body);
        }
        joint.get()->setDamping(1.f);
        joint.get()->setFrequency(0.f);
		joints.push_back(joint);
	}
    
    cout << "new dot with " << numberOfNodes << " nodes\n";
}

void dot::update(){
// TODO: add ALIVE_CHECK code here

}

void dot::draw(){

	// Skeleton
    ofFill();
    ofSetColor(255);
	nucleus.draw();
	for(int i=0; i<nodes.size(); i++) {
		nodes[i].get()->draw();
	}
	
	for(int i=0; i<joints.size(); i++) {
		joints[i].get()->draw();
	}
    
    // Membrane
    ofFill();
    ofSetColor(255, 255, 255, 150);
    ofBeginShape();
    for (int i = 0; i < nodes.size(); i++){
        // sorry about all the if/states here, but to do catmull rom curves
        // we need to duplicate the start and end points so the curve acutally
        // goes through them.
        
        // for i == 0, we just call the vertex twice
        // for i == nCurveVertices-1 (last point) we call vertex 0 twice
        // otherwise just normal ofCurveVertex call
        
        if (i == 0){
            ofCurveVertex(nodes[0]->getPosition().x, nodes[0]->getPosition().y); // we need to duplicate 0 for the curve to start at point 0
            ofCurveVertex(nodes[0]->getPosition().x, nodes[0]->getPosition().y);; // we need to duplicate 0 for the curve to start at point 0
        } else if (i == nodes.size()-1){
            ofCurveVertex(nodes[i]->getPosition().x, nodes[i]->getPosition().y);
            ofCurveVertex(nodes[0]->getPosition().x, nodes[0]->getPosition().y);	// to draw a curve from pt N to pt 0
            ofCurveVertex(nodes[0]->getPosition().x, nodes[0]->getPosition().y);	// we duplicate the first point twice
        } else {
            ofCurveVertex(nodes[i]->getPosition().x, nodes[i]->getPosition().y);
        }
    }
    ofEndShape();
}



