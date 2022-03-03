#ifndef TESTING_H
#define TESTING_H

#include "Robot.h"

class Testing: public RobotClass{
    public:

    void getEncValues();
    void forwardXInches(float x);
    void backwardXInches(float x);
    void rightXDegrees(float deg);
    void leftXDegrees(float deg);
    void getCdSValue();
};


#endif