#ifndef SERVOTYPES_H
#define SERVOTYPES_H

#include "FEHServo.h"
#include "FEHIO.h"
#include "Constants.h"

class BurgerFliperServo: public FEHServo {

    public:
    BurgerFliperServo(FEHServoPort _servo) : FEHServo(_servo){
        SetMin(BurgerRotMin);
        SetMax(BurgerRotMax);
    }
    void flipBurger();
    void returnPlate();
};

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
};

#endif