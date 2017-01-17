//
//  polyPDFScenes.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/14.
//
//

#ifndef polyPDFScenes_hpp
#define polyPDFScenes_hpp

#include "ofMain.h"
#include "sketchBaseScene.hpp"
#include "ofxPDF.h"
#include "PolyManagementPDFVertices.hpp"
#include "simpleCounter.hpp"
#include "simplePDFVertices.hpp"

//====================================================================
//
// polyPDFScene001 [simple polyPDF Example]
//
//====================================================================
class polyPDFScene001 : public sketchBaseScene {
    void begin() {
        ofLogNotice("polyPDFScene001 :: begin");
        pdf = new ofxPDF();
        poly = new ofPolyline();
        pdf->load("pdf/example_ellipse_400px.pdf");
        polyManagement.add("pdf/example_ellipse_400px.pdf", 20);
        ofBackground(0);
    }

    void update() {
        //        for(int i=0;i<polyManagement._resamples.size();i++){
        //            polyManagement._resamples[i] =
        //        }
    }

    void draw() {
        ofSetColor(255);

        vector<vector<ofVec2f>> point = polyManagement.getVertices();
        vector<vector<ofVec2f>> point_small = polyManagement.getVertices();

        for (int i = 0; i < point.size(); i++) {
            // cout << point.size() << " : " << point[i].size() << endl;
            poly->begin();

            for (int j = 0; j < point[i].size(); j++) {
                ofSetColor(255, 0, 0);
                ofDrawCircle(point[i][j].x, point[i][j].y, 5);
                //                cout << point[i][j].x << " : " << point[i][j].y << endl;
                poly->addVertex(ofPoint(point[i][j].x, point[i][j].y));

                if (j == point[i].size() - 1) {
                    poly->addVertex(ofPoint(point[i][0].x, point[i][0].y));
                }
            }
            poly->end();
            poly->draw();
            poly->clear();
        }

        pdf->draw();
    }

    void end() {
        delete pdf;
        delete poly;
    }

   public:
   private:
    ofxPDF *pdf;
    ofPolyline *poly;
    PolyManagementPDFVertices polyManagement;
};

//====================================================================
//
// polyPDFScene002 [simple polyPDF Example]
//
//====================================================================
class polyPDFScene002 : public sketchBaseScene {
    void begin() {
        ofLogNotice("polyPDFScene001 :: begin");
        pdf = new ofxPDF();
        pdf_small = new ofxPDF();
        poly = new ofPolyline();
        counter = new simpleCounter();
        resample = 400;
        circleNum = 20;

        counter->setup(0, resample / circleNum - 1, speed);
        pdf->load("pdf/example_ellipse_400px.pdf");
        pdf_small->load("pdf/example_ellipse_100px.pdf");
        polyManagement.add("pdf/example_ellipse_400px.pdf", resample);
        polyManagement.add("pdf/example_ellipse_100px.pdf", resample);
        // ofBackground(255);
    }

    void update() {
        counter->update();
        counter->changeCountAmount(speed);
    }

    void draw() {
        ofSetColor(255);

        vector<vector<ofVec2f>> point = polyManagement.getVertices();
        vector<vector<ofVec2f>> point_small = polyManagement.getVertices();

        for (int i = 0; i < point.size(); i++) {
            // cout << point.size() << " : " << point[i].size() << endl;
            poly->begin();

            for (int j = 0; j < point[i].size(); j++) {
                if (j % (resample / circleNum) == 0) {
                    ofPushMatrix();
                    ofTranslate(point[i][j].x, point[i][j].y);
                    for (int k = 0; k < point_small.size(); k++) {
                        for (int l = 0; l < point_small[k].size(); l++) {
                            if (l % (resample / circleNum) == counter->getValue()) {
                                ofSetColor(255, 0, 0);
                                ofDrawCircle(point_small[k][l].x, point_small[k][l].y, 2);
                            }
                        }
                    }
                    ofPopMatrix();
                }
            }
            poly->end();
            poly->draw();
            poly->clear();
        }

        // pdf->draw();
    }

    void end() {
        delete pdf;
        delete poly;
    }

   public:
   private:
    ofxPDF *pdf;
    ofxPDF *pdf_small;
    ofPolyline *poly;
    PolyManagementPDFVertices polyManagement;
    simpleCounter *counter;
    int resample;
    int circleNum;

    // int counter = 0;
};

