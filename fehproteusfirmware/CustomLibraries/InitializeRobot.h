#ifndef INITIALIZEROBOT_H
#define INITIALIZEROBOT_H

#include "Drivetrain.h"
#include "CdSSensor.h"
#include "FEHServo.h"

Drivetrain dt;
CdSSensor CdS(FEHIO::P2_0);
FEHServo burgerFlip(FEHServo::Servo0);
FEHServo trayFlip(FEHServo::Servo1);


#endif