//
//  particleExample.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/15.
//
//

#ifndef particleExample_hpp
#define particleExample_hpp

#include "ofMain.h"
#include "sketchBaseScene.hpp"
#include "ofxPDF.h"
#include "PolyManagementPDFVertices.hpp"
#include "simpleCounter.hpp"

//====================================================================
//
// vboMeshParticle001 [simple vboMesh Example]
//
//====================================================================
class vboMeshParticle001 : public sketchBaseScene {
    void begin() {
        vboMesh = new ofVboMesh();
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

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                //                vertex[i * d + j] = ofVec3f(-1250 + i * 5, 0, -250 + j * 5);
                vertices.push_back(ofVec3f(-1250 + i * 5, 0, -250 + j * 5));
            }
        }
    }

    void update() {
        counter->update();
        counter->changeCountAmount(speed);

        vboMesh->clear();
        vboMesh->setMode(OF_PRIMITIVE_POINTS);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                vboMesh->addVertex(vertices[i * depth + j]);
            }
        }
    }

    void draw() {
        ofSetColor(255);
        vboMesh->draw();

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
    }

    void end() {
        delete vboMesh;
        delete pdf;
        delete pdf_small;
        delete poly;
        delete counter;
    }

   public:
    vboMeshParticle001(string name) { sceneName = name; };

   private:
    static const int NUM_PARTICLES = 50000;
    vector<ofVec3f> vertices;
    int width = 500;
    int depth = 100;
    ofVboMesh *vboMesh;

    PolyManagementPDFVertices polyManagement;
    ofPolyline *poly;
    vector<ofPolyline *> _poly;
    PolyManagementPDFVertices polyManagement_small;

    ofxPDF *pdf;
    ofxPDF *pdf_small;
    simpleCounter *counter;
    int resample;
    int circleNum;
};

//====================================================================
//
// vboMeshParticle002 [simple vboMesh Example]
//
//====================================================================
class vboMeshParticle002 : public sketchBaseScene {
    void begin() {
        vboMesh = new ofVboMesh();
        pdf = new ofxPDF();
        pdf_small = new ofxPDF();
        polyManagement = new PolyManagementPDFVertices();
        polyManagement_small = new PolyManagementPDFVertices();
        poly = new ofPolyline();
        poly_small = new ofPolyline();

        resample = 1000;
        circleNum = 50;
        pdf->load("pdf/example_ellipse_400px.pdf");
        //        pdf_small->load("pdf/")
        polyManagement->add("pdf/example_ellipse_400px.pdf", resample / 2);
    }

    void update() {
        vboMesh->clear();
        vboMesh->setMode(OF_PRIMITIVE_POINTS);
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                vboMesh->addVertex(ofVec3f(100 * sin(36 * i) + 200 * sin(36 * j), 200 * cos(36 * j), 100 * cos(36 * i)));
            }
        }
    }

    void draw() {
        vector<vector<ofVec2f>> point = polyManagement->getVertices();
        float scale = 1.5;
        int poly_index = 0;

        for (int i = 0; i < point.size(); i++) {
            poly->begin();
            for (int j = 0; j < point[i].size(); j++) {
                if (j % (resample / circleNum) == 0) {
                    poly->addVertex(ofVec3f(point[i][j].x, point[i][j].y, 0));
                    ofSetColor(255, 255, 0);
                    ofDrawCircle(point[i][j].x, point[i][j].y, 2);
                }
            }
            poly->end();
            poly->draw();
            poly->clear();
        }
        ofSetColor(255);
        //        vboMesh->draw();
    }

    void end() {
        delete vboMesh;
        delete pdf;
        delete polyManagement;
        delete poly;
    }

   public:
    vboMeshParticle002(string name) { sceneName = name; };

   private:
    ofVboMesh *vboMesh;

    ofxPDF *pdf;
    ofxPDF *pdf_small;
    PolyManagementPDFVertices *polyManagement;
    PolyManagementPDFVertices *polyManagement_small;
    ofPolyline *poly;
    ofPolyline *poly_small;
    int resample;
    int circleNum;
};

#endif /* particleExample_hpp */
