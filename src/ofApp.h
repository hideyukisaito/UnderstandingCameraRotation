#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class MyBox
{
public:
    MyBox()
    {
        position = ofVec3f(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300));
        color.setHsb(ofRandom(1.0), 1.0, 1.0);
    }
    
    void draw()
    {
        ofPushStyle();
        {
            ofPushMatrix();
            {
                ofTranslate(position);
                ofSetColor(color);
                ofDrawBox(50);
            }
            ofPopMatrix();
        }
        ofPopStyle();
    }
    
    ofVec3f position;
    ofFloatColor color;
};

class ofApp : public ofBaseApp
{

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
    
    ofFbo fbo1, fbo2;
    
    ofCamera cam;
    vector<MyBox> boxes;
    
    ofxPanel gui;
    ofxFloatSlider rotationX, rotationY, distance, lookAtX, lookAtY;
    ofxToggle autoRotate;
    ofxButton changeTarget;
    
    ofEasyCam easyCam;
    
};
