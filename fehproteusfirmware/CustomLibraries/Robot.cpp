#include "Robot.h"
#include "FEHLCD.h"

//use to drive over jukebox
int RobotClass::readCdSEncoderForward(double distance, double speed){
    drivetrain.resetLeftCounts();
    drivetrain.resetRightCounts();
    // Set to max value of CdS value
    double CdSmin = 3.0;
    drivetrain.leftMotor.SetPercent(speed * 0.88);
    drivetrain.rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    
    // Continue until both left and right motors have reached their desired values
    while(!leftDone || !rightDone){
        if(CdS.Value() < CdSmin){
            CdSmin = CdS.Value();
        }
        int diff = drivetrain.getRightEnc1() - drivetrain.getLeftEnc1();

        // Print debugging values to LCD
        drivetrain.printEncoderValues();
        LCD.WriteAt(0.88 * (-speed - drivetrain.sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - drivetrain.sigmoid(diff), 190, 140);

        if(!leftDone){
            drivetrain.leftMotor.SetPercent(0.88 * (speed + drivetrain.sigmoid(diff)));
        }
        if(!rightDone){
            drivetrain.rightMotor.SetPercent(speed - drivetrain.sigmoid(diff));
        }
        if(drivetrain.getRightEnc1() > distance * COUNTS_PER_INCH){
            rightDone = true;
            drivetrain.rightMotor.Stop();
        }
        if(drivetrain.getLeftEnc1() > distance * COUNTS_PER_INCH){
            leftDone = true;
            drivetrain.leftMotor.Stop();
        }
        Sleep(.01);

    }
    drivetrain.leftMotor.Stop();
    drivetrain.rightMotor.Stop();
    return CdS.getLight(CdSmin);
}