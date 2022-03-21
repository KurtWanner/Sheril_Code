#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHRPS.h"



class Drivetrain {

    public:

    FEHMotor leftMotor = FEHMotor(FEHMotor::Motor0,7.2);
    FEHMotor rightMotor = FEHMotor(FEHMotor::Motor1,7.2);
    DigitalEncoder leftEncoder1 = DigitalEncoder(FEHIO::P0_1);
    DigitalEncoder leftEncoder2 = DigitalEncoder(FEHIO::P0_7);
    DigitalEncoder rightEncoder1 = DigitalEncoder(FEHIO::P2_7);
    DigitalEncoder rightEncoder2 = DigitalEncoder(FEHIO::P3_4);

    Drivetrain();

    // TODO Add overloaded functions for encoder counts
    // TODO Add PIDBackward function
    void PIDForward(double dist);
    void PIDForwardToX(double x);
    void PIDForwardToY(double y);
    void PIDTurn(double angle);
    void PIDTurnToHeading(double heading);

    // TODO Add overloaded functions for encoder counts
    void encoderForward(double distance, double speed);
    void encoderBackward(double distance, double speed);
    void encoderForwardToX(double x, double speed);
    void encoderForwardToY(double y, double speed);
    void encoderLeftMotorTurn(double angle, double speed);
    void encoderRightMotorTurn(double angle, double speed);
    void encoderTurn(double angle, double speed);
    void encoderTurnToHeading(double heading, double speed);

    void drive(double speed, double time);
    void driveTurn(double speedLeft, double speedRight, double time);

    int getLeftEnc1();
    int getLeftEnc2();
    int getRightEnc1();
    int getRightEnc2();

    void resetLeftCounts();
    void resetRightCounts();

    double sigmoid(double x);

    // TODO Test polarity
    void SetLeftPolarity(bool b);
    void SetRightPolarity(bool b);

    void turnCounterclockwise(int, int);
    void pulseForward();
    void pulseBackward();
    void pulseClockwise();
    void pulseCounterclockwise();


    void checkY(float y);
    void checkX(float x);
    void checkHeading(float heading);

    double getDistToX(double x);
    double getDistToY(double y);

};

#endif