//====================================================================
//
// polyPDFScene003 [simple polyPDF Example]
//
//====================================================================
class polyPDFScene003 : public sketchBaseScene {
    void begin() {
        ofLogNotice("polyPDFScene001 :: begin");
        pdf = new ofxPDF();
        pdf_small = new ofxPDF();
        poly = new ofPolyline();
        counter = new simpleCounter();
        resample = 1000;
        circleNum = 10;

        counter->setup(0, resample / circleNum - 1, speed);
        pdf->load("pdf/example_ellipse_600px.pdf");
        pdf_small->load("pdf/example_ellipse_200px.pdf");
        polyManagement.add("pdf/example_ellipse_600px.pdf", resample);
        polyManagement.add("pdf/example_ellipse_200px.pdf", resample);
        // ofBackground(255);
    }

    void update() {
        counter->changeCountAmount(speed);
        //        counter->changeResetCount(int(resample / circleNum * elementInterval) - 1);
        //        cout << "counter : " << counter->getValue() << " : " << counter->getResetValue() << " : " << elementInterval << endl;
        counter->update();
    }

    void draw() {
        ofSetColor(255);

        vector<vector<ofVec2f>> point = polyManagement.getVertices();
        vector<vector<ofVec2f>> point_small = polyManagement.getVertices();

        if (_poly.size()) _poly.clear();
        int poly_index = 0;
        for (int i = 0; i < point.size(); i++) {
            poly->begin();

            for (int j = 0; j < point[i].size(); j++) {
                if (j % (resample / circleNum) == 0) {
                    //                    ofSetColor(255,255,0);
                    //                    ofDrawCircle(point[i][j].x, point[i][j].y, 5);

                    _poly.push_back(new ofPolyline());
                    _poly[poly_index]->begin();
                    for (int k = 0; k < point_small.size(); k++) {
                        for (int l = 0; l < point_small[k].size(); l++) {
                            if (l % (resample / circleNum) == counter->getValue()) {
                                _poly[poly_index]->addVertex(point[i][j].x, point[i][j].y);
                                _poly[poly_index]->addVertex(point_small[k][l].x, point_small[k][l].y);
                            }
                        }
                    }
                    _poly[poly_index]->end();
                    ofSetColor(255, 0, 0);
                    _poly[poly_index]->draw();
                    _poly[poly_index]->clear();
                    poly_index++;
                }
            }
            //            poly->end();
            //            ofSetColor(255, 0, 0);
            //            poly->draw();
            //            poly->clear();
        }

        // pdf->draw();
    }

    void end() {
        delete pdf;
        delete poly;
    }

   public:
   private:
    ofxPDF *pdf;
    ofxPDF *pdf_small;
    ofPolyline *poly;
    vector<ofPolyline *> _poly;
    PolyManagementPDFVertices polyManagement;
    simpleCounter *counter;
    int resample;
    int circleNum;

    // int counter = 0;
};

//====================================================================
//
// polyPDFScene004 [simple polyPDF Example]
//
//====================================================================
class polyPDFScene004 : public sketchBaseScene {
    void begin() {
        ofLogNotice("polyPDFScene004 :: begin");
        pdf = new ofxPDF();
        pdf_small = new ofxPDF();
        poly = new ofPolyline();
        counter = new simpleCounter();
        resample = 3000;
        circleNum = 150;

        counter->setup(0, resample / circleNum - 1, speed);
        pdf->load("pdf/example_ellipse_400px.pdf");
        pdf_small->load("pdf/example_ellipse_100px.pdf");
        polyManagement.add("pdf/example_ellipse_400px.pdf", resample / 2);
        polyManagement_small.add("pdf/example_ellipse_100px.pdf", resample);
        // ofBackground(255);
    }

    void update() {
        counter->update();
        counter->changeCountAmount(speed);
    }

    void draw() {
        ofSetColor(255);

        vector<vector<ofVec2f>> point = polyManagement.getVertices();
        vector<vector<ofVec2f>> point_small = polyManagement_small.getVertices();
        float scale = 1.5;

        for (int i = 0; i < point.size(); i++) {
            poly->begin();

            for (int j = 0; j < point[i].size(); j++) {
                if (j % (resample / circleNum) == 0) {
                    ofPushMatrix();
                    ofTranslate(point[i][j].x * ratio_1, point[i][j].y * ratio_1);
                    //                    ofSetColor(255, 255, 0);
                    //                    ofDrawCircle(0, 0, 5, 5);
                    for (int k = 0; k < point_small.size(); k++) {
                        //                        ofSetColor(255, 0, 0);
                        //                        ofDrawCircle(point_small[k][0].x, point_small[k][0].y, 5, 5);
                        for (int l = 0; l < point_small[k].size(); l++) {
                            if (l % (resample / circleNum) == counter->getValue()) {
                                ofSetColor(255, 255, 0);
                                ofDrawCircle(point_small[k][l].x * ratio_2 * 2, point_small[k][l].y * ratio_2 * 2, 1);
                            }
                        }
                    }
                    ofPopMatrix();
                }
            }
            poly->end();
            poly->draw();
            poly->clear();
        }

        // pdf->draw();
    }

