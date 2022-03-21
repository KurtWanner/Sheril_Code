#include "Testing.h"
#include "Constants.h"
#include "FEHUtility.h"
#include "FEHLCD.h"

void Testing::getEncValues(){
    int x, y;
    while(!LCD.Touch(&x, &y)){
        LCD.Clear();
        LCD.WriteAt(drivetrain.getLeftEnc1(), 5, 50);
        LCD.WriteAt(drivetrain.getLeftEnc2(), 5, 100);
        LCD.WriteAt(drivetrain.getRightEnc1(), 200, 50);
        LCD.WriteAt(drivetrain.getRightEnc2(), 200, 100);

        Sleep(.02);
    }
    WaitForTouch();
    
}

void Testing::forwardXInches(float x){
    drivetrain.encoderForward(x, SlowSpeed);
    WaitForTouch();
}

void Testing::backwardXInches(float x){
    drivetrain.encoderForward(x, SlowSpeed);
    WaitForTouch();
    
}

void Testing::leftXDegrees(float deg){
    drivetrain.encoderTurn(-deg, SlowSpeed);
    WaitForTouch();
}

void Testing::rightXDegrees(float deg){
    drivetrain.encoderTurn(deg, SlowSpeed);
    WaitForTouch();
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
    WaitForTouch();
}