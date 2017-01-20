//
//  meshExample.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/15.
//
//

#ifndef meshExample_hpp
#define meshExample_hpp

#include "ofMain.h"
#include "sketchBaseScene.hpp"

//====================================================================
//
// meshExample001 [simple ofMesh Example]
//
//====================================================================
class meshExample001 : public sketchBaseScene {
    void begin() { mesh = new ofMesh(); }

    void update() {}

    void draw() {
        mesh->clear();
        for (int i = 0; i < 7; i++) {
            switch (i) {
                case 0:
                    mesh->setMode(OF_PRIMITIVE_TRIANGLES);
                    break;
                case 1:
                    mesh->setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                    break;
                case 2:
                    mesh->setMode(OF_PRIMITIVE_TRIANGLE_FAN);
                    break;
                case 3:
                    mesh->setMode(OF_PRIMITIVE_LINES);
                    break;
                case 4:
                    mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                    break;
                case 5:
                    mesh->setMode(OF_PRIMITIVE_LINE_LOOP);
                    break;
                case 6:
                    mesh->setMode(OF_PRIMITIVE_POINTS);
                    break;
            }
            mesh->addVertex(ofVec3f(100, 100, 0));
            mesh->addVertex(ofVec3f(100, 200, 0));
            mesh->addVertex(ofVec3f(200, 200, 0));
            mesh->addVertex(ofVec3f(200, 100, 0));
            mesh->addVertex(ofVec3f(250, 150, 0));

            ofPushMatrix();
            ofTranslate(-800 + 200 * i, -250);
            mesh->draw();
            ofPushMatrix();
            ofTranslate(0, 200);
            mesh->drawWireframe();
            ofPopMatrix();
            ofPopMatrix();
        }
    }

    void end() { delete mesh; }

   public:
    meshExample001(string name) { sceneName = name; };

   private:
    ofMesh *mesh;
};

//====================================================================
//
// vboExample001 [simple vbo Example]
//
//====================================================================
class vboExample001 : public sketchBaseScene {
    void begin() {
        mesh = new ofMesh();
        myVbo = new ofVbo();
        ofEnableDepthTest();
        int d = 100;
        int w = 500;

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < d; j++) {
                vertex[i * d + j] = ofVec3f(-1250 + i * 5, 0, -250 + j * 5);
            }
        }
        myVbo->setVertexData(vertex, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    }

    void update() {}

    void draw() {
        ofSetColor(255);
        ofDrawAxis(50);
        glPointSize(sin(ofGetElapsedTimef()) * 4.0);
        myVbo->draw(GL_POINTS, 0, NUM_PARTICLES);
    }

    void end() {
        ofDisableDepthTest();
        delete mesh;
        delete myVbo;
    }

   public:
    vboExample001(string name) { sceneName = name; };

   private:
    static const int NUM_PARTICLES = 50000;
    ofVec3f vertex[NUM_PARTICLES];
    ofMesh *mesh;
    ofVbo *myVbo;
};

//====================================================================
//
// vboExample002 [simple vbo Example]
//
//====================================================================
class vboExample002 : public sketchBaseScene {
    void begin() {
        mesh = new ofMesh();
        myVbo = new ofVbo();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                vertex[i * depth + j] = ofVec3f(-1250 + i * 5, 0, -250 + j * 5);
            }
        }
        myVbo->setVertexData(vertex, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    }

    void update() {
        // myVbo->clearVertices();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                vertex[i * depth + j] = ofVec3f(-1250 + i * 5, sin((ofGetElapsedTimef() + width) * 2) * 500, -250 + j * 5);
            }
        }
        myVbo->updateVertexData(vertex, NUM_PARTICLES);
    }

    void draw() {
        ofSetColor(255);
        glPointSize(sin(ofGetElapsedTimef()) * 4.0);
        myVbo->draw(GL_POINTS, 0, NUM_PARTICLES);
    }

    void end() {
        delete mesh;
        delete myVbo;
    }

   public:
    vboExample002(string name) { sceneName = name; };

   private:
    static const int NUM_PARTICLES = 50000;
    ofVec3f vertex[NUM_PARTICLES];
    int width = 500;
    int depth = 100;
    ofMesh *mesh;
    ofVbo *myVbo;
};

//====================================================================
//
// vboMeshExample001 [simple vboMesh Example]
//
//====================================================================
class vboMeshExample001 : public sketchBaseScene {
    void begin() {
        vboMesh = new ofVboMesh();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                //                vertex[i * d + j] = ofVec3f(-1250 + i * 5, 0, -250 + j * 5);
                vertices.push_back(ofVec3f(-1250 + i * 5, 0, -250 + j * 5));
            }
        }
    }

    void update() {
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
        vboMesh->drawWireframe();
    }

    void end() { delete vboMesh; }

   public:
    vboMeshExample001(string name) { sceneName = name; };

   private:
    static const int NUM_PARTICLES = 50000;
    vector<ofVec3f> vertices;
    int width = 500;
    int depth = 100;
    ofVboMesh *vboMesh;
};

//====================================================================
//
// meshObjExample001 [simple vboMesh Example]
//
//====================================================================
class meshObjExample001 : public sketchBaseScene {
    void begin() {
        mesh = new ofMesh();
        mesh->load("obj/lofi-bunny.ply");
        for(int i=0;i<mesh->getNumVertices();i++){
            vertices.push_back(mesh->getVertex(i));
            //ofLogNotice("vertices")<<vertices[i].x << " : " <<vertices[i].y << " : " << vertices[i].z ;
        }
    }

    void update() {
    }

    void draw() {
        glPointSize(2);
        ofSetColor(ofColor::white);
        mesh->drawVertices();
    }

    void end() {
        delete mesh;
    }

   public:
    meshObjExample001(string name) { sceneName = name; };

   private:
    ofMesh *mesh;
    vector<ofVec3f> vertices;

};

#endif /* meshExample_hpp */
