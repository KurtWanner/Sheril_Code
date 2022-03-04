#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "CdSSensor.h"
#include "FEHServo.h"
#include "ServoTypes.h"

class RobotClass {
    public:
    Drivetrain drivetrain;
    CdSSensor CdS = CdSSensor(FEHIO::P2_0);
    BurgerFliperServo burgerServo = BurgerFliperServo(FEHServo::Servo0);

    IceCreamTrayServo iceCreamTrayServo = IceCreamTrayServo(FEHServo::Servo2);

    // TODO Eventually deal with order slide
    //OrderSlideServo orderSlideServo = OrderSlideServo(FEHServo::Servo2);
};

#endif