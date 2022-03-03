#include "Testing.h"
#include "InitializeRobot.h"
#include "Constants.h"
#include "FEHUtility.h"
#include "FEHLCD.h"

void Testing::getEncValues(){
    int x, y;
    while(!LCD.Touch(&x, &y)){
        LCD.Clear();
        LCD.WriteAt(dt.GetLeftEnc1(), 5, 50);
        LCD.WriteAt(dt.GetLeftEnc2(), 5, 100);
        LCD.WriteAt(dt.GetRightEnc1(), 200, 50);
        LCD.WriteAt(dt.GetRightEnc2(), 200, 100);

        Sleep(.02);
    }
}

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