#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <Drivetrain.h>
#include <FEHSD.h>
#include "CdSSensor.h"
#include "Constants.h"

CdSSensor CdS(FEHIO::P2_0);
FEHServo burgerFlip(FEHServo::Servo0);
FEHServo trayFlip(FEHServo::Servo1);

void start(int*, char*, int*);

void printMenus();
int getMenuInput();

int main(void)
{
    
    Drivetrain dt;
    int course = 0;
    char region = 'a';
    int iceCream;

    printMenus();

    int input = getMenuInput();


    if(input == Testing){

    } else if(input == Run){

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

void printMenus(){
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.DrawLine(0, 120, 319, 120);
    LCD.WriteAt("Testing", 140, 60);
    LCD.WriteAt("Start Run", 140, 180);
}

int getMenuInput(){
    int x, y;
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    if(y < 160){
        return Testing;
    } else {
        return Run;
    }
}