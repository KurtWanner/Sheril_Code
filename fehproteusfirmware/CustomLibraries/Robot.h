#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "CdSSensor.h"
#include "FEHServo.h"
#include "ServoTypes.h"

class RobotClass {
    public:

    // Drivetrain initialization
    Drivetrain drivetrain;

    // CdS Initialization
    CdSSensor CdS = CdSSensor(FEHIO::P1_0);

    // Servo initializations
    BurgerFliperServo burgerServo = BurgerFliperServo(FEHServo::Servo0);
    IceCreamTrayServo iceCreamTrayServo = IceCreamTrayServo(FEHServo::Servo2);

    // Used to drive over jukebox
    int readCdSEncoderForward(double distance, double speed);

};

#endif