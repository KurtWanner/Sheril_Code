#include "Testing.h"
#include "InitializeRobot.h"
#include "Constants.h"
#include "FEHUtility.h"

void Testing::forwardXInches(float x){
    dt.EncoderForward(x, SlowSpeed);
    Sleep(5.0);
}

void Testing::backwardXInches(float x){
    dt.EncoderForward(x, SlowSpeed);
    Sleep(5.0);
}

void Testing::leftXDegrees(float deg){
    dt.EncoderTurn(-deg, SlowSpeed);
    Sleep(5.0);
}

void Testing::rightXDegrees(float deg){
    dt.EncoderTurn(deg, SlowSpeed);
    Sleep(5.0);
}