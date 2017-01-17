//
//  sceneManagement.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/13.
//
//

#ifndef sceneManagement_hpp
#define sceneManagement_hpp

#include "ofMain.h"
#include "guiManagement.hpp"
#include "sceneUnit.hpp"
#include "sketchBaseScene.hpp"
#include "dataReaderSceneParameters.hpp"
#include "ofxXmlSettings.h"

class sceneManagement {
   public:
    void setup(int index) {
        gui = new guiManagement();
        gui->setup();

        setGuiParams(index);
        scenes[index]->setSpeed(speed[index]);
        scenes[index]->setElementInterval(elementInterval[index]);
        scenes[index]->setRatio1(ratio_1[index]);
        scenes[index]->setRatio2(ratio_2[index]);

        scenes[index]->setup();
    }

    void begin(int index) {
        setGuiParams(index);
        scenes[index]->setSpeed(speed[index]);
        scenes[index]->setElementInterval(elementInterval[index]);
        scenes[index]->setRatio1(ratio_1[index]);
        scenes[index]->setRatio2(ratio_2[index]);
        scenes[index]->begin();
    }

    void update(int index) {
        gui->update();
        updateGuiParams(index);
        if (gui->isSaveAvailable()) {
            saveXml(index);
        }
        scenes[index]->setSpeed(gui->getSpeed());
        scenes[index]->setElementInterval(gui->getElementInterval());
        scenes[index]->setRatio1(gui->getRatio1());
        scenes[index]->setRatio2(gui->getRatio2());
        scenes[index]->update();
    }
    void draw(int index) {
        ofEnableDepthTest();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        cam.begin();
        scenes[index]->draw();
        cam.end();
        ofPopMatrix();
        ofSetColor(255);
        ofDisableDepthTest();

        caption(index);
        gui->draw();
    }
    void end(int index) { scenes[index]->end(); }

    void caption(int index) { ofDrawBitmapString("scene : " + sceneName[index] + " ( " + ofToString(index + 1) + " / " + ofToString(sceneTotal) + " )", 250, 20); }

    void setGuiParams(int index) {
        gui->setSpeed(speed[index]);
        gui->setElementInterval(elementInterval[index]);
        gui->setRatio1(ratio_1[index]);
        gui->setRatio2(ratio_2[index]);
    }
    void updateGuiParams(int index){
        speed[index] = gui->getSpeed();
        elementInterval[index] = gui->getElementInterval();
        ratio_1[index] = gui->getRatio1();
        ratio_2[index] = gui->getRatio2();
    }
    

    void saveXml(int index) {
        xml = new ofxXmlSettings();
        string path = "xml/sceneParameters.xml";
        xml->load(path);
        xml->pushTag("sceneParameters");
        xml->pushTag("scene", index);
        xml->setValue("speed", speed[index]);
        xml->setValue("elementInterval", elementInterval[index]);
        xml->setValue("ratio_1", ratio_1[index]);
        xml->setValue("ratio_2", ratio_2[index]);
        xml->popTag();
        xml->popTag();
        xml->save(path);
        delete xml;
        gui->saveCompleted();
        cout << "save completed !!  speed :" << speed[index] << endl;
    }

    sceneManagement() {
        unit = new sceneUnit();
        scenes = unit->scenes;
        delete unit;

        sceneParams = new dataReaderSceneParameters();
        sceneParams->loadXml("xml/sceneParameters.xml");
        sceneTotal = sceneParams->sceneTotal;
        sceneName = sceneParams->name;
        speed = sceneParams->speed;
        elementInterval = sceneParams->elementInterval;
        ratio_1 = sceneParams->ratio_1;
        ratio_2 = sceneParams->ratio_2;
        cout << sceneName[0] << endl;
        delete sceneParams;
    };

    vector<sketchBaseScene *> scenes;

   private:
    guiManagement *gui;
    sceneUnit *unit;
    dataReaderSceneParameters *sceneParams;
    ofxXmlSettings *xml;
    ofEasyCam cam;

    int sceneTotal;
    vector<string> sceneName;
    vector<float> speed;
    vector<float> elementInterval;
    vector<float> ratio_1;
    vector<float> ratio_2;
};

#endif /* sceneManagement_hpp */
