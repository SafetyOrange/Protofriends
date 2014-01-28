#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    debug=false;
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    player1.prime(1);
    player2.prime(2);

    box2d.init();
    box2d.setFPS(60);
	box2d.setGravity(0, 10);
    box2d.createBounds();
    
    
    
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
    
//    b2Vec2 derp = screenPtToWorldPt(ofVec2f(ofGetWidth(), ofGetHeight()));
//    ofLog()<< derp.x << "  " << derp.y << endl;
    ground.setPhysics(0.f, 0, 1);
    ground.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()*.9, ofGetWidth(), ofGetHeight()*.5);
    
    player1.setPhysics(1.f, 0.1, 0); // Density, Bounce, Friction 0.f density makes shape static.
    player1.setup(box2d.getWorld(), player1.pos.x, player1.pos.y, player1.w, player1.h);
    
    player2.setPhysics(1.f, 0.1, 0); // 0.f density makes shape static.
    player2.setup(box2d.getWorld(), player2.pos.x, player2.pos.y, player2.w, player2.h);
    
    box2d.enableGrabbing();
    box2d.registerGrabbing();
    
    }

//--------------------------------------------------------------
void testApp::update(){

    box2d.update();
    
    
    player1.myUpdate();
    player2.myUpdate();

   
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
     //   if (e.axis == 3)    mVal.y=e.value;
        
        if (abs(mVal.x)<stickBuffer)  mVal.x=0;
    //    if (abs(mVal.y)<stickBuffer)  mVal.y=0;
        
        
        player1.move(mVal.x);
    }
}

//--------------------------------------------------------------
void testApp::buttonPressed(ofxGamepadButtonEvent &e){
    
    
}
//--------------------------------------------------------------
void testApp::buttonReleased(ofxGamepadButtonEvent &e){
    
    if(e.button==11)player1.jump(-10);
    
}
//--------------------------------------------------------------
void testApp::axisChanged2(ofxGamepadAxisEvent &e){
    
    if(player2.dead==false){
        
        //LEFT JOYSTICK
        if (e.axis == 2)    mVal2.x=e.value;
        if (e.axis == 3)    mVal2.y=e.value;
        
        if (abs(mVal2.x)<stickBuffer)  mVal2.x=0;
        if (abs(mVal2.y)<stickBuffer)  mVal2.y=0;
        
        
       // player2.move(mVal2.x,mVal2.y);
        
    }
    
}
//--------------------------------------------------------------
void testApp::buttonPressed2(ofxGamepadButtonEvent &e){
    

}
//--------------------------------------------------------------
void testApp::buttonReleased2(ofxGamepadButtonEvent &e){
    
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
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
