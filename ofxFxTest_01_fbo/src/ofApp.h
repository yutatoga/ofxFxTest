#pragma once

#include "ofMain.h"
#include "ofxGlow.h"
#include "ofxBloom.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void radiusChanged(float &radius);
    
    const int width = 640;
    const int height = 480;
    ofVideoGrabber  videoGrabber;
    ofFbo fbo, fboMix;
    ofxGlow glow, glowMix;
    ofxBloom bloom, bloomMix;
    ofxPanel panel;
    ofParameter<float> radius;
};
