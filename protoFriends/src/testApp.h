#pragma once

#include "ofMain.h"
#include "Player.h"
#include "ofxGamepadHandler.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
        void p2p();
    
    bool debug;
    bool breakJ;
    
    ofxGamepad* pad;
    ofxGamepad* pad2;
    
    Player player1, player2;
    
    
    float stickBuffer = .5;
    float goalAngle,goalAngle2;
    ofVec2f mVal, mVal2;
    ofVec2f rVal, rVal2;
    
    void axisChanged(ofxGamepadAxisEvent &e);
    void buttonPressed(ofxGamepadButtonEvent &e);
    void buttonReleased(ofxGamepadButtonEvent &e);
    
    void axisChanged2(ofxGamepadAxisEvent &e);
    void buttonPressed2(ofxGamepadButtonEvent &e);
    void buttonReleased2(ofxGamepadButtonEvent &e);
    
    // this is the function for contacts
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    
    ofxBox2d box2d;
    ofxBox2dRect ground;
    
    b2RopeJoint* joint;
};
