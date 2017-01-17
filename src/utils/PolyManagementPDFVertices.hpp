//
//  PolyManagementPDFVertices.hpp
//  PolyMotion
//
//  Created by user1 on 4/6/16.
//
//

#ifndef PolyManagementPDFVertices_hpp
#define PolyManagementPDFVertices_hpp

#include "ofMain.h"
#include "ofxPDF.h"

class PolyManagementPDFVertices {
   public:
    inline vector<vector<ofVec2f> > getVertices() { return _positions[_target]; };
    inline int getRegisteredTotal() { return _positions.size(); };

    inline string getPath(int index) { return _paths[index]; };
    inline int getResample(int index) { return _resamples[index]; };

    void view(int target);
    void add(string path, int resample);

   private:
    int checkNum(int target);

    // method
    vector<vector<ofVec2f> > findVertexList(string path, int resample);

    // arr
    vector<vector<vector<ofVec2f> > > _positions;
    vector<string> _paths;
    vector<int> _resamples;

    int _target;
};

#endif /* PolyManagementPDFVertices_hpp */
