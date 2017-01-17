//
//  QuaternionManagement.hpp
//  QuaternionPractice
//
//  Created by 藤元 翔平 on 8/3/16.
//
//

#ifndef QuaternionManagement_hpp
#define QuaternionManagement_hpp

#include "ofMain.h"

class QuaternionManagement {
   public:
    QuaternionManagement(){};
    ~QuaternionManagement(){};

    inline float getQuaternionAngle() { return this->quaternionAngle; };
    inline ofVec3f getQuaternionAxis() { return this->quaternionAxis; };
    inline float getQuaternionAngle(float rotateX, float rotateY, float rotateZ) {
        this->quaternionAngle = makeQuaternionAngle(rotateX, rotateY, rotateZ);
        return this->quaternionAngle;
    };
    inline ofVec3f getQuaternionAxis(float rotateX, float rotateY, float rotateZ) {
        this->quaternionAxis = makeQuaternionAxis(rotateX, rotateY, rotateZ);
        return this->quaternionAxis;
    };
    inline ofPoint getPosition(ofPoint position, float quaternionAngle, ofVec3f quaternionAxis) {
        m.makeRotationMatrix(quaternionAngle, quaternionAxis);
        return position * m;
    }

    void setRotate(float rotateX, float rotateY, float rotateZ) {
        this->quaternionAngle = makeQuaternionAngle(rotateX, rotateY, rotateZ);
        this->quaternionAxis = makeQuaternionAxis(rotateX, rotateY, rotateZ);
    };

   private:
    float makeQuaternionAngle(float rotateX, float rotateY, float rotateZ) {
        qp = ofQuaternion(rotateX, Xnormal);
        qy = ofQuaternion(rotateY, Ynormal);
        qr = ofQuaternion(rotateZ, Znormal);
        qt = qr * qp * qy;

        ofVec3f qAxsis;
        float angle;
        qt.getRotate(angle, qAxsis);

        return angle;
    }

    ofVec3f makeQuaternionAxis(float rotateX, float rotateY, float rotateZ) {
        qp = ofQuaternion(rotateX, Xnormal);
        qy = ofQuaternion(rotateY, Ynormal);
        qr = ofQuaternion(rotateZ, Znormal);
        qt = qr * qp * qy;

        ofVec3f qAxsis;
        float angle;
        qt.getRotate(angle, qAxsis);

        return qAxsis;
    }

    float quaternionAngle;
    ofVec3f quaternionAxis;

    ofVec3f Znormal = ofVec3f(0, 0, 1);
    ofVec3f Xnormal = ofVec3f(1, 0, 0);
    ofVec3f Ynormal = ofVec3f(0, 1, 0);

    ofQuaternion qr;
    ofQuaternion qp;
    ofQuaternion qy;
    ofQuaternion qt;

    ofMatrix4x4 m;
};

#endif /* QuaternionManagement_hpp */
