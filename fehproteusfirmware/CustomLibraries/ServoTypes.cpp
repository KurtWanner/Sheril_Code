#include "ServoTypes.h"
#include "Constants.h"
#include "FEHUtility.h"
#include "FEHLCD.h"

// Burger Flipper
// TODO Add functionality
void BurgerFliperServo::flipBurger(){
        LCD.WriteAt(burgerUp, 5, 5);
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
    LCD.WriteAt(restAngle, 5, 5);
    SetDegree(restAngle);
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
    //LCD.WriteAt(leverDown, 5, 5);
}

// TODO Add functionality
void IceCreamTrayServo::setAboveLever(){
    LCD.WriteAt(leverUp, 5, 5);
    SetDegree(leverUp);
}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromAbove(){
    LCD.WriteAt(leverDown, 5, 5);
    SetDegree(leverDown);
}

// TODO Add functionality
void IceCreamTrayServo::flipLeverFromBelow(){
    LCD.WriteAt(leverUp, 5, 5);
    SetDegree(leverUp);
}

void IceCreamTrayServo::setToTicket(){
    for(int i = 50; i < 180; i++){
        SetDegree(i);
        Sleep(5);
    }
}

