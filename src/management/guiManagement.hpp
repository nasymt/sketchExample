//
//  guiManagement.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/13.
//
//

#ifndef guiManagement_hpp
#define guiManagement_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "sketchBaseScene.hpp"

class guiManagement {
   public:
    void setup() {
        gui.setup();
        //        gui.setSize(300,114);
        gui.add(speed.setup("speed", 1.0, 0.0, 10.0));
        gui.add(elementInterval.setup("elementInterval", 1.0, 0.0, 10.0));
        gui.add(ratio_1.setup("ratio 1", 1.0, 0.0, 10.0));
        gui.add(ratio_2.setup("ratio 2", 1.0, 0.0, 10.0));
        gui.add(save.setup("save"));
        gui.add(drawAxis.setup("drawAxis", false));
    }

    void update() {
        if (save) {
            saveAvailable = true;
        }
    }

    void draw() { gui.draw(); }

    void reset() {
        speed = 1.0;
        elementInterval = 1.0;
    }

    inline float getSpeed() { return speed; }
    inline float getElementInterval() { return elementInterval; }
    inline float getRatio1() { return ratio_1; };
    inline float getRatio2() { return ratio_2; };
    inline bool getDrawAxis() { return drawAxis; };

    inline void setSpeed(float _speed) { speed = _speed; }
    inline void setElementInterval(float _elementInterval) { elementInterval = _elementInterval; }
    inline void setRatio1(float _ratio) { ratio_1 = _ratio; }
    inline void setRatio2(float _ratio) { ratio_2 = _ratio; }

    bool isSaveAvailable() {
        if (saveAvailable) {
            return true;
        } else {
            return false;
        }
    };
    void saveCompleted() { saveAvailable = false; }

   private:
    ofxPanel gui;
    ofxFloatSlider speed;
    ofxFloatSlider elementInterval;
    ofxFloatSlider ratio_1;
    ofxFloatSlider ratio_2;
    ofxButton save;
    ofxToggle drawAxis;
    sketchBaseScene baseScene;
    bool saveAvailable;
};

#endif /* guiManagement_hpp */
