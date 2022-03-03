#include "Testing.h"
#include "Constants.h"
#include "FEHUtility.h"
#include "FEHLCD.h"

void Testing::getEncValues(){
    int x, y;
    while(!LCD.Touch(&x, &y)){
        LCD.Clear();
        LCD.WriteAt(drivetrain.GetLeftEnc1(), 5, 50);
        LCD.WriteAt(drivetrain.GetLeftEnc2(), 5, 100);
        LCD.WriteAt(drivetrain.GetRightEnc1(), 200, 50);
        LCD.WriteAt(drivetrain.GetRightEnc2(), 200, 100);

        Sleep(.02);
    }
    
}

void Testing::forwardXInches(float x){
    drivetrain.EncoderForward(x, SlowSpeed);
    Sleep(5.0);
}

void Testing::backwardXInches(float x){
    drivetrain.EncoderForward(x, SlowSpeed);
    Sleep(5.0);
    
}

void Testing::leftXDegrees(float deg){
    drivetrain.EncoderTurn(-deg, SlowSpeed);
    Sleep(5.0);
}

void Testing::rightXDegrees(float deg){
    drivetrain.EncoderTurn(deg, SlowSpeed);
    Sleep(5.0);
}

void Testing::getCdSValue(){
    int x, y;
    LCD.Clear();
    while(!LCD.Touch(&x, &y)){
        LCD.WriteAt("Value:", 5, 20);
        LCD.WriteAt("onBlueLight:", 5, 50);
        LCD.WriteAt("onRedLight:", 5, 80);
        LCD.WriteAt("onStartLight", 5, 110);
        LCD.WriteAt(CdS.Value(), 100, 20);
        LCD.WriteAt(CdS.onBlueLight(), 100, 50);
        LCD.WriteAt(CdS.onBlueLight(), 100, 80);
        LCD.WriteAt(CdS.onStartLight(), 100, 110);
    }
    Sleep(5.0);
}