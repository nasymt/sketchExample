//
//  dataReaderSceneParameters.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/15.
//
//

#ifndef dataReaderSceneParameters_hpp
#define dataReaderSceneParameters_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class dataReaderSceneParameters {
   public:
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load(path);
        xml->pushTag("sceneParameters");
        sceneTotal = xml->getNumTags("scene");
        cout << "sceneNum : " << sceneTotal << endl;
        for (int i = 0; i < sceneTotal; i++) {
            name.push_back(xml->getValue("scene:name", "", i));
            speed.push_back(xml->getValue("scene:speed", 1.0, i));
            elementInterval.push_back(xml->getValue("scene:elementInterval", 1.0, i));
            ratio_1.push_back(xml->getValue("scene:ratio_1", 1.0, i));
            ratio_2.push_back(xml->getValue("scene:ratio_2", 1.0, i));
        }
        xml->popTag();
        delete xml;
    }

    int sceneTotal;
    vector<string> name;
    vector<float> speed;
    vector<float> elementInterval;
    vector<float> ratio_1;
    vector<float> ratio_2;

   private:
    ofxXmlSettings *xml;
};

#endif /* dataReaderSceneParameters_hpp */
