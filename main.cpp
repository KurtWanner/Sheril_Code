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
    dt.SetLeftPolarity(true);
    int course = 0;
    char region = 'a';
    int iceCream;


    printMenus();

    int input = getMenuInput();

    if(input == Testing){

        dt.ResetLeftCounts();
        dt.ResetRightCounts();

        while(true){
            LCD.Clear();
            LCD.WriteAt(dt.GetLeftEnc1(), 5, 50);
            LCD.WriteAt(dt.GetLeftEnc2(), 5, 100);
            LCD.WriteAt(dt.GetRightEnc1(), 200, 50);
            LCD.WriteAt(dt.GetRightEnc2(), 200, 100);

            Sleep(.02);
        }

        dt.Drive(25, 2.0);

    } else if(input == Run){
        

        start(&course, &region, &iceCream);

        // Go Up Ramp
        dt.EncoderForward(10, 20);
        dt.EncoderTurn(-90, 20);
        dt.EncoderForward(10, 20);
        dt.EncoderTurn(90, 20);
        dt.EncoderForward(10, 20);
        



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
    Sleep(1.0);
    LCD.Clear();
    /*
    while(!CdS.onStartLight()){
      
        LCD.WriteAt(CdS.Value(), 5,5);
        Sleep(5);
        LCD.Clear();
    
    }  
    */ 
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
    while(!LCD.Touch(&x, &y)){
        Sleep(.02);
    }
    while(LCD.Touch(&x, &y)){
        Sleep(.02);
    }
    LCD.WriteAt(y, 50, 50);
    
    return Run;
    if(y < 120){
        return Testing;
    } else {
        return Run;
    }
}