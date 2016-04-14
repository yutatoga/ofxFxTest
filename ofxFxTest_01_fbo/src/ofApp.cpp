#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // video grabber
    videoGrabber.initGrabber(width , height);

    // fbo
    fbo.allocate(width, height, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    fboMix.allocate(width, height, GL_RGBA);
    fboMix.begin();
    ofClear(255, 255, 255, 0);
    fboMix.end();
    
    // ofxFx
    glow.allocate(width, height);
    bloom.allocate(width, height);
    glowMix.allocate(width, height);
    bloomMix.allocate(width, height);
    
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
    glowMix.update();
    bloomMix.update();
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
    
    // glow & bloom
    glowMix.setTexture(fbo);
    fboMix.begin();
    ofBackground(0);
    glowMix.draw(0, 0, width, height);
    fboMix.end();
    bloomMix.setTexture(fboMix);
    bloomMix.draw(width, height, width, height);
    
    // gui
    panel.draw();
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
    
    ofVec2f bitMapStringOrigin(-5, 8);

    ofDrawBitmapStringHighlight("fbo without ofxFx", 0-bitMapStringOrigin.x , height-bitMapStringOrigin.y, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxGlow",  width-bitMapStringOrigin.x, height-bitMapStringOrigin.y, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxGlow & ofxBloom", width-bitMapStringOrigin.x , height*2-bitMapStringOrigin.y, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxBloom", 0-bitMapStringOrigin.x, height*2-bitMapStringOrigin.y, ofColor::white, ofColor::black);
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
    glowMix.setRadius(radius);
}
