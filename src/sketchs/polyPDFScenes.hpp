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
#include "QuaternionManagement.hpp"
#include "easingManagement.hpp"

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
    polyPDFScene001(string name) { sceneName = name; };

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
        ofLogNotice("polyPDFScene002 :: begin");
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
        delete pdf_small;
        delete poly;
        delete counter;
    }

   public:
    polyPDFScene002(string name) { sceneName = name; };

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
        ofLogNotice("polyPDFScene003:: begin");
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
        delete pdf_small;
        delete poly;
        //        delete _poly;
        delete counter;
    }

   public:
    polyPDFScene003(string name) { sceneName = name; };

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
        //        pdf = new ofxPDF();
        //        pdf_small = new ofxPDF();
        poly = new ofPolyline();
        counter = new simpleCounter();
        simplePDF = new simplePDFVertices();
        simplePDF2 = new simplePDFVertices();
        resample = 3000;
        circleNum = 150;

        counter->setup(0, resample / circleNum - 1, speed);

        //        simplePDF->setup(tracing_path, resample / 2);
        simplePDF->setup("pdf/example_ellipse_400px.pdf", tracing_resample / 2);
        simplePDF2->setup(tracing_path, tracing_resample);

        //        pdf->load("pdf/example_ellipse_400px.pdf");
        //        pdf_small->load("pdf/example_ellipse_100px.pdf");
        //        polyManagement.add("pdf/example_ellipse_400px.pdf", resample / 2);
        //        polyManagement_small.add("pdf/example_ellipse_100px.pdf", resample);
    }

    void update() {
        counter->update();
        counter->changeCountAmount(speed);
    }

    void draw() {
        ofSetColor(255);

        vector<ofPoint> point = simplePDF->getVertices();
        vector<ofPoint> point2 = simplePDF2->getVertices();
        float scale = 1.5;

        for (int i = 0; i < point.size(); i++) {
            poly->begin();
            if (i % (resample / circleNum) == 0) {
                ofPushMatrix();
                ofTranslate(point[i].x * ratio_1, point[i].y * ratio_1);
                for (int j = 0; j < point2.size(); j++) {
                    if (j % (resample / circleNum) == counter->getValue()) {
                        ofSetColor(255, 255, 0);
                        ofDrawCircle(point2[j].x * ratio_2 * 2, point2[j].y * ratio_2 * 2, 1);
                    }
                }
                ofPopMatrix();
            }
            poly->end();
            poly->draw();
            poly->clear();
        }
    }

    void end() {
        //        delete pdf;
        //        delete pdf_small;
        delete poly;
        delete counter;
        delete simplePDF;
    }

   public:
    polyPDFScene004(string name) { sceneName = name; };

   private:
    //    ofxPDF *pdf;
    //    ofxPDF *pdf_small;
    ofPolyline *poly;
    //    PolyManagementPDFVertices polyManagement;
    //    PolyManagementPDFVertices polyManagement_small;
    simplePDFVertices *simplePDF;
    simplePDFVertices *simplePDF2;
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
    polyPDFScene005(string name) { sceneName = name; };

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
// polyPDFScene006 [simple Quaternion Example]
//
//====================================================================
class polyPDFScene006 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        simplePDF2 = new simplePDFVertices();
        poly = new ofPolyline();
        simplePDF->setup("pdf/example_ellipse_400px.pdf", 20);
        simplePDF2->setup("pdf/example_ellipse_400px.pdf", 20);
        ofBackground(0);

        if (vertices.size()) vertices.clear();

        //        simplePDF->rotate(0,0,0);
        vertices = simplePDF->getVertices();
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        for (int i = 0; i < vertices.size(); i++) {
            poly->begin();

            //            ofSetColor(255, 0, 0);
            //            ofDrawBox(vertices[i].x, vertices[i].y, vertices[i].z, 5);
            for (int j = 0; j < vertices.size(); j++) {
                ofPoint transPoint = ofPoint(vertices[i].x, vertices[i].y, vertices[i].z);

                ofSetColor(255, 255, 0);
                ofDrawBox(transPoint.x, transPoint.y, transPoint.z, 5);
                ofSetColor(255, 0, 0);
                //                simplePDF2->rotate(j, 0, 0, 360 / vertices.size() * i);
                //                simplePDF2->rotate(sin(ofGetElapsedTimef())*360, 0, 0);
                ofPoint vert2 = simplePDF2->getVertices(j);
                ofPoint point = (vert2 * ratio_1) + transPoint;
                ofPushMatrix();
                ofTranslate(point.x, point.y, point.z);
                ofDrawAxis(10);
                ofPopMatrix();
                ofDrawBox(point.x, point.y, point.z, 5);
            }

            poly->addVertex(ofPoint(vertices[i].x, vertices[i].y, vertices[i].z));
        }
        poly->end();
        poly->draw();
        poly->clear();
    }

    void end() {
        delete poly;
        delete simplePDF;
        delete simplePDF2;
    }

   public:
    polyPDFScene006(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    simplePDFVertices *simplePDF2;
    vector<ofPoint> vertices;
    vector<vector<ofPoint>> vertices2;
};

