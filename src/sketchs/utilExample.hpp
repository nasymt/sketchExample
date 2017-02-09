//
//  utilExample.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/20.
//
//

#ifndef utilExample_hpp
#define utilExample_hpp

#include "ofMain.h"

//====================================================================
//
// noiseExample001
//
//====================================================================
class noiseExample001 : public sketchBaseScene {
    void begin() {
        poly = new ofPolyline();
        ofBackground(0);
        vert_num = 50;
        amount = 100;
        for (int i = 0; i < vert_num; i++) {
            noise.push_back(ofPoint(ofNoise(i) * amount - amount, ofNoise(i + 1) * amount - amount, 0));
            vertices.push_back(ofPoint(1280 / vert_num * i - 640 + noise[i].x, noise[i].y, 0));
        }
    }

    void update() {
        amount = 100 * ratio_1;
        for (int i = 0; i < vert_num; i++) {
            noise[i] = ofPoint(0, ofNoise((i + 1.1) * elementInterval * 0.1) * amount - amount / 2, 0);
            vertices[i] = ofPoint(1280 / vert_num * i - 640 + noise[i].x, noise[i].y, 0);
        }
    }
    void draw() {
        poly->clear();
        poly->begin();
        for (int i = 0; i < vertices.size(); i++) {
            poly->addVertex(vertices[i]);
            ofSetColor(255, 255, 0);
            ofDrawCircle(vertices[i].x, vertices[i].y, 2, 2);
        }
        poly->end();
        ofSetColor(255, 0, 0);
        poly->draw();
    }

    void end() { delete poly; }

   public:
    noiseExample001(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    vector<ofPoint> vertices;
    vector<ofPoint> noise;
    float amount;
    int vert_num;
};

#endif /* utilExample_hpp */
