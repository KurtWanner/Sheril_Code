#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "CdSSensor.h"
#include "FEHServo.h"

class RobotClass {
    public:
    RobotClass();
    Drivetrain dt;
    CdSSensor CdS = CdSSensor(FEHIO::P2_0);
    FEHServo burgerFlip = FEHServo(FEHServo::Servo0);
    FEHServo trayFlip = FEHServo(FEHServo::Servo1);
};

#endif