//====================================================================
//
// polyPDFScene007 [simple Quaternion Example]
//
//====================================================================
class polyPDFScene007 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        simplePDF2 = new simplePDFVertices();
        poly = new ofPolyline();
        simplePDF->setup("pdf/example_rect_1.pdf", tracing_resample);
        simplePDF2->setup("pdf/example_rect_1.pdf", tracing_resample);
        ofBackground(0);

        if (vertices.size()) vertices.clear();

        vertices = simplePDF->getVertices();
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        for (int i = 0; i < vertices.size(); i++) {
            poly->begin();

            //            ofSetColor(255, 0, 0);
            //            ofDrawBox(vertices[i].x, vertices[i].y, vertices[i].z, 5);
            for (int j = 0; j < vertices.size(); j++) {
                ofPoint transPoint = ofPoint(vertices[i].x, vertices[i].y, vertices[i].z);

                ofSetColor(255, 255, 0);
                ofDrawBox(transPoint.x, transPoint.y, transPoint.z, 5);
                ofSetColor(255, 0, 0);
                //                simplePDF2->rotate(j, 0, 0, 360 / vertices.size() * i);
                //                simplePDF2->rotate(sin(ofGetElapsedTimef())*360, 0, 0);
                ofPoint vert2 = simplePDF2->getVertices(j);
                ofPoint point = (vert2 * ratio_1) + transPoint;
                ofPushMatrix();
                //                simplePDF->rotate(i, 0, 360 / tracing_resample * i, 0);
                //                vertices[i] = simplePDF->getVertice()[i];
                //                ofRotateZ(360 / tracing_resample * i);
                ofRotateZ(100 * elementInterval);
                ofTranslate(point.x, point.y, point.z);
                //                ofDrawAxis(10);
                //                ofDrawBox(point.x, point.y, point.z, 5);
                ofDrawBox(0, 0, 0, 5);

                ofPopMatrix();
            }

            poly->addVertex(ofPoint(vertices[i].x, vertices[i].y, vertices[i].z));
        }
        poly->end();
        poly->draw();
        poly->clear();
    }

    void end() {
        delete poly;
        delete simplePDF;
        delete simplePDF2;
    }

   public:
    polyPDFScene007(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    simplePDFVertices *simplePDF2;
    vector<ofPoint> vertices;
    vector<vector<ofPoint>> vertices2;
};

