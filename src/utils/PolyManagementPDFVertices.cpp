//
//  PolyManagementPDFVertices.cpp
//  PolyMotion
//
//  Created by user1 on 4/6/16.
//
//

#include "PolyManagementPDFVertices.hpp"

//--------------------------------------------------------------
void PolyManagementPDFVertices::view(int target) { _target = checkNum(target); }

//--------------------------------------------------------------
void PolyManagementPDFVertices::add(string path, int resample) {
    _paths.push_back(path);
    _resamples.push_back(resample);

    _positions.push_back(findVertexList(path, resample));
}

//--------------------------------------------------------------
vector<vector<ofVec2f> > PolyManagementPDFVertices::findVertexList(string path, int resample) {
    ofxPDF *pdf;
    pdf = new ofxPDF();
    pdf->loadPDF(path);

    vector<vector<ofVec2f> > parentList;
    int pathTotal = pdf->getNumPath();

    for (int i = 0; i < pathTotal; i++) {
        vector<ofVec2f> list;

        ofPath *path;
        path = &pdf->getPathAt(i);  // 1 : get path from pdf

        vector<ofPolyline> polys = path->getOutline();  // 2 : get outline from path

        for (int j = 0; j < polys.size(); j++) {
            ofPolyline polyline = polys[j];                     // 3 : get polyline from outline
            polyline = polyline.getResampledByCount(resample);  // 4 : div

            for (int k = 0; k < polyline.getVertices().size(); k++) {
                list.push_back(ofVec2f(polyline.getVertices()[k]));  // 5 : get vertices, push to arr
            }
        }

        parentList.push_back(list);
    }
    delete pdf;
    return parentList;
}

//--------------------------------------------------------------
int PolyManagementPDFVertices::checkNum(int target) {
    if (target < _positions.size()) {
        return target;
    } else {
        return 0;
    }
}
