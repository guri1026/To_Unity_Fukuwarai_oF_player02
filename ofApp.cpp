#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);
    
    sender.setup(HOST, PORT);
    
    
    ////shake //////
    serial.setup("/dev/cu.usbmodem141221",9600);
    madeConnect = false;
    
    d = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //// シリアル通信 ....................
    if(madeConnect == false){
        serial.writeByte(255);
    }
    
    if(serial.available() >= 4){
        for(int i=0; i<3; i++){
            data_before[i] = data[i];
        }
        madeConnect = true;
        value = serial.readByte();
        
        if(value == 255){
            for(int i=0; i<3; i++){
                data[i] = ofMap(serial.readByte(), 0, 100, 0, 1023);
            }
        }
        
        serial.writeByte(255);
    }
    
    ///// 取得データで変化量を計算
    int sum = 0;
    for(int i=0; i<3; i++){
        sum = sum + pow( (data[i] - data_before[i]), 2.0);
    }
    d = 0;
    d = sqrt(sum);
    
    ///// shake................
    
    if(d > 200){
        shake_on_off = true;
    }
    else{
        shake_on_off = false;
        move_right = move_left = false;
    }
    
    ///// move .................
    if(shake_on_off == true && data[0] < 250){
        move_right = false;
        move_straight = false;
        
        move_left = true;
        
    }
    else if(shake_on_off == true &&  300 <= data[0] && data[0] <= 650){
        move_right = false;
        move_left = false;
        
        move_straight = true;
        
    }
    else if(shake_on_off == true && data[0] > 650){
        move_left = false;
        move_straight = false;
        
        move_right = true;
    }
    
    
    
    
    
    //// send message
    if(shake_on_off){
        shake();
    }
    if(shake_on_off == false){
        no_shake();
    }
    if(move_right){
        right_move();
    }
    if(move_left){
        left_move();
    }
    
    
    //// seusu stand
    if(data[1] > 710){
        sensu_stand();
    }
    
    cout << "x : " << data[0] << " / " <<
    "y : " << data[1] << " / " <<
    "z : " << data[2] << endl;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofDrawCircle(mouseX, mouseY, 10);
    
    if(shake_on_off){
        ofSetColor(0,255,127);
        ofCircle(ofGetScreenWidth()/2, ofGetScreenHeight()/2, 50);
    }
    
    if(move_left){
        ofSetColor(255,0,127);
        ofCircle(50, 20, 10);
    }
    if(move_right){
        ofSetColor(255,0,127);
        ofCircle(50, 100, 10);
    }
    
    if(data[1] > 710){
        ofCircle(50,200,20);
    }
    
}


///////////////////////////////////////////

void ofApp::shake(){
    ofxOscMessage m;
    m.setAddress("/player02/shake/yes");
    //m.addFloatArg(shake_on_off);
    sender.sendMessage(m);
}

void ofApp::no_shake(){
    ofxOscMessage m;
    m.setAddress("/player02/shake/no");
    sender.sendMessage(m);
}

void ofApp::right_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/right");
    sender.sendMessage(m);
    
}

void ofApp::left_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/left");
    sender.sendMessage(m);
}

void ofApp::straight_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/straight");
    sender.sendMessage(m);
}

void ofApp::sensu_stand(){
    ofxOscMessage m;
    m.setAddress("/player02/sensu/stand");
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

