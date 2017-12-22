#pragma once
//// player02


#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "127.0.0.1"
#define PORT 8100


class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void shake();
    void no_shake();
    void left_move();
    void right_move();
    void straight_move();
    void sensu_stand();
    
    ofxOscSender sender;
    
    
    //// shake //////
    ofSerial serial;
    
    bool madeConnect;
    
    int value;
    int x,y,z;
    int data[3];
    int data_before[3];
    
    int shake_count;
    
    bool shake_on_off;
    bool move_right, move_left, move_straight;
    
    long d;
    
};
