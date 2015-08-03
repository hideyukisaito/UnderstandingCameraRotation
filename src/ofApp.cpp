#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetCircleResolution(128);
    
    fbo1.allocate(ofGetWidth() / 2, ofGetHeight(), GL_RGBA, 8);
    fbo2.allocate(ofGetWidth() / 2, ofGetHeight(), GL_RGBA, 8);
    
    cam.setNearClip(1);
    cam.setFarClip(10000);
    cam.lookAt(ofVec3f());
    cam.setPosition(0, 0, 1000);
    
    easyCam.setNearClip(1);
    easyCam.setFarClip(10000);
    easyCam.setDistance(5000);
    
    for (unsigned int i = 0; i < 100; ++i) {
        boxes.push_back(MyBox());
    }
    
    
    gui.setup();
    gui.add(rotationX.setup("rotation x", 0, -180, 180));
    gui.add(rotationY.setup("rotation y", 0, -180, 180));
    gui.add(distance.setup("distance", 1000, 0, 10000));
    gui.add(lookAtX.setup("lookAt x", 0, -1000, 1000));
    gui.add(lookAtY.setup("lookAt y", 0, -1000, 1000));
    gui.add(autoRotate.setup("auto rotate", false));
    gui.add(changeTarget.setup("change target"));
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (autoRotate) {
        rotationY = rotationY + 0.5;
    }
    
    ofQuaternion xRot(rotationX, ofVec3f(1, 0, 0));
    ofQuaternion yRot(rotationY, ofVec3f(0, 1, 0));
    ofVec3f center(0, 0, distance);
    
    cam.setPosition(center * xRot * yRot);
    
    cam.lookAt(ofVec3f(lookAtX, lookAtY, 0));
    
    
    fbo1.begin();
    {
        ofClear(0, 0);
        
        glEnable(GL_DEPTH_TEST);
        
        cam.begin();
        {
            ofPushMatrix();
            
            
            
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofLine(0, 0, 0, 200, 0, 0);
            ofPopStyle();
            
            ofPushStyle();
            ofSetColor(0, 255, 0);
            ofLine(0, 0, 0, 0, 200, 0);
            ofPopStyle();
            
            ofPushStyle();
            ofSetColor(0, 0, 255);
            ofLine(0, 0, 0, 0, 0, 200);
            ofPopStyle();
            
            for (unsigned int i = 0; i < boxes.size(); ++i) {
                boxes.at(i).draw();
            }
            
            ofPopMatrix();
        }
        cam.end();
        
        glDisable(GL_DEPTH_TEST);
    }
    fbo1.end();
    
    fbo2.begin();
    {
        ofClear(50, 255);
        
        float angle;
        ofVec3f axis;
        cam.getOrientationQuat().getRotate(angle, axis);
        
        glEnable(GL_DEPTH_TEST);
        
        easyCam.begin();
        {
            ofPushStyle();
            {
                for (unsigned int i = 0; i < boxes.size(); ++i) {
                    boxes.at(i).draw();
                }
            }
            ofPopStyle();
            
            // x axis
            ofPushMatrix();
            {
                ofRotateY(rotationY - 90);
                ofLog() << angle;
                
                ofPushStyle();
                {
                    ofNoFill();
                    ofCircle(0, 0, distance);
                }
                ofPopStyle();
            }
            ofPopMatrix();
            
            // y axis
            ofPushMatrix();
            {
                ofRotateX(-90);
                ofPushStyle();
                {
                    ofNoFill();
                    ofCircle(0, 0, distance);
                }
                ofPopStyle();
            }
            ofPopMatrix();
            
            ofPushMatrix();
            {
                ofLine(cam.getPosition(), cam.getLookAtDir() + ofVec3f(lookAtX, lookAtY, 0));
                ofLine(cam.getPosition(), cam.getPosition() + cam.getUpDir() * 500);
                ofLine(cam.getPosition(), cam.getPosition() + cam.getSideDir() * 500);
                
                ofDrawBitmapString("lookAt dir", cam.getPosition() + cam.getLookAtDir() * 500);
                ofDrawBitmapString("up dir", cam.getPosition() + cam.getUpDir() * 500);
                ofDrawBitmapString("side dir", cam.getPosition() + cam.getSideDir() * 500);
                
                ofLog() << axis;
                
                ofTranslate(cam.getPosition());
                ofRotate(angle, axis.x, axis.y, axis.z);
                
                ofPushStyle();
                {
                    ofSetColor(255, 0, 255);
                    ofFill();
                    ofDrawSphere(0, 0, 0, 10);
                    ofNoFill();
                    ofDrawBox(0, 0, 0, 100);
                }
                ofPopStyle();
            }
            ofPopMatrix();
        }
        easyCam.end();
        
        glDisable(GL_DEPTH_TEST);
    }
    fbo2.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    
    fbo1.draw(0, 0);
    fbo2.draw(ofGetWidth() / 2, 0);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
