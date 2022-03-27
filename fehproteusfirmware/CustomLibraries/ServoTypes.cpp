#include "ServoTypes.h"
#include "Constants.h"
#include "FEHUtility.h"

// Burger Flipper
// TODO Add functionality
void BurgerFliperServo::flipBurger(){
        SetDegree(burgerUp);

}

// TODO Add functionality
void BurgerFliperServo::returnPlate(){
    for(int i = burgerUp; i > burgerDown; i--){
        SetDegree(i);
        Sleep(10);
    }
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
    SetDegree(leverDown);
}

// TODO Add functionality
void IceCreamTrayServo::setAboveLever(){
    SetDegree(leverUp);
}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromAbove(){
    SetDegree(leverDown);
}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromBelow(){
    SetDegree(leverUp);
}

