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
    void setup() { ofLogNotice("polylineExample001 :: setup"); }

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

    void end() { delete poly; }

   public:
    polylineExample001(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
};

//====================================================================
//
// polylineExample002 [simple addVertices Example]
//
//====================================================================
class polylineExample002 : public sketchBaseScene {
    void setup() { ofLogNotice("polylineExample002 :: setup"); }
    void begin() { ofLogNotice("polylineExample002 :: begin"); }
    void update() {
        // make a pentagon
        if (verts.size()) verts.clear();
        p.clear();
        float size = 400.f;
        float X1 = 0.125 * sqrt(10 + 2 * sqrt(5)) * size * sin(ofGetElapsedTimef());
        float X2 = 0.125 * sqrt(10 - 2 * sqrt(5)) * size * sin(ofGetElapsedTimef());
        float Y1 = 0.125 * (sqrt(5) - 1) * size * sin(ofGetElapsedTimef());
        float Y2 = 0.125 * (sqrt(5) + 1) * size * sin(ofGetElapsedTimef());
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

   public:
    polylineExample002(string name) { sceneName = name; };

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
    void begin() { p = new ofPolyline(); }
    void update() {
        //        p->clear();
        //        p->begin();
        //        p->addVertex(0,0);
        //        p->addVertex(100,0);
        p->curveTo(-300, 50);
        p->curveTo(0, -100);
        p->curveTo(400, 400);
        //        p->addVertex(200,100);
        //        p->end();
    }
    void draw() { p->draw(); }

    void end() { delete p; }

   public:
    polylineExample003(string name) { sceneName = name; };

   private:
    ofPolyline *p;
};

//====================================================================
//
// polylineExample004 [bezier example]
//
//====================================================================
class polylineExample004_bezier : public sketchBaseScene {
    void begin() { p = new ofPolyline(); }
    void update() {
        point1 = ofPoint(-500, -200);
        point2 = ofPoint(sin(ofGetElapsedTimef()) * 100, cos(ofGetElapsedTimef()) * 50 * ratio_1);
        point3 = ofPoint(200, 250);
        p1 = ofPoint(0, -200);
        p2 = ofPoint(-200, 0);
        p3 = ofPoint(0, 200);
        p4 = ofPoint(200, 0);
        curveResolution = 10 * elementInterval;

        p->clear();
        p->begin();
        //        p->addVertex(point1);
        //        p->addVertex(point2);
        //        p->addVertex(point3);
        //        p->bezierTo(point1, point2, point3, curveResolution);
        //        for (int i = 0; i < 10; i++) {
        //            p->bezierTo(point3, point2 - ofPoint(5 * i * ratio_2, 5 * i * ratio_2), point1, curveResolution);
        //            p->bezierTo(point2, point3 - ofPoint(20, 20), point1, curveResolution);
        //        }

        p->addVertex(p1);
        // p->addVertex(p2);

        p->bezierTo(p1, p2, p3, curveResolution);
        p->bezierTo(p3, p4, p1, curveResolution);

        p->end();
    }
    void draw() {
        p->draw();
        //        ofDrawCircle(point1.x, point1.y, 2);
        //        ofDrawCircle(point2.x, point2.y, 2);
        //        ofDrawCircle(point3.x, point3.y, 2);
        ofDrawCircle(p1.x, p1.y, 2);
        ofDrawCircle(p2.x, p2.y, 2);
        ofDrawCircle(p3.x, p3.y, 2);
        ofDrawCircle(p4.x, p4.y, 2);
    }

    void end() { delete p; }

   public:
    polylineExample004_bezier(string name) { sceneName = name; };

   private:
    ofPolyline *p;
    ofPoint point1;
    ofPoint point2;
    ofPoint point3;
    ofPoint p1, p2, p3, p4;
    int curveResolution = 20;
};

//====================================================================
//
// polylineExample005_curveTo [curveTo example]
//
//====================================================================
class polylineExample005_curveTo : public sketchBaseScene {
    void begin() { p = new ofPolyline(); }
    void update() {
        point.push_back(ofPoint(-400, -200));
        point.push_back(ofPoint(-200, -100));
        point.push_back(ofPoint(100, 200));
        point.push_back(ofPoint(300, 0));
        point.push_back(ofPoint(350, -200));

        curveResolution = 10 * elementInterval;

        p->clear();
        p->begin();

        for (int i = 0; i < point.size(); i++) {
            p->curveTo(point[i],curveResolution);
        }

        //        for (int i = 0; i < 10; i++) {
        //            p->curveTo(ofPoint(sin(360 / 20 * i + ofGetElapsedTimef()) * 200, cos(360 / 20 * i + ofGetElapsedTimef()) * 200));
        //        }

        //        float angle = 0;
        //        while (angle < TWO_PI ) {
        //            p->curveTo(100*cos(angle), 0, 100*sin(angle));
        //            p->curveTo(300*cos(angle), 300, 300*sin(angle));
        //            angle += TWO_PI / 30;
        //        }

        //        float angle = 0;
        //        while (angle < TWO_PI ) {
        //            p->curveTo( ofPoint(100*cos(angle), 100*sin(angle)));
        //            p->curveTo( ofPoint(300*cos(angle), 300*sin(angle)));
        //            angle += TWO_PI / 30;
        //        }

        p->end();
    }
    void draw() {
        p->draw();
        //        ofDrawCircle(point1.x, point1.y, 2);
        //        ofDrawCircle(point2.x, point2.y, 2);
        //        ofDrawCircle(point3.x, point3.y, 2);
        ofSetColor(255, 0, 0);
        for (int i = 0; i < point.size(); i++) {
            ofDrawCircle(point[i].x, point[i].y, 5);
        }
    }

    void end() { delete p; }

   public:
    polylineExample005_curveTo(string name) { sceneName = name; };

   private:
    ofPolyline *p;
    vector<ofPoint> point;
    ofPoint p1, p2, p3, p4, p5;
    int curveResolution = 20;
};

#endif /* polylineExample_hpp */
