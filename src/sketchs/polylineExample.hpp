//
//  polylineExample.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/13.
//
//

#ifndef polylineExample_hpp
#define polylineExample_hpp

#include "ofMain.h"
#include "sketchBaseScene.hpp"

//====================================================================
//
// polylineExample001 [simple addVertex Example]
//
//====================================================================
class polylineExample001 : public sketchBaseScene {
   public:
    void setup() {
        ofLogNotice("polylineExample001 :: setup");
    }

    void begin() {
        poly = new ofPolyline();
        ofLogNotice("polylineExample001 :: begin");
        ofBackground(0);
    }

    void update() {
        poly->clear();
        poly->begin();
        poly->addVertex(sin(ofGetElapsedTimef() * speed) * 300, cos(ofGetElapsedTimef() * speed) * 300);
        poly->addVertex(0, 0);
        poly->close();
    }

    void draw() {
        ofSetColor(255, 0, 0);
        // ofDrawEllipse(0, 0, 200, 200);
        poly->draw();
    }
    
    void end(){
        delete poly;
    }

   private:
    ofPolyline *poly;
};

//====================================================================
//
// polylineExample002 [simple addVertices Example]
//
//====================================================================
class polylineExample002 : public sketchBaseScene {
   public:
    void setup() { ofLogNotice("polylineExample002 :: setup"); }
    void begin() {
        ofLogNotice("polylineExample002 :: begin");
    }
    void update() {
        // make a pentagon
        if(verts.size()) verts.clear();
        p.clear();
        float size = 400.f;
        float X1 = 0.125*sqrt(10 + 2*sqrt(5)) * size * sin(ofGetElapsedTimef());
        float X2 = 0.125*sqrt(10 - 2*sqrt(5)) * size * sin(ofGetElapsedTimef());
        float Y1 = 0.125*(sqrt(5) - 1) * size * sin(ofGetElapsedTimef());
        float Y2 = 0.125*(sqrt(5) + 1) * size * sin(ofGetElapsedTimef());
        verts.push_back(ofPoint(0, -0.5 * size * sin(ofGetElapsedTimef())));
        verts.push_back(ofPoint(-X1, -Y1));
        verts.push_back(ofPoint(-X2, Y2));
        verts.push_back(ofPoint(X2, Y2));
        verts.push_back(ofPoint(X1, -Y1));
        p.addVertices(verts);
    }
    void draw() {
        ofSetColor(0, 255, 0);
        p.draw();
    }

   private:
    vector<ofPoint> verts;
    ofPolyline p;

};


//====================================================================
//
// polylineExample003
//
//====================================================================
class polylineExample003 : public sketchBaseScene {
   public:
    void begin() {
        p = new ofPolyline();
    }
    void update() {
//        p->clear();
//        p->begin();
//        p->addVertex(0,0);
//        p->addVertex(100,0);
        p->curveTo(-300,50);
        p->curveTo(0,-100);
        p->curveTo(400,400);
//        p->addVertex(200,100);
//        p->end();
        
        
    }
    void draw() {
        p->draw();
    }
    
    void end(){
        delete p;
    }

   private:
    ofPolyline *p;
};

#endif /* polylineExample_hpp */
