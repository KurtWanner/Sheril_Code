#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHRPS.h"

class Drivetrain {

    public:

    // Motor and encoder initializations
    FEHMotor leftMotor = FEHMotor(FEHMotor::Motor0,7.2);
    FEHMotor rightMotor = FEHMotor(FEHMotor::Motor1,7.2);
    DigitalEncoder leftEncoder1 = DigitalEncoder(FEHIO::P0_1);
    DigitalEncoder leftEncoder2 = DigitalEncoder(FEHIO::P0_7);
    DigitalEncoder rightEncoder1 = DigitalEncoder(FEHIO::P2_7);
    DigitalEncoder rightEncoder2 = DigitalEncoder(FEHIO::P3_4);

    Drivetrain();

    // Navigational methods using encoders
    void encoderForward(double distance, double speed);
    void encoderBackward(double distance, double speed);
    void encoderForwardToX(double x, double speed);
    void encoderForwardToY(double y, double speed);
    void encoderLeftMotorTurn(double angle, double speed);
    void encoderRightMotorTurn(double angle, double speed);

    // Set raw speed to motors
    void drive(double speed, double time);
    void driveTurn(double speedLeft, double speedRight, double time);

    // Getting encoder values
    int getLeftEnc1();
    int getLeftEnc2();
    int getRightEnc1();
    int getRightEnc2();
    void printEncoderValues();

    // Resetting encoder values for left and right sides 
    void resetLeftCounts();
    void resetRightCounts();

    // Drivetrain sigmoid method
    double sigmoid(double x);

    // Motor polarity methods
    void SetLeftPolarity(bool b);
    void SetRightPolarity(bool b);

    // Check & pulse functions
    void pulseForward();
    void pulseBackward();
    void pulseClockwise();
    void pulseCounterclockwise();
    void checkY(float y);
    void checkX(float x);
    void checkHeading(float heading);

    // Get distance to given x or y RPS value
    double getDistToX(double x);
    double getDistToY(double y);

};

#endif