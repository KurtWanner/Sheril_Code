#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "FEHMotor.h"
#include "FEHIO.h"



class Drivetrain {

    public:

    // TODO Add overloaded functions for encoder counts
    // TODO Add PIDBackward function
    void PIDForward(double dist);
    void PIDForwardToX(double x);
    void PIDForwardToY(double y);
    void PIDTurn(double angle);
    void PIDTurnToHeading(double heading);

    // TODO Add overloaded functions for encoder counts
    void EncoderForward(double distance, double speed);
    void EncoderBackward(double distance, double speed);
    void EncoderForwardToX(double x, double speed);
    void EncoderForwardToY(double y, double speed);
    void EncoderTurn(double angle, double speed);
    void EncoderTurnToHeading(double heading, double speed);

    void Drive(double speed, double time);
    void DriveTurn(double speedLeft, double speedRight, double time);

    int GetLeftEnc1();
    int GetLeftEnc2();
    int GetRightEnc1();
    int GetRightEnc2();

    void ResetLeftCounts();
    void ResetRightCounts();

    double sigmoid(double x);

    // TODO Test polarity
    void SetLeftPolarity(bool b);
    void SetRightPolarity(bool b);

};

#endif