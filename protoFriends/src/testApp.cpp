#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    debug=false;
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    box2d.init();
    box2d.setFPS(60);
	box2d.setGravity(0, 62);
    box2d.createBounds();
    
    player1.prime(1);
    player2.prime(2);
    
    ofxGamepadHandler::get()->enableHotplug();  //Look for controllers
    
    
    //CHECK IF THERE EVEN IS A GAMEPAD CONNECTED
    
	if(ofxGamepadHandler::get()->getNumPads()>0){
        pad = ofxGamepadHandler::get()->getGamepad(0);
        ofAddListener(pad->onAxisChanged, this, &testApp::axisChanged);
        ofAddListener(pad->onButtonPressed, this, &testApp::buttonPressed);
        ofAddListener(pad->onButtonReleased, this, &testApp::buttonReleased);
    }
    
    if(ofxGamepadHandler::get()->getNumPads()>1){
        pad2 = ofxGamepadHandler::get()->getGamepad(1);
        ofAddListener(pad2->onAxisChanged, this, &testApp::axisChanged2);
        ofAddListener(pad2->onButtonPressed, this, &testApp::buttonPressed2);
        ofAddListener(pad2->onButtonReleased, this, &testApp::buttonReleased2);
	}
    
    
    //Set physics and overrides
    ground.setPhysics(0.f, 0, 1);
    ground.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()*.9, ofGetWidth(), ofGetHeight()*.5);
    ground.body->SetUserData((void*)3 );
    
    player1.setup(box2d.world, player1.pos.x, player1.pos.y, player1.w, player1.h);
    player1.body->SetUserData((void*)1 );
    
    player2.setup(box2d.world, player2.pos.x, player2.pos.y, player2.w, player2.h);
    player2.body->SetUserData((void*)2 );

    
    //REMOVE AFTER DEBUG!!!
    box2d.enableGrabbing();
    box2d.registerGrabbing();
    
    // Register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
    }

//--------------------------------------------------------------
void testApp::update(){

    box2d.update();
    
    player1.myUpdate();
    player2.myUpdate();
    
    player1.move(mVal.x, mVal.y);
    player2.move(mVal2.x, mVal2.y);
    p2p();

   
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(100, 100, 255);
    
    
    if(debug) {
        ofPushStyle();
        ofxGamepadHandler::get()->draw(10,10);
        ofVec2f p1 = ofVec2f(player1.body->GetPosition().x, player1.body->GetPosition().y);
        ofVec2f p2 = ofVec2f(player2.body->GetPosition().x, player2.body->GetPosition().y);
        ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate())+ "\nPlayer 1:\n" + ofToString(p1.x) + "\n" + ofToString(p1.y)+"\n\nPlayer 2:\n" + ofToString(p2.x) + "\n" + ofToString(p2.y), ofPoint(ofGetMouseX()+20,ofGetMouseY()));
        ofPopStyle();
    }
    
    
    //Ground
    ofPushStyle();
    ofSetColor(150, 150, 0);
    ground.draw();
    ofPopStyle();
    
    player1.myDraw();
    player2.myDraw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='k') debug=!debug;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::axisChanged(ofxGamepadAxisEvent &e) {
    
    if(player1.dead==false){
        
        //LEFT JOYSTICK
        if (e.axis == 2)    mVal.x=e.value;
        if (e.axis == 3)    mVal.y=e.value;
        
        if (abs(mVal.x)<stickBuffer)  mVal.x=0;
        if (abs(mVal.y)<stickBuffer)  mVal.y=0;
        
        
        
    }
}

