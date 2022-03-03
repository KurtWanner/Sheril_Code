#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <Drivetrain.h>
#include <FEHSD.h>
#include "CdSSensor.h"
#include "Constants.h"
#include "InitializeRobot.h"
#include "Testing.h"

Testing Test;

void start(int*, char*, int*);

void printStartMenu();
int getMenuInput();

void printTestMenu();
int getTestMenuInput();

int main(void)
{
    


    dt.SetLeftPolarity(true);

    int course = 0;
    char region = 'a';
    int iceCream;


    printStartMenu();

    int input = getMenuInput();

    if(input == RunCode){

        dt.Drive(25, 2.0);
        start(&course, &region, &iceCream);

        // Go Up Ramp
        dt.EncoderForward(10, 20);
        dt.EncoderTurn(-90, 20);
        dt.EncoderForward(10, 20);
        dt.EncoderTurn(90, 20);
        dt.EncoderForward(10, 20);


    } else if(input == TestingCode){

        int choice = 1;

        while(choice != Stop){

            printTestMenu();
            choice = getTestMenuInput();
            
            switch(choice){

                case Forward:
                    Test.forwardXInches(10);
                    break;
                case Backward:
                    Test.backwardXInches(10);
                    break;
                case Left:
                    Test.leftXDegrees(90);
                    break;
                case Right:
                    Test.rightXDegrees(90);
                    break;



            }
            LCD.Clear();
            LCD.WriteAt(dt.GetLeftEnc1(), 5, 50);
            LCD.WriteAt(dt.GetLeftEnc2(), 5, 100);
            LCD.WriteAt(dt.GetRightEnc1(), 200, 50);
            LCD.WriteAt(dt.GetRightEnc2(), 200, 100);

            Sleep(.02);
        }

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

void printStartMenu(){
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.DrawLine(0, 120, 319, 120);
    LCD.WriteAt("Testing", 140, 60);
    LCD.WriteAt("Start Run", 140, 180);
}

void printTestMenu(){
    LCD.Clear();
    LCD.DrawLine(0, TestMenuY, LCDRight, TestMenuY);
    LCD.DrawLine(0, 2 * TestMenuY, LCDRight, 2 * TestMenuY);
    LCD.DrawLine(TestMenuX, 0, TestMenuX, LCDBottom);
    LCD.DrawLine(2 * TestMenuX, 0, 2 * TestMenuX, LCDBottom);
    LCD.WriteAt("Enc", TestMenuXOffset, TestMenuYOffset);
    LCD.WriteAt("Forward", TestMenuXOffset + TestMenuX, TestMenuYOffset);
    LCD.WriteAt("Backward", TestMenuXOffset + TestMenuX * 2, TestMenuYOffset);
    LCD.WriteAt("Left", TestMenuXOffset, TestMenuYOffset + TestMenuY);
    LCD.WriteAt("Right", TestMenuXOffset + TestMenuX, TestMenuYOffset + TestMenuY);
    LCD.WriteAt("Return", TestMenuXOffset + TestMenuX * 2, TestMenuYOffset + TestMenuY);
}

int getMenuInput(){
    int x, y;
    bool getXY = false;
    while(!getXY){
        if(LCD.Touch(&x, &y)){
            getXY = true;
        }
    }
    
    if(y < 120){
        return TestingCode;
    } else {
        return RunCode;
    }
}

int getTestMenuInput(){
    int x, y;
    bool getXY = false;
    while(!getXY){
        if(LCD.Touch(&x, &y)){
            getXY = true;
        }
    }




}