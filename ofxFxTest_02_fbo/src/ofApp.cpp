#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // Setup box positions
    for (unsigned i = 0; i < NUM_BOXES; ++i){
        posns.push_back(ofVec3f(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300)));
        cols.push_back(ofColor::fromHsb(255 * i / (float)NUM_BOXES, 255, 255, 255));
    }
    boxMesh = ofMesh::box(20, 20, 20);

    light.setPosition(1000, 1000, 2000);
    
    // fbo
    fbo.allocate(width, height, GL_RGBA);
    fbo2.allocate(width, height, GL_RGBA);
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();
    
    fbo2.begin();
    ofClear(0, 0, 0, 0);
    fbo2.end();
    
    // ofxFx
    glow.allocate(width, height);
    bloom.allocate(width, height);
    glow2.allocate(width, height);
    bloom2.allocate(width, height);
    
    // listener
    radius.addListener(this, &ofApp::radiusChanged);
    
    // gui
    panel.setup("GUI", "settings.xml", 0, 0);
    panel.add(radius.set("radius", 3, 0, 100));
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    // ofxFx
    glow.update();
    bloom.update();
    glow2.update();
    bloom2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // fbo
    // draw boxes
    fbo.begin();
    ofEnableDepthTest();
    glPushAttrib(GL_ENABLE_BIT);
    ofEnableLighting();
    light.enable();
    cam.begin();
    ofBackground(0);
    for (unsigned i = 0; i < posns.size(); ++i){
        ofSetColor(cols[i]);
        ofPushMatrix();
        ofTranslate(posns[i]);
        boxMesh.draw();
        ofPopMatrix();
    }
    cam.end();
    light.disable();
    ofDisableLighting();
    glPopAttrib();
    ofDisableDepthTest();
    fbo.end();

  
    ofSetColor(255, 255, 255, 255);
    fbo.draw(0, 0, width, height);

    // glow
    glow.setTexture(fbo);
    glow.draw(width, 0, width, height);
    
    // bloom
    bloom.setTexture(fbo);
    bloom.draw(0, height, width, height);
    
    // glow & bloom
    glow2.setTexture(fbo);
    fbo2.begin();
    ofBackground(0);
    glow2.draw(0, 0, width, height);
    fbo2.end();
    bloom2.setTexture(fbo2);
    bloom2.draw(width, height, width, height);
    
    // gui
    panel.draw();
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
    
    ofDrawBitmapStringHighlight("fbo without ofxFx", 0 , height, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxGlow",  width, height, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxGlow & ofxBloom", width , height*2, ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("ofxBloom", 0 , height*2, ofColor::white, ofColor::black);
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
    glow2.setRadius(radius);
}
