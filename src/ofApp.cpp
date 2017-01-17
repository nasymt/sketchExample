#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    config = new dataReaderConfig();
    config->loadXml("xml/config.xml");
    sceneIndex = config->start_scene;
    ofBackground(0);

    cout << "size : " << scene.scenes.size() << endl;
    for(int i=0;i<scene.scenes.size();i++){
        scene.setup(i);
    }
    scene.begin(sceneIndex);
    bHideGui = false;
}

//--------------------------------------------------------------
void ofApp::update() {
    scene.update(sceneIndex);
}

//--------------------------------------------------------------
void ofApp::draw() {
    scene.draw(sceneIndex);

    if (!bHideGui) {
        ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()), 20, ofGetHeight() - 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_UP) {
        if(sceneIndex < scene.scenes.size()-1){
            scene.end(sceneIndex);
            sceneIndex++;
            scene.begin(sceneIndex);
        }
    } else if (key == OF_KEY_DOWN) {
        if (sceneIndex > 0) {
            scene.end(sceneIndex);
            sceneIndex--;
            scene.begin(sceneIndex);
        }
    } else if (key == 'h') {
        if (bHideGui) {
            bHideGui = false;
        } else {
            bHideGui = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
