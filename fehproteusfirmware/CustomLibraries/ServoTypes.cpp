#include "ServoTypes.h"
#include "Constants.h"
#include "FEHUtility.h"

// Burger Flipper
// TODO Add functionality
void BurgerFliperServo::flipBurger(){

}

// TODO Add functionality
void BurgerFliperServo::returnPlate(){

}

// Ice Cream Tray
// TODO Add functionality
void IceCreamTrayServo::restingPosition(){
    SetDegree(StartAngle);
}

// TODO Add functionality
void IceCreamTrayServo::dumpTray(){
    for(int i = StartAngle; i < DumpAngle; i++){
        SetDegree(i);
        Sleep(.01);
    }
}

// TODO Add functionality
void IceCreamTrayServo::setBelowLever(){

}

// TODO Add functionality
void IceCreamTrayServo::setAboveLever(){

}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromAbove(){

}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromBelow(){

}

// Order Slide
// TODO Add functionality
void OrderSlideServo::extend(){

}

// TODO Add functionality
void OrderSlideServo::retract(){

}