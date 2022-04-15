#include "ServoTypes.h"
#include "Constants.h"
#include "FEHUtility.h"
#include "FEHLCD.h"

// Burger Flipper
void BurgerFliperServo::flipBurger(){
        LCD.WriteAt(burgerUp, 5, 5);
        SetDegree(burgerUp);

}

// Return burger flip servo
void BurgerFliperServo::returnPlate(){

    // Gradual return
    for(int i = burgerUp; i > burgerDown; i--){
        SetDegree(i);
        Sleep(10);
    }
}

// Default position for lever arm
void IceCreamTrayServo::restingPosition(){
    LCD.WriteAt(restAngle, 5, 5);
    SetDegree(restAngle);
}

// Drop tray into sunk using lever arm
void IceCreamTrayServo::dumpTray(){

    // Gradual drop
    for(int i = StartAngle; i < DumpAngle; i++){
        SetDegree(i);
        Sleep(.01);
    }
}

// Prepare to flip up ice cream lever
void IceCreamTrayServo::setBelowLever(){
    SetDegree(leverDown);
}

// Prepare to flip down ice cream lever
void IceCreamTrayServo::setAboveLever(){
    LCD.WriteAt(leverUp, 5, 5);
    SetDegree(leverUp);
}

// Flip down ice cream lever
void IceCreamTrayServo::flipLeverFromAbove(){
    LCD.WriteAt(leverDown, 5, 5);
    SetDegree(leverDown);
}

// Flip up ice cream lever
void IceCreamTrayServo::flipLeverFromBelow(){
    LCD.WriteAt(leverUp, 5, 5);
    SetDegree(leverUp);
}

// Set lever arm to ground
void IceCreamTrayServo::setToTicket(){
    
    // Gradual drop
    for(int i = 50; i < 180; i++){
        SetDegree(i);
        Sleep(5);
    }
}

