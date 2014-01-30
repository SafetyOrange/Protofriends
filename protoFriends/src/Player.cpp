//
//  Player.cpp
//  dildoCircus
//
//  Created by Keion Anthony Marefat on 1/25/14.
//
//

#include "Player.h"


Player::Player(){               //Essentially a setup function
    
    dX=0;
    dY=0;
    health = 5;
    speed = 10;
    pos = pCenter;
    w=20;
    h=50;
    dead=false;
    
}
void Player::prime(int _index){
    
    index=_index;
    pos.x= (index+1)* (.17* ofGetWidth());
    pos.y= ofGetHeight()/3;
    
  //  setPhysics(1.f, 0.f, 1);
    
}

void Player::myUpdate(){
    body->SetFixedRotation(true);
    update();
}

void Player::myDraw(){
    
    
    if(!dead){
    ofSetRectMode(OF_RECTMODE_CENTER);//KILL//KILL//KILL//KILL//KILL//KILL

    ofPushStyle();
        if(index==1)ofSetColor(255, 150, 0);
        if(index==2)ofSetColor(255, 0, 255);
        draw();
    ofPopStyle();
    
    ofSetRectMode(OF_RECTMODE_CORNER);//KILL//KILL//KILL//KILL//KILL
    }
}

void Player::move(float xVal){
    
    if(!dead){
    
        dX=ofMap(xVal, 0, 1, 0, speed);
        
            float velChange = dX - getVelocity().x;
            float impulse = body->GetMass() * velChange;
            body->ApplyLinearImpulse( b2Vec2(impulse,0), body->GetWorldCenter(), false );
    }
}

void Player::jump(float yVal){
    
    setVelocity(body->GetLinearVelocity().x, yVal);
    }