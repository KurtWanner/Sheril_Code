#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "FEHMotor.h"
#include "FEHIO.h"

FEHMotor leftMotor(FEHMotor::Motor0,7.2);
FEHMotor rightMotor(FEHMotor::Motor1,7.2);
DigitalEncoder leftEncoder(FEHIO::P0_1);
DigitalEncoder rightEncoder(FEHIO::P3_4);

class Drivetrain {

    
    public:

    Drivetrain();

    void PIDForward(double);
    void PIDForwardToX(double);
    void PIDForwardToY(double);
    void PIDTurn(double);
    void PIDTurnToHeading(double);

    void EncoderForward(double, double);
    void EncoderForwardToX(double, double);
    void EncoderForwardToY(double, double);
    void EncoderTurn(double, double);
    void EncoderTurnToHeading(double, double);

    void Drive(double, double);
    void DriveTurn(double, double, double);

};

#endif