//====================================================================
//
// polyPDFScene008 [simple Quaternion Example]
//
//====================================================================
class polyPDFScene008 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        poly = new ofPolyline();
        simplePDF->setup(tracing_path, tracing_resample);
        ofBackground(0);

        if (vertices.size()) vertices.clear();
        vertices = simplePDF->getVertices();
        for (int i = 0; i < vertices.size(); i++) {
            seed_x.push_back((int)ofRandom(200));
            seed_y.push_back((int)ofRandom(200));
        }
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        for (int i = 0; i < vertices.size(); i++) {
            poly->begin();
            ofPoint noise = ofPoint(ofNoise(ofGetElapsedTimef() + seed_x[i]) * 100 * ratio_1, ofNoise(ofGetElapsedTimef() + seed_y[i]) * 100 * ratio_1, 0);
            poly->addVertex(ofPoint(vertices[i].x + noise.x, vertices[i].y + noise.y, vertices[i].z));
            if (i == vertices.size() - 1) {
                poly->addVertex(ofPoint(vertices[0].x + noise.x, vertices[0].y + noise.y, vertices[i].z));
            }
            // ofDrawBox(vertices[i].x + noise.x, vertices[i].y + noise.y, vertices[i].z, 5);
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
    polyPDFScene008(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    vector<ofPoint> vertices;
    vector<int> seed_x;
    vector<int> seed_y;
};

//====================================================================
//
// polyPDFScene009 [simple Quaternion Example]
//
//====================================================================
class polyPDFScene009 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        //        poly = new ofPolyline();
        simplePDF->setup(tracing_path, tracing_resample);
        ofBackground(0);

        if (vertices.size()) vertices.clear();
        if (poly.size()) poly.clear();
        vector<ofPoint> tmp_vert = simplePDF->getVertices();
        sphere_resolution = 10;
        for (int i = 0; i < sphere_resolution; i++) {
            poly.push_back(ofPolyline());
            tmp_vert = simplePDF->getRotateVertices(360 / sphere_resolution * i, 0, 0);
            vertices.push_back(tmp_vert);
        }
        //        for (int i = 0; i < vertices.size(); i++) {
        //            seed_x.push_back((int)ofRandom(200));
        //            seed_y.push_back((int)ofRandom(200));
        //        }
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        for (int i = 0; i < sphere_resolution; i++) {
            //            ofPoint noise = ofPoint(ofNoise(ofGetElapsedTimef() + seed_x[i]) * 100 * ratio_1, ofNoise(ofGetElapsedTimef() + seed_y[i]) * 100 * ratio_1, 0);
            for (int j = 0; j < vertices[i].size(); j++) {
                //                ofDrawBox(vertices[i][j].x,vertices[i][j].y,vertices[i][j].z,5);

                poly[i].begin();
                poly[i].addVertex(ofPoint(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z));
                //                if (j == vertices[i].size() - 1) {
                //                    poly[i].addVertex(ofPoint(vertices[i][0].x, vertices[i][0].y, vertices[i][0].z));
                //                }
                poly[i].addVertex(ofPoint(0, 0, 0));
            }
            poly[i].end();
            poly[i].draw();
            poly[i].clear();

            // ofDrawBox(vertices[i].x + noise.x, vertices[i].y + noise.y, vertices[i].z, 5);
        }
    }

    void end() {
        //        delete poly;
        delete simplePDF;
    }

   public:
    polyPDFScene009(string name) { sceneName = name; };

   private:
    //    ofPolyline *poly;
    vector<ofPolyline> poly;
    simplePDFVertices *simplePDF;
    vector<vector<ofPoint>> vertices;
    vector<int> seed_x;
    vector<int> seed_y;
    int sphere_resolution;
};

