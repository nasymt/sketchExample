//
//  simplePDFVertices.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/17.
//
//

#ifndef simplePDFVertices_hpp
#define simplePDFVertices_hpp

#include "ofMain.h"
#include "ofxPDF.h"
#include "PolyManagementPDFVertices.hpp"
#include "QuaternionManagement.hpp"

class simplePDFVertices {
   public:
    void setup(string path, int resample) {
        pdf = new ofxPDF();
        polyPDF = new PolyManagementPDFVertices();
        qManagement = new QuaternionManagement();
        pdf->load(path);
        polyPDF->add(path, resample);
        points = polyPDF->getVertices();
        for (int i = 0; i < points[0].size(); i++) {
            vertices.push_back(ofPoint(points[0][i].x, points[0][i].y));
        }
    }

    void rotate(float rotX, float rotY, float rotZ) {
        float quaternionAngle = qManagement->getQuaternionAngle(rotX, rotY, rotZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotX, rotY, rotZ);
        for (int i = 0; i < vertices.size(); i++) {
            ofPoint pos = qManagement->getPosition(ofPoint(polyPDF->getVertices()[0][i].x, polyPDF->getVertices()[0][i].y, 0), quaternionAngle, quaternionAxis);
            vertices[i] = pos;
        }
    }
    void rotate(int index, float rotX, float rotY, float rotZ) {
        float quaternionAngle = qManagement->getQuaternionAngle(rotX, rotY, rotZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotX, rotY, rotZ);
        ofPoint pos = qManagement->getPosition(ofPoint(vertices[index].x, vertices[index].y, 0), quaternionAngle, quaternionAxis);
        vertices[index] = pos;
    }

    void resize(float ratio) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i] *= ratio;
        }
    }

    //    inline vector<ofVec2f> getVertices() { return vertices; }
    inline vector<ofPoint> getVertices() { return vertices; }
    inline ofPoint getVertices(int index) { return vertices[index]; };

    void drawPDF() { pdf->draw(); }

    void clear() {
        delete pdf;
        delete polyPDF;
        delete qManagement;
    }

   private:
    ofxPDF *pdf;
    PolyManagementPDFVertices *polyPDF;
    QuaternionManagement *qManagement;
    //    vector<ofVec2f> vertices;
    vector<ofPoint> vertices;
    vector<vector<ofVec2f>> points;
};

#endif /* simplePDFVertices_hpp */
