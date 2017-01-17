//
//  simpleCounter.hpp
//  sketchExamples
//
//  Created by 松岡正 on 2017/01/14.
//
//

#ifndef simpleCounter_hpp
#define simpleCounter_hpp

#include "ofMain.h"

class simpleCounter {
   public:
    void setup(int start, int reset, float amount) {
        start_val = start;
        counter_val = start;
        tmp_counter_val = start;
        count_amount = amount;
        reset_val = reset;
        reset_count = 0;
    }

    void setup(int reset) {
        start_val = 0;
        counter_val = 0;
        count_amount = 1;
        reset_val = reset;
        reset_count = 0;
    }

    inline void changeCountAmount(float amount) { count_amount = amount; };
    inline void changeResetCount(int reset) { reset_val = reset; };

    void update() {
        if (tmp_counter_val < reset_val) {
            tmp_counter_val += count_amount;
        } else {
            tmp_counter_val = start_val;
            reset_count++;
        }
        counter_val = (int)tmp_counter_val;
    }

    inline int getValue() { return (int)counter_val; }
    //    inline int getValue() { return ofToInt(counter_val); }
    inline int getResetCount() { return reset_count; }
    inline int getResetValue() { return reset_val; };

   private:
    int start_val;
    float tmp_counter_val;
    int counter_val;
    float count_amount;
    float reset_val;

    int reset_count;
};

#endif /* simpleCounter_hpp */
