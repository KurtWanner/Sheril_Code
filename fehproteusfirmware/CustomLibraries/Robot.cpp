#include "Robot.h"
#include "FEHLCD.h"

int RobotClass::readCdSEncoderForward(double distance, double speed){
    drivetrain.resetLeftCounts();
    drivetrain.resetRightCounts();
    double CdSmin = 3.0;
    drivetrain.leftMotor.SetPercent(speed * 0.88);
    drivetrain.rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        if(CdS.Value() < CdSmin){
            CdSmin = CdS.Value();
        }
        int diff = drivetrain.getRightEnc1() - drivetrain.getLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(drivetrain.getLeftEnc1(), 190, 5);
        LCD.WriteAt(drivetrain.getLeftEnc2(), 190, 30);
        LCD.WriteAt(drivetrain.getRightEnc1(), 190, 55);
        LCD.WriteAt(drivetrain.getRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - drivetrain.sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - drivetrain.sigmoid(diff), 190, 140);
        if(!leftDone){
            drivetrain.leftMotor.SetPercent(0.88 * (speed + drivetrain.sigmoid(diff)));
        }
        if(!rightDone){
            drivetrain.rightMotor.SetPercent(speed - drivetrain.sigmoid(diff));
        }
        if(drivetrain.getRightEnc1() > distance * CountsPerInch){
            rightDone = true;
            drivetrain.rightMotor.Stop();
        }
        if(drivetrain.getLeftEnc1() > distance * CountsPerInch){
            leftDone = true;
            drivetrain.leftMotor.Stop();
        }
        Sleep(.01);

    }
    drivetrain.leftMotor.Stop();
    drivetrain.rightMotor.Stop();
    return CdS.getLight(CdSmin);
}