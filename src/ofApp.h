#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"
#include "FaceOverlay.h"
class Particle {
public:
    ofVec2f pos, vel, acc;
    float r = 1;
    float red = 255;
    ofPolyline l;
    
    void setup(){
        pos = ofVec2f(ofRandom(20,100),ofRandom(20,100));
        vel = ofVec2f(ofRandom(-1,1),ofRandom(-1,1));
        acc = ofVec2f(1.);
    }
    ofVec2f force(ofVec2f a, ofVec2f pos){
        
        ofVec2f d = (a - pos);
        float dist = d.length() * 0.1;
        ofVec2f d_norm = d/dist;
        dist = MAX(0.1, dist);
        
        ofVec2f Fgravity = d_norm / (dist*dist) ;
        
        return Fgravity;
        
    }
    void update(ofPolyline p){
        
        float drag = 0.3f;
        ofVec2f F_gravity = 80.*force(p.getCentroid2D(),pos);
        
        
        float vel_length = vel.length();
        ofVec2f vecNormalized = vel / vel_length;
        ofVec2f F_drag = - vel_length * vel_length * vecNormalized * 0.5 * drag;
        ofVec2f F = F_drag + F_gravity ;
        vel += F ;
//        pos.x = pos.x > ofGetWidth() ? -10 : pos.x;
//        pos.x = pos.x < 0 ? ofGetWidth()+10 : pos.x;
//        pos.y = pos.y > ofGetHeight() ? -10 : pos.y;
//        pos.y = pos.y < 0 ? ofGetHeight()+10 : pos.y;
        
        //pos.z = pos.z < -10 ? 10 : pos.z;
        //pos.z = pos.z > 10 ? -10 : pos.z;
        
 
        pos+=vel ;
        l = p;
    }
    void draw(){
        ofSetColor(r,255,255);
        ofDrawCircle(pos,r);
        l.draw();
    }
private:
};
class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    FaceOverlay overlay;
    
    ofMesh mesh;
    ofTexture img;
    vector<Particle>particles;
    
    ofImage eyeL, eyeR, mouthUp, mouthDown, nose;
};
