//
//  dataReaderSceneList.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/17.
//
//

#ifndef dataReaderSceneList_hpp
#define dataReaderSceneList_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class dataReaderSceneList {
   public:
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load(path);

        xml->pushTag("sceneList");
        sceneListNum = xml->getNumTags("scene");
        for (int i = 0; i < sceneListNum; i++) {
            cout << "scenelist : " << xml->getValue("scene:path", "", i) << endl;
            string tmp = xml->getValue("scene:path","",i);
            scene_path.push_back(tmp);
        }
        xml->popTag();
        delete xml;
    }

    int sceneListNum;
    vector<string> scene_path;

   private:
    ofxXmlSettings *xml;
};

#endif /* dataReaderSceneList_hpp */
