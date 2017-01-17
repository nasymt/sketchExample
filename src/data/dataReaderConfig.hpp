//
//  dataReaderConfig.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/14.
//
//

#ifndef dataReaderConfig_hpp
#define dataReaderConfig_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class dataReaderConfig {
   public:
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load(path);
        xml->pushTag("config");
        start_scene = xml->getValue("start_scene", 0);
        xml->popTag();

        delete xml;
    }

    int start_scene;

   private:
    ofxXmlSettings *xml;
};

#endif /* dataReaderConfig_hpp */