//--------------------------------------------------------------
void testApp::buttonPressed(ofxGamepadButtonEvent &e){
    
    //This is actually button RELEASED
    if(e.button==12) player1.friendMode=false;
    
    
}
//--------------------------------------------------------------
void testApp::buttonReleased(ofxGamepadButtonEvent &e){
    
    //This is actually button PRESSED
    
    if(e.button==11 && player1.grounded)player1.jump(-15);          // A Button
    if(e.button==12) player1.friendMode=true;                      // B Button
    
}
//--------------------------------------------------------------
void testApp::axisChanged2(ofxGamepadAxisEvent &e){
    
    if(player2.dead==false){
        
        //LEFT JOYSTICK
        if (e.axis == 2)    mVal2.x=e.value;
  //      if (e.axis == 3)    mVal2.y=e.value;
        
        if (abs(mVal2.x)<stickBuffer)  mVal2.x=0;
 //       if (abs(mVal2.y)<stickBuffer)  mVal2.y=0;
        
    }
    
}
//--------------------------------------------------------------
void testApp::buttonPressed2(ofxGamepadButtonEvent &e){
    
    if(e.button==11 && player2.grounded)player2.jump(-15);

}
//--------------------------------------------------------------
void testApp::buttonReleased2(ofxGamepadButtonEvent &e){
    
}
//--------------------------------------------------------------
void testApp::p2p(){
    
    if(player1.friendMode || player2.friendMode){
        
        if(ofDist(player1.body->GetPosition().x,
                  player1.body->GetPosition().y,
                  player2.body->GetPosition().x,
                  player2.body->GetPosition().y) < 2){
            
            //Vaulting
            if(player1.vault){
                player2.jump(-30);
            }
            if(player2.vault){
                player1.jump(-30);
            }
            
            //Hand Holding
            if(player1.grab || player2.grab){
                if(!breakJ){
                    b2RopeJointDef jointDef;
                    
                    jointDef.bodyA=player1.body;
                    jointDef.bodyB=player2.body;
                    jointDef.localAnchorA.SetZero();
                    jointDef.localAnchorB.SetZero();
                    jointDef.maxLength=1;
                    jointDef.collideConnected=false;
                    
                    joint=(b2RopeJoint*)box2d.world->CreateJoint(&jointDef);
                    breakJ=true;
                } else{
                    if(breakJ==true){
                        //                    player1.grab=false;
                        //                    player2.grab=false;
                        box2d.world->DestroyJoint(joint);
                       // ofLog()<<"Did it"<<endl;
                        joint=NULL;
                        breakJ=false;
                        
                    }
                }
                
            }
            // Hug
            if(player1.grab && player2.grab){
                //hug
            }
        }
    }else{
        player1.vault=false;
        player1.net=false;
        player1.toss=false;
        player1.grab=false;
        player2.vault=false;
        player2.net=false;
        player2.toss=false;
        player2.grab=false;
        if(breakJ==true){
            //                    player1.grab=false;
            //                    player2.grab=false;
            box2d.world->DestroyJoint(joint);
            // ofLog()<<"Did it"<<endl;
            joint=NULL;
            breakJ=false;
        }
        
    }
}

//--------------------------------------------------------------

void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------

void testApp::contactStart(ofxBox2dContactArgs &e) {
//	if(e.a != NULL && e.b != NULL) {
//          //0x0 = NOTHING
//          //0x1 = player 1
////        //0x2 = player 2
////        //0x3 = ground
////        //0x4 =
////        //0x5 =
////        //0x6 =
//        
//        ofLog()<<"Contact"<<endl;
//        
//        
//        if((int)e.b->GetBody()->GetUserData()==0x3 && (int)e.a->GetBody()->GetUserData()!=0x1) { //player 1
//            player1.grounded=true;
//        }
//        if((int)e.a->GetBody()->GetUserData()==0x3 && (int)e.b->GetBody()->GetUserData()!=0x1){  //player 1
//            player1.grounded=true;
//        }
//        
//        if((int)e.b->GetBody()->GetUserData()==0x3 && (int)e.a->GetBody()->GetUserData()!=0x2) { //player 2
//            player2.grounded=true;
//        }
//        if((int)e.a->GetBody()->GetUserData()==0x3 && (int)e.b->GetBody()->GetUserData()!=0x2){  //player 2
//            player2.grounded=true;
//        }
//		
//	}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) {
        
//        if(((int)e.b->GetBody()->GetUserData()==0x1 && (int)e.a->GetBody()->GetUserData()==0x5) || ((int)e.a->GetBody()->GetUserData()==0x1 && (int)e.b->GetBody()->GetUserData()==0x5)){ //player 1
//            player1.touchdown=NULL;
//        }
//        
//        if(((int)e.b->GetBody()->GetUserData()==0x2 && (int)e.a->GetBody()->GetUserData()==0x5) || ((int)e.a->GetBody()->GetUserData()==0x2 && (int)e.b->GetBody()->GetUserData()==0x5)){ //player 2
//            player2.touchdown=NULL;
//        }
//        
//        if(((int)e.b->GetBody()->GetUserData()==0x3 && (int)e.a->GetBody()->GetUserData()==0x5) || ((int)e.a->GetBody()->GetUserData()==0x3 && (int)e.b->GetBody()->GetUserData()==0x5)){ //player 3
//            player3.touchdown=NULL;
//        }
//        if(((int)e.b->GetBody()->GetUserData()==0x4 && (int)e.a->GetBody()->GetUserData()==0x5) || ((int)e.a->GetBody()->GetUserData()==0x4 && (int)e.b->GetBody()->GetUserData()==0x5)){ //player 4
//            player4.touchdown=NULL;
//        }
	}
}