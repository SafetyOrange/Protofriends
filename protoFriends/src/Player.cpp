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
    w=20;
    h=50;

    dead=false;
    primate=false;
    
    fixture.filter.groupIndex=-1;
    
}
void Player::prime(int _index){
    
    index=_index;
    pos.x= (index+1)* (.20* ofGetWidth());
    pos.y= ofGetHeight()/3;

    setPhysics(2.f, 0, 0);                // Density, Bounce, Friction.   0.f density makes shape static.
}

void Player::myUpdate(){
    
    body->SetFixedRotation(true);
    update();
    
    
    //Make sure we're not falling/flying
    if(abs(body->GetLinearVelocity().y)>0){
        grounded=false;
        ofLog()<<"Arf"<<endl;
    }
    
    

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
        body->ApplyLinearImpulse( b2Vec2(impulse,0), body->GetWorldCenter(), true );
        
        if(grounded){
            b2Vec2 pos = body->GetPosition();
            pos.y-=.5;
            body->SetTransform(pos, body->GetAngle());
        }
        
        
        
    }

}

void Player::jump(float yVal){
    
    setVelocity(body->GetLinearVelocity().x, yVal);
}