//====================================================================
//
// polyPDFScene010 [simple Quaternion Example]
//
//====================================================================
class polyPDFScene010 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        //        poly = new ofPolyline();
        simplePDF->setup(tracing_path, tracing_resample);
        layer_num = 100;
        ofBackground(255);
        if (poly.size()) poly.clear();
        if (vertices.size()) vertices.clear();
        if (noise.size()) noise.clear();
        if (scale.size()) scale.clear();
        vertices = simplePDF->getVertices();
        for (int i = 0; i < vertices.size(); i++) {
            seed_x.push_back((int)ofRandom(200));
            seed_y.push_back((int)ofRandom(200));
            noise.push_back(ofPoint(ofNoise(i / 100 + 1.11111) * 100 - 100, ofNoise(i / 100 + 1.11111) * 100 - 100, 0));
            scale.push_back(ofNoise(i+ 1.0));
            //            cout << noise[i].x << " : " << noise[i].y << ofNoise(i * 10 + ofGetElapsedTimef()) << " : " << ofGetElapsedTimef() <<  endl;
            // cout << "noise : " << i <<  " : " << noise[i] << endl;
        }

        for (int i = 0; i < layer_num; i++) {
            poly.push_back(ofPolyline());
        }
    }

    void update() {
        for (int i = 0; i < noise.size(); i++) {
            noise[i] = ofPoint(ofNoise(i * elementInterval / 20 + ofGetElapsedTimef() / 50 * speed), ofNoise((i * elementInterval) / 20 + 1 + ofGetElapsedTimef() / 50 * speed), 0);
        }
        amount = 100 * ratio_1;
        //        cout << "noise : " << ofNoise(ofGetElapsedTimef()) << endl;
    }

    void draw() {
        ofSetColor(0, 200);

        for (int i = 0; i < layer_num; i++) {
            poly[i].begin();
            for (int j = 0; j < vertices.size(); j++) {
                //                ofPoint tmp_vertices = ofPoint(vertices[j] / layer_num * i * ratio_1 + noise[j]);
                ofPoint tmp_vertices = ofPoint(vertices[j] / layer_num * i * ratio_1);
                // poly[i].addVertex(ofPoint(tmp_vertices.x + ofNoise(i + 1.111 * elementInterval) * 100 - 100, tmp_vertices.y + ofNoise(i + 1.111 * elementInterval) * 100 - 100, tmp_vertices.z));

                poly[i].addVertex(ofPoint(tmp_vertices.x + noise[j].x * amount - amount / 2, tmp_vertices.y + noise[j].y * amount - amount / 2, tmp_vertices.z));
                if (j == vertices.size() - 1) {
                    tmp_vertices = ofPoint(vertices[0] / layer_num * i * ratio_1);
                    poly[i].addVertex(ofPoint(tmp_vertices.x + noise[0].x * amount - amount / 2, tmp_vertices.y + noise[0].y * amount - amount / 2, tmp_vertices.z));
                }
            }
            poly[i].end();
            poly[i].draw();
            poly[i].clear();
        }
    }

    void end() {
        //        delete poly;
        delete simplePDF;
    }

   public:
    polyPDFScene010(string name) { sceneName = name; };

   private:
    //    ofPolyline *poly;
    vector<ofPolyline> poly;
    int layer_num;
    simplePDFVertices *simplePDF;
    vector<ofPoint> vertices;
    vector<ofPoint> noise;
    vector<float> scale;
    vector<int> seed_x;
    vector<int> seed_y;
    float amount;
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
        //        simplePDF->setup("pdf/example_ellipse_400px.pdf", 20);
        simplePDF->setup(tracing_path, tracing_resample);
        ofBackground(0);
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        vector<ofPoint> point = simplePDF->getVertices();

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
    simplePDFVerticesExample001(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
};

