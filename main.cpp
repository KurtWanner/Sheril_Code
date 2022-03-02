Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@KurtWanner 
KurtWanner
/
Sheril_Code
Public
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Settings
Sheril_Code/Proteus_Project/main.cpp
@KurtWanner
KurtWanner Started structure
Latest commit bef6ca5 26 minutes ago
 History
 1 contributor
62 lines (40 sloc)  982 Bytes
   
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <Drivetrain.h>
#include <FEHSD.h>
#include "CdSSensor.h"

CdSSensor CdS(FEHIO::P2_0);
FEHServo burgerFlip(FEHServo::Servo0);
FEHServo trayFlip(FEHServo::Servo1);

void start(int*, char*, int*);

int main(void)
{
    
    Drivetrain dt;
    int course = 0;
    char region = 'a';
    int iceCream;


    // TODO: Print menu to proteus
    // Testing
    // Start Run 

    {
        start(&course, &region, &iceCream);







    }


    

	return 0;
}

void start(int *course, char *region, int *iceCream){
    /*RPS.InitializeTouchMenu();
    *course = RPS.CurrentCourse();
    *region = RPS.CurrentRegionLetter();
    *iceCream = RPS.GetIceCream();*/

    LCD.Clear();
    LCD.WriteAt("Welcome to Carmen's Dinner!", 5, 5);
    Sleep(2.0);
    LCD.Clear();
    while(!CdS.onStartLight()){
      
        LCD.WriteAt(CdS.Value(), 5,5);
        Sleep(5);
        LCD.Clear();
    
    }   
}
