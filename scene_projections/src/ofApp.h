#pragma once

#include "ofMain.h"
#include "oscManager.h"
#include "_projectGlobals.h"
#include "ofEvents.h"
#include "ofxGui.h"

#include "projections.h"
#include "blowpop.h"

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void onBlowpopToggle(int& value);

    oscManager * osc;

    // ----------------- scenes and gui-menu controls
    ofxPanel gui;
    bool showMenu;
    
    projections proj;
    ofxToggle proj_on;
    bool previousProjToggle;
    
    blowpop blowpop;
    ofxToggle blowpop_on;
    bool previousBlowpopToggle;
    
    float previousGravity;
    ofxFloatSlider gravity;

};