//====================================================================
//
// simplePDFVerticesExample002 [simple Quaternion Example]
//
//====================================================================
class simplePDFVerticesExample002 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        poly = new ofPolyline();
        simplePDF->setup("pdf/example_ellipse_400px.pdf", 20);
        ofBackground(0);

        if (vertices.size()) vertices.clear();
    }

    void update() {
        //        simplePDF->rotate(90, sin(ofGetElapsedTimef()) * 360, cos(ofGetElapsedTimef()) * 360);
        simplePDF->rotate(0, 0, 90);
        vertices = simplePDF->getVertices();
    }

    void draw() {
        ofSetColor(255);

        for (int i = 0; i < vertices.size(); i++) {
            poly->begin();

            if (i == 0) {
                ofSetColor(255, 0, 0);
            } else if (i == vertices.size() / 2) {
                ofSetColor(255, 255, 0);
            } else {
                ofSetColor(0, 255, 255);
            }

            ofDrawBox(vertices[i].x, vertices[i].y, vertices[i].z, 5);
            //            ofPushMatrix();
            //            ofTranslate(simplePDF->getVertices()[i]);
            //            ofRotateX(90);
            //            ofSetColor(0, 0, 255);
            //            ofDrawBox(vertices[i].x, vertices[i].y, vertices[i].z, 5);
            //            ofPopMatrix();

            poly->addVertex(ofPoint(vertices[i].x, vertices[i].y, vertices[i].z));
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
    simplePDFVerticesExample002(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    vector<ofPoint> vertices;
};

//====================================================================
//
// simplePDFVerticesExample003 [simple polyPDF Example]
//
//====================================================================
class simplePDFVerticesExample003 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        poly = new ofPolyline();
        qManagement = new QuaternionManagement();
        simplePDF->setup("pdf/example_ellipse_400px.pdf", 20);
        ofBackground(0);
    }

    void update() {}

    void draw() {
        ofSetColor(255);

        vector<ofPoint> point;
        float rotateX = 90;
        float rotateY = sin(ofGetElapsedTimef()) * 360;
        float rotateZ = 180;
        float quaternionAngle = qManagement->getQuaternionAngle(rotateX, rotateY, rotateZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotateX, rotateY, rotateZ);

        for (int i = 0; i < simplePDF->getVertices().size(); i++) {
            poly->begin();
            ofPoint pos = qManagement->getPosition(ofPoint(simplePDF->getVertices()[i].x + 1000, simplePDF->getVertices()[i].y, 0), quaternionAngle, quaternionAxis);
            point.push_back(pos);

            ofSetColor(255, 0, 0);
            ofDrawBox(point[i].x, point[i].y, point[i].z, 5);
            //            ofDrawCircle(point[i].x, point[i].y, 5);
            poly->addVertex(ofPoint(point[i].x, point[i].y, point[i].z));

            if (i == simplePDF->getVertices().size() - 1) {
                poly->addVertex(ofPoint(point[0].x, point[0].y, point[0].z));
            }
        }
        poly->end();
        poly->draw();
        poly->clear();
    }

    void end() {
        delete poly;
        delete simplePDF;
        delete qManagement;
    }

   public:
    simplePDFVerticesExample003(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    QuaternionManagement *qManagement;
};

//====================================================================
//
// simplePDFVerticesExample004 [simple polyPDF Example]
//
//====================================================================
class simplePDFVerticesExample004 : public sketchBaseScene {
    void begin() {
        simplePDF = new simplePDFVertices();
        poly = new ofPolyline();
        counter = new simpleCounter();
        simplePDF->setup("pdf/example_ellipse_400px.pdf", 100);
        simplePDF->rotate(90, 0, 0);
        counter->setup(0, 9, speed);
    }

    void update() {
        counter->changeCountAmount(speed);
        counter->update();
    }

    void draw() {
        ofSetColor(255);

        vector<ofPoint> point = simplePDF->getVertices();
        int vertNum = point.size();
        float amount = 5 * elementInterval;

        poly->begin();
        for (int i = 0; i < simplePDF->getVertices().size(); i++) {
            ofSetColor(255, 0, 0);
            for (int j = 0; j < simplePDF->getVertices().size(); j++) {
                if (j % 10 == counter->getValue()) {
                    point[j] = point[j] * ratio_1;
                    ofDrawBox(point[j].x, point[j].y + vertNum * amount * i + amount * j - 500, point[j].z, 5);
                    poly->addVertex(ofPoint(point[j].x, point[j].y + vertNum * amount * i + amount * j - 500, point[j].z));
                }
            }
        }
        poly->end();
        // poly->draw();
        poly->clear();
    }

    void end() {
        simplePDF->clear();
        delete poly;
        delete simplePDF;
        delete counter;
    }

   public:
    simplePDFVerticesExample004(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    simplePDFVertices *simplePDF;
    simpleCounter *counter;
};

//====================================================================
//
// stringPDFExample001 [simple polyPDF Example]
//
//====================================================================
class stringPDFExample001 : public sketchBaseScene {
    void begin() {
        poly = new ofPolyline();
        counter = new simpleCounter();
        vertPDF = new simplePDFVertices();
        numberTotal = 3;
        if (simplePDF.size()) simplePDF.clear();
        if (easings_x.size()) easings_x.clear();
        if (easings_y.size()) easings_y.clear();
        if (easings_z.size()) easings_z.clear();

        for (int i = 0; i < numberTotal; i++) {
            simplePDF.push_back(simplePDFVertices());
            simplePDF[i].setup("pdf/number/" + ofToString(i + 1) + ".pdf", 200);
            simplePDF[i].setTranslatePosition(ofVec3f(-640, -360, 0));
            simplePDF[i].rotate(180, 0, 0);
        }
        for (int i = 0; i < simplePDF[0].getVertices().size(); i++) {
            easings_x.push_back(easingManagement());
            easings_y.push_back(easingManagement());
            easings_z.push_back(easingManagement());
        }
        vertPDF->setup("pdf/example_ellipse_100px.pdf", 30);

        counter->setup(0, 9, speed);
        active_index = 0;
        int startTime = ofGetElapsedTimeMillis();
        interval = 2000;
        nextTime = startTime + interval;
        bMoveVertices = false;
    }

    void update() {
        counter->changeCountAmount(speed);
        counter->update();

        int now = ofGetElapsedTimeMillis();
        if (now > nextTime) {
            setEasings(active_index);
            if (active_index < numberTotal - 1) {
                active_index++;
            } else {
                active_index = 0;
            }
            bMoveVertices = true;
            nextTime += interval;
        }
    }

    void draw() {
        ofSetColor(255);

        vector<ofPoint> point = simplePDF[active_index].getVertices();
        for (int i = 0; i < point.size(); i++) {
            if (i % 2 == 0) {
                poly->begin();
                if (!bMoveVertices) {
                    point[i] = point[i] * ratio_1;
                    // ofDrawBox(point[i].x, point[i].y, point[i].z, 5);
                    for (int j = 0; j < vertPDF->getVertices().size(); j++) {
                        vector<ofPoint> vertPoint = vertPDF->getVertices();
                        vertPoint[j] = (vertPoint[j] * ratio_2) + point[i];
                        poly->addVertex(vertPoint[j].x, vertPoint[j].y, vertPoint[j].z);
                        //                        ofDrawBox(vertPoint[j].x,vertPoint[j].y,vertPoint[j].z,2);
                    }
                } else {
                    easings_x[i].update();
                    easings_y[i].update();
                    easings_z[i].update();
                    ofPoint pos = ofPoint(easings_x[i].getValue(), easings_y[i].getValue(), easings_z[i].getValue());
                    // ofDrawBox(pos.x, pos.y, pos.z, 5);
                    for (int j = 0; j < vertPDF->getVertices().size(); j++) {
                        vector<ofPoint> vertPoint = vertPDF->getVertices();
                        vertPoint[j] = (vertPoint[j] * ratio_2) + pos;
                        poly->addVertex(vertPoint[j].x, vertPoint[j].y, vertPoint[j].z);
                    }
                    if (easings_x[i].completed() && i == point.size() - 1) {
                        bMoveVertices = false;
                    }
                }
                poly->end();
                poly->draw();
                poly->clear();
            }
        }
    }

    void end() {
        delete poly;
        delete vertPDF;
        delete counter;
    }

    void setEasings(int index) {
        int next_index = index;
        if (index + 1 < numberTotal) {
            next_index++;
        } else {
            next_index = 0;
        }
        vector<ofPoint> nowPoint = simplePDF[index].getVertices();
        vector<ofPoint> nextPoint = simplePDF[next_index].getVertices();
        cout << "nowPoint : " << index << "  next : " << next_index << endl;

        for (int i = 0; i < nowPoint.size(); i++) {
            nowPoint[i] = nowPoint[i] * ratio_1;
            nextPoint[i] = nextPoint[i] * ratio_1;
            int duration = 500;
            int delay = 0;
            float begin_x = nowPoint[i].x;
            float begin_y = nowPoint[i].y;
            float begin_z = nowPoint[i].z;
            float end_x = nextPoint[i].x;
            float end_y = nextPoint[i].y;
            float end_z = nextPoint[i].z;
            easings_x[i].setParam(duration, delay, begin_x, end_x);
            easings_y[i].setParam(duration, delay, begin_y, end_y);
            easings_z[i].setParam(duration, delay, begin_z, end_z);
            easings_x[i].start();
            easings_y[i].start();
            easings_z[i].start();
        }
    }

   public:
    stringPDFExample001(string name) { sceneName = name; };

   private:
    ofPolyline *poly;
    vector<simplePDFVertices> simplePDF;
    simplePDFVertices *vertPDF;
    simpleCounter *counter;
    vector<easingManagement> easings_x;
    vector<easingManagement> easings_y;
    vector<easingManagement> easings_z;
    int numberTotal;
    int active_index;
    int interval;
    int nextTime;
    bool bMoveVertices;
};

#endif /* polyPDFScenes_hpp */