#ifndef SERVOTYPES_H
#define SERVOTYPES_H

#include "FEHServo.h"
#include "FEHIO.h"
#include "Constants.h"

// Servo class for burger flip mechanism
class BurgerFliperServo: public FEHServo {

    public:
    BurgerFliperServo(FEHServoPort _servo) : FEHServo(_servo){
        SetMin(BurgerRotMin);
        SetMax(BurgerRotMax);
    }
    void flipBurger();
    void returnPlate();
};

// Servo class for lever arm mechanism
class IceCreamTrayServo: public FEHServo {

    public:
    IceCreamTrayServo(FEHServoPort _servo) : FEHServo(_servo){
        SetMin(IceTrayRotMin);
        SetMax(IceTrayRotMax);
    }

    void restingPosition();
    void dumpTray();
    void setBelowLever();
    void setAboveLever();
    void flipLeverFromAbove();
    void flipLeverFromBelow();
    void setToTicket();
};

#endif