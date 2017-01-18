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

    string sceneName;

   protected:
    float speed;
    float elementInterval;
    float ratio_1;
    float ratio_2;

   private:
};

#endif /* sketchBaseScene_hpp */