    void end() {
        delete pdf;
        delete poly;
    }

   public:
   private:
    ofxPDF *pdf;
    ofxPDF *pdf_small;
    ofPolyline *poly;
    PolyManagementPDFVertices polyManagement;
    PolyManagementPDFVertices polyManagement_small;
    simpleCounter *counter;
    int resample;
    int circleNum;

    // int counter = 0;
};

//====================================================================
//
// polyPDFScene005 [simple polyPDF Example]
//
//====================================================================
class polyPDFScene005 : public sketchBaseScene {
    void begin() {
        ofLogNotice("polyPDFScene005 :: begin");
        pdf = new ofxPDF();
        pdf_small = new ofxPDF();
        poly = new ofPolyline();
        counter = new simpleCounter();
        resample = 3000;
        circleNum = 150;

        counter->setup(0, resample / circleNum - 1, speed);
        pdf->load("pdf/example_ellipse_400px.pdf");
        pdf_small->load("pdf/example_ellipse_100px.pdf");
        polyManagement.add("pdf/example_ellipse_400px.pdf", resample / 2);
        polyManagement_small.add("pdf/example_ellipse_100px.pdf", resample);
        // ofBackground(255);
    }

    void update() {
        counter->update();
        counter->changeCountAmount(speed);
    }

    void draw() {
        ofSetColor(255);

        vector<vector<ofVec2f>> point = polyManagement.getVertices();
        vector<vector<ofVec2f>> point_small = polyManagement_small.getVertices();
        float scale = 1.5;
        int poly_index = 0;
        if (_poly.size()) _poly.clear();

        for (int i = 0; i < point.size(); i++) {
            poly->begin();

            for (int j = 0; j < point[i].size(); j++) {
                if (j % (resample / circleNum) == counter->getValue()) {
                    _poly.push_back(new ofPolyline());
                    _poly[poly_index]->begin();
                    ofPushMatrix();
                    ofTranslate(point[i][j].x * ratio_1, point[i][j].y * ratio_1);
                    for (int k = 0; k < point_small.size(); k++) {
                        //                        ofSetColor(255, 0, 0);
                        //                        ofDrawCircle(point_small[k][0].x, point_small[k][0].y, 5, 5);
                        for (int l = 0; l < point_small[k].size(); l++) {
                            //                            if (l % (resample / circleNum) == counter->getValue()) {
                            _poly[poly_index]->addVertex(point_small[k][l].x * ratio_2 * 2, point_small[k][l].y * ratio_2 * 2);

                            //                                ofSetColor(255, 0, 0);
                            //                                ofDrawCircle(point_small[k][l].x * ratio_2 * 2, point_small[k][l].y * ratio_2 * 2, 3);
                            //                            }
                        }
                    }
                    _poly[poly_index]->end();
                    _poly[poly_index]->draw();
                    _poly[poly_index]->clear();
                    ofPopMatrix();
                }
            }
            poly->end();
            poly->draw();
            poly->clear();
        }

        // pdf->draw();
    }

    void end() {
        delete pdf;
        delete pdf_small;
        delete poly;
        delete counter;
    }

   public:
   private:
    ofxPDF *pdf;
    ofxPDF *pdf_small;
    ofPolyline *poly;
    vector<ofPolyline *> _poly;
    PolyManagementPDFVertices polyManagement;
    PolyManagementPDFVertices polyManagement_small;
    simpleCounter *counter;
    int resample;
    int circleNum;

    // int counter = 0;
};

//====================================================================
//
// simplePDFVerticesExample001 [simple polyPDF Example]
//
//====================================================================
class simplePDFVerticesExample001 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        poly = new ofPolyline();
        simplePDF->setup("pdf/example_ellipse_400px.pdf", 20);
        ofBackground(0);
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        vector<ofVec2f> point = simplePDF->getVertices();

        for (int i = 0; i < point.size(); i++) {
            poly->begin();

            ofSetColor(255, 0, 0);
            ofDrawCircle(point[i].x, point[i].y, 5);
            poly->addVertex(ofPoint(point[i].x, point[i].y));

            if (i == point.size() - 1) {
                poly->addVertex(ofPoint(point[0].x, point[0].y));
            }
        }
        poly->end();
        poly->draw();
        poly->clear();
    }

    void end() {
        delete poly;
        delete simplePDF;
    }

   public:
   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
};

#endif /* polyPDFScenes_hpp */