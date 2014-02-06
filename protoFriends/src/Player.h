//
//  Player.h
//  dildoCircus
//
//  Created by Keion Anthony Marefat on 1/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Player : public ofxBox2dRect{
    
public:
    
    Player();
    
    int index=0;
    
    float health;
    float speed;
    float dX;
    float dY;
    float w;
    float h;
    float angle;
    void prime(int _index);
    
    bool primate;
    bool dead;
    bool grounded;
    
    void myUpdate();
    void myDraw();
    void move(float xVal, float yVal);
    void jump(float amt);
    
    
    bool friendMode;
    bool vault;
    bool net;
    bool lift;
    bool toss;
    bool grab;


    ofVec2f pos;
    ofVec2f pCenter = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);

};