//
//  sceneUnit.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/15.
//
//

#ifndef sceneUnit_hpp
#define sceneUnit_hpp

#include "ofMain.h"

// sketchs class
#include "polylineExample.hpp"
#include "polyPDFScenes.hpp"
#include "meshExample.hpp"
#include "particleExample.hpp"
#include "utilExample.hpp"

class sceneUnit {
   public:
    sceneUnit() {
        //---------------------------------------
        // polyline Example
        //---------------------------------------
        add(new polylineExample001("polylineExample001"));
        add(new polylineExample002("polylineExample002"));
        add(new polylineExample003("polylineExample003"));
        add(new polylineExample004_bezier("polylineExample004_bezier"));
        add(new polylineExample005_curveTo("polylineExample005_curveTo"));
        
        //---------------------------------------
        // polyPDF Example
        //---------------------------------------
        add(new polyPDFScene001("polyPDFScene001"));
        add(new polyPDFScene002("polyPDFScene002"));
        add(new polyPDFScene003("polyPDFScene003"));
        add(new polyPDFScene004("polyPDFScene004"));
        add(new polyPDFScene005("polyPDFScene005"));
        add(new polyPDFScene006("polyPDFScene006"));
        add(new polyPDFScene007("polyPDFScene007"));
        add(new polyPDFScene008("polyPDFScene008"));
        add(new polyPDFScene009("polyPDFScene009"));
        add(new polyPDFScene010("polyPDFScene010"));
        add(new simplePDFVerticesExample001("simplePDFVerticesExample001"));
        add(new simplePDFVerticesExample002("simplePDFVerticesExample002"));
        add(new simplePDFVerticesExample003("simplePDFVerticesExample003"));
        add(new simplePDFVerticesExample004("simplePDFVerticesExample004"));
        add(new stringPDFExample001("stringPDFExample001"));
        
        //---------------------------------------
        // vbo / mesh Example
        //---------------------------------------
        add(new meshExample001("meshExample001"));
        add(new vboExample001("vboExample001"));
        add(new vboExample002("vboExample002"));
        add(new vboMeshExample001("vboMeshExample001"));
        add(new meshObjExample001("meshObjExample001"));
        
        //---------------------------------------
        // particle Example
        //---------------------------------------
        add(new vboMeshParticle001("vboMeshParticle001"));
        add(new vboMeshParticle002("vboMeshParticle002"));
        add(new vboMeshParticle003("vboMeshParticle003"));
        
        
        //---------------------------------------
        // noise Example
        //---------------------------------------
        add(new noiseExample001("noiseExample001"));
}

    vector<sketchBaseScene *> scenes;

   private:
    void add(sketchBaseScene *scene) { scenes.push_back(scene); };
};

#endif /* sceneUnit_hpp */
