#pragma once

#include "ofMain.h"
#include "sceneManagement.hpp"
#include "guiManagement.hpp"
#include "dataReaderConfig.hpp"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

   private:
    dataReaderConfig *config;
    sceneManagement scene;
    guiManagement gui;
    bool bHideGui;
    int sceneIndex;
};
