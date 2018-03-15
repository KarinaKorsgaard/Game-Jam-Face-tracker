#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	cam.initGrabber(1280, 720);
    ofBackground(0);
	tracker.setup();

    for(int i = 0; i< 1000; i++){
        Particle p = *new Particle;
        p.setup();
        particles.push_back(p);
    }
    eyeL.load("cutout/eyeL.png");
    eyeR.load("cutout/eyeR.png");
    
    mouthDown.load("cutout/mouthLow.png");
    mouthUp.load("cutout/mouthUp.png");
    nose.load("cutout/nose.png");
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
    
    for(int i = 0 ; i<particles.size();i++){
       // particles[i].update(tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH));
    }
    
}

void ofApp::draw() {
    if(ofGetKeyPressed()) {
//        ofSetColor(255);
//        ofMesh m = tracker.getImageMesh();
//        mesh.addIndex(0);
//        mesh.addIndex(1);
//        mesh.addIndex(2);
//        mesh.addIndex(3);
//
//        mesh.addTexCoord(ofVec2f(0,0));
//        mesh.addTexCoord(ofVec2f(0, 100));
//        mesh.addTexCoord(ofVec2f(100, 100));
//        mesh.addTexCoord(ofVec2f(100, 0));
//
//        img.bind();
//        tracker.getImageMesh().draw();
//        img.unbind();
//
        //ofSetColor(255, 32);
        //ofSetLineWidth(1);
        //tracker.getImageMesh().drawWireframe();
        //tracker.getImageMesh().drawFaces();
        //tracker.draw(true);
        
        
    }
    ofNoFill();
   // tracker.getImageMesh().drawWireframe();
   // tracker.draw(true);
//
//    ofSetColor(255);
//    ofSetLineWidth(2);
//    ofPushStyle();
//    ofNoFill();
//    ofSetColor(255);
//    //overlay.draw(tracker);
//    ofPopStyle();
//    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
//    ofSetColor(255,0,0);
//    tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH).draw();
    ofPoint eyeLeft = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D();
    ofPoint eyeRight = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D();
    ofPoint mouth = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH).getCentroid2D();
    
    ofPolyline noseP;
    float nostrilWidth = .06;
    noseP.addVertex(tracker.getImagePoint(31).getInterpolated(tracker.getImagePoint(4), nostrilWidth));
    noseP.addVertex(tracker.getImagePoint(31));
    noseP.addVertex(tracker.getImagePoint(32));
    noseP.addVertex(tracker.getImagePoint(33));
    noseP.addVertex(tracker.getImagePoint(34));
    noseP.addVertex(tracker.getImagePoint(35));
    noseP.addVertex(tracker.getImagePoint(35).getInterpolated(tracker.getImagePoint(12), nostrilWidth));
    ofPoint nosePoint = noseP.getCentroid2D();
    
    float mouthopenness = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT)*20.f;
    
    int w = eyeL.getWidth();
    int h = eyeL.getHeight();
    eyeL.draw(eyeLeft - ofPoint(w/2+20,h), w,h);
    
    w = eyeR.getWidth();
    h = eyeR.getHeight();
    eyeR.draw(eyeRight - ofPoint(w/2-20,h), w,h);
    
    w = mouthUp.getWidth();
    h = mouthUp.getHeight();
    mouthUp.draw(mouth - ofPoint(w/2,h/2), w,h);
    
    w = mouthDown.getWidth();
    h = mouthDown.getHeight();
    mouthDown.draw(mouth + ofPoint(-w/2,mouthopenness + mouthUp.getHeight()/2 - w/3), w, h);
    
    w = nose.getWidth();
    h = nose.getHeight();
    nose.draw(nosePoint + ofPoint(-w/2,-h), w*1.2, h*1.2);
    
    for(auto& p: particles){
    //    p.draw();
    }
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
