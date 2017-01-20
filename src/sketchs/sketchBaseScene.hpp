//
//  sketchBaseScene.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/13.
//
//

#ifndef sketchBaseScene_hpp
#define sketchBaseScene_hpp

#include "ofMain.h"

class sketchBaseScene {
   public:
    inline virtual void setup(){};
    inline virtual void begin(){};
    inline virtual void update(){};
    inline virtual void draw(){};
    inline virtual void end(){};

    inline void setSpeed(float _speed) { speed = _speed; }
    inline void setElementInterval(float _elementInterval) { elementInterval = _elementInterval; }
    inline void setRatio1(float _ratio) { ratio_1 = _ratio; }
    inline void setRatio2(float _ratio) { ratio_2 = _ratio; }
    inline void setTracingResample(int resample) { tracing_resample = resample; };
    inline void setTracingPath(string path) { tracing_path = path; };

    string sceneName;

   protected:
    float speed;
    float elementInterval;
    float ratio_1;
    float ratio_2;
    bool bTracing;
    int tracing_resample;
    string tracing_path;

   private:
};

#endif /* sketchBaseScene_hpp */
