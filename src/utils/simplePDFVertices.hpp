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
        translatePosition = ofVec3f(0,0,0);
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
            ofPoint pos = qManagement->getPosition(ofPoint(polyPDF->getVertices()[0][i].x + translatePosition.x, polyPDF->getVertices()[0][i].y + translatePosition.y, translatePosition.z), quaternionAngle, quaternionAxis);
            vertices[i] = pos;
        }
    }
    void rotate(int index, float rotX, float rotY, float rotZ) {
        float quaternionAngle = qManagement->getQuaternionAngle(rotX, rotY, rotZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotX, rotY, rotZ);
        ofPoint pos = qManagement->getPosition(ofPoint(vertices[index].x + translatePosition.x, vertices[index].y + translatePosition.y, translatePosition.z), quaternionAngle, quaternionAxis);
        vertices[index] = pos;
    }
    vector<ofPoint> getRotateVertices(float rotX,float rotY,float rotZ){
        vector<ofPoint> tmp_vertices;
        float quaternionAngle = qManagement->getQuaternionAngle(rotX, rotY, rotZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotX, rotY, rotZ);
        for (int i = 0; i < vertices.size(); i++) {
            ofPoint pos = qManagement->getPosition(ofPoint(polyPDF->getVertices()[0][i].x + translatePosition.x, polyPDF->getVertices()[0][i].y + translatePosition.y, translatePosition.z), quaternionAngle, quaternionAxis);
            tmp_vertices.push_back(pos);
        }
        return tmp_vertices;
    }
    ofPoint getRotateVertices(int index,float rotX,float rotY,float rotZ){
        ofPoint tmp_vertices;
        float quaternionAngle = qManagement->getQuaternionAngle(rotX, rotY, rotZ);
        ofVec3f quaternionAxis = qManagement->getQuaternionAxis(rotX, rotY, rotZ);
            ofPoint pos = qManagement->getPosition(ofPoint(polyPDF->getVertices()[0][index].x + translatePosition.x, polyPDF->getVertices()[0][index].y + translatePosition.y, translatePosition.z), quaternionAngle, quaternionAxis);
        return pos;
    }
    
    void setTranslatePosition(ofVec3f position){
        translatePosition = position;
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
    ofVec3f translatePosition;
};

#endif /* simplePDFVertices_hpp */
