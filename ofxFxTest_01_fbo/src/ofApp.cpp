#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // video grabber
    videoGrabber.initGrabber(width , height);

    // fbo
    fbo.allocate(width, height);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    // ofxFx
    glow.allocate(width, height);
    bloom.allocate(width, height);
    
    // listener
    radius.addListener(this, &ofApp::radiusChanged);
    
    // gui
    panel.setup("GUI", "settings.xml", 0, 0);
    panel.add(radius.set("radius", 3, 0, 100));
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    // video grabber
    videoGrabber.update();
    
    // ofxFx
    glow.update();
    bloom.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // fbo
    fbo.begin();
    videoGrabber.draw(0, 0, videoGrabber.getWidth(), videoGrabber.getHeight());
    fbo.end();
    fbo.draw(0, 0, width, height);
    
    // glow
    glow.setTexture(fbo);
    glow.draw(width, 0, width, height);
    
    // bloom
    bloom.setTexture(fbo);
    bloom.draw(0, height, width, height);
    
    // gui
    panel.draw();
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        default:
            break;
    }
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::radiusChanged(float &radius){
    glow.setRadius(radius);
}
