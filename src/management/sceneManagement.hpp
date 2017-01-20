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
#include "dataReaderSceneList.hpp"
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
        scenes[index]->setTracingResample(tracing_resample[index]);
        scenes[index]->setTracingPath(tracing_path[index]);

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
//        scenes[index]->setSpeed(gui->getSpeed());
//        scenes[index]->setElementInterval(gui->getElementInterval());
//        scenes[index]->setRatio1(gui->getRatio1());
//        scenes[index]->setRatio2(gui->getRatio2());
        updateSceneParams(index);
        scenes[index]->update();
    }
    void draw(int index) {
        ofEnableDepthTest();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        cam.begin();
        scenes[index]->draw();
        if (gui->getDrawAxis()) {
            ofDrawAxis(100);
        }
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
//        gui->setTracingResample(tracing_resample[index]);
//        gui->setTracingPath(tracing_path[index]);
    }
    void updateGuiParams(int index) {
        speed[index] = gui->getSpeed();
        elementInterval[index] = gui->getElementInterval();
        ratio_1[index] = gui->getRatio1();
        ratio_2[index] = gui->getRatio2();
    }
    
    void updateSceneParams(int index){
        scenes[index]->setSpeed(gui->getSpeed());
        scenes[index]->setElementInterval(gui->getElementInterval());
        scenes[index]->setRatio1(gui->getRatio1());
        scenes[index]->setRatio2(gui->getRatio2());
    }

    void saveXml(int index) {
        xml = new ofxXmlSettings();
//        string path = "xml/sceneParameters.xml";
//        xml->load(path);
        xml->load(sceneList_path[index]);
        xml->pushTag("sceneParameters");
        xml->pushTag("scene", index);
        xml->setValue("speed", speed[index]);
        xml->setValue("elementInterval", elementInterval[index]);
        xml->setValue("ratio_1", ratio_1[index]);
        xml->setValue("ratio_2", ratio_2[index]);
        xml->popTag();
        xml->popTag();
        xml->save(sceneList_path[index]);
        delete xml;
        gui->saveCompleted();
        cout << "save completed !!  speed :" << speed[index] << endl;
    }

    sceneManagement() {
        vector<sketchBaseScene *> tmp_scenes;
        unit = new sceneUnit();
         tmp_scenes = unit->scenes;
        //scenes = unit->scenes;
        delete unit;

        sceneList = new dataReaderSceneList();
        sceneList->loadXml("xml/sceneList.xml");
        int sceneListNum = sceneList->sceneListNum;
        cout << "sceneManagement " << sceneListNum << endl;

        for (int i = 0; i < sceneListNum; i++) {
            sceneParams = new dataReaderSceneParameters();
            sceneParams->loadXml(sceneList->scene_path[i]);
            for (int j = 0; j < sceneParams->name.size(); j++) {
                for (int k = 0; k < tmp_scenes.size(); k++) {
                    cout << sceneParams->name[j] << " : " << tmp_scenes[k]->sceneName << endl;
                    if (sceneParams->name[j] == tmp_scenes[k]->sceneName) {
                        sceneList_path.push_back(sceneList->scene_path[i]);
                        scenes.push_back(tmp_scenes[k]);
                        sceneName.push_back(sceneParams->name[j]);
                        speed.push_back(sceneParams->speed[j]);
                        elementInterval.push_back(sceneParams->elementInterval[j]);
                        ratio_1.push_back(sceneParams->ratio_1[j]);
                        ratio_2.push_back(sceneParams->ratio_2[j]);
                        bTracing.push_back(sceneParams->bTracing[j]);
                        tracing_resample.push_back(sceneParams->tracing_resample[j]);
                        tracing_path.push_back(sceneParams->tracing_path[j]);
//                        cout << "sceneName : " << scenes[k]->sceneName << endl;
                        break;
                    }
                }
                cout << "--------------" << endl;
            }
            delete sceneParams;
        }
        sceneTotal = scenes.size();

        //        sceneParams = new dataReaderSceneParameters();
        //        sceneParams->loadXml("xml/sceneParameters.xml");
        //        sceneTotal = sceneParams->sceneTotal;
        //        sceneName = sceneParams->name;
        //        speed = sceneParams->speed;
        //        elementInterval = sceneParams->elementInterval;
        //        ratio_1 = sceneParams->ratio_1;
        //        ratio_2 = sceneParams->ratio_2;
        //        delete sceneParams;
    };

    vector<sketchBaseScene *> scenes;

   private:
    guiManagement *gui;
    sceneUnit *unit;
    dataReaderSceneParameters *sceneParams;
    dataReaderSceneList *sceneList;
    ofxXmlSettings *xml;
    ofEasyCam cam;

    int sceneTotal;
    vector<string> sceneName;
    vector<string> sceneList_path;
    vector<float> speed;
    vector<float> elementInterval;
    vector<float> ratio_1;
    vector<float> ratio_2;
    vector<bool> bTracing;
    vector<int> tracing_resample;
    vector<string> tracing_path;
};

#endif /* sceneManagement_hpp */
