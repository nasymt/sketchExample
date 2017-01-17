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

class simplePDFVertices {
   public:
    void setup(string path, int resample) {
        pdf = new ofxPDF();
        polyPDF = new PolyManagementPDFVertices();
        pdf->load(path);
        polyPDF->add(path, resample);
        points = polyPDF->getVertices();
        for (int i = 0; i < points[0].size(); i++) {
            vertices.push_back(ofPoint(points[0][i].x, points[0][i].y));
        }
    }

    inline vector<ofVec2f> getVertices() { return vertices; }

    voif drawPDF() { pdf->draw(); }

    void clear() {
        delete pdf;
        delete polyPDF;
    }

   private:
    ofxPDF *pdf;
    PolyManagementPDFVertices *polyPDF;
    vector<ofVec2f> vertices;
    vector<vector<ofVec2f>> points;
};

#endif /* simplePDFVertices_hpp */
