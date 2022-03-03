#include <FEHLCD.h>
#include <FEHIO.h>
#include "Constants.h"
#include "Testing.h"
#include "Robot.h"

void start(int*, char*, int*);

void printStartMenu();
int getMenuInput();

void printTestMenu();
int getTestMenuInput();

RobotClass Robot = RobotClass();

int main(void)
{
    
    Robot.dt.SetLeftPolarity(true);

    int course = 0;
    char region = 'a';
    int iceCream;

    Testing Test = Testing();


    printStartMenu();

    int input = getMenuInput();

    if(input == RunCode){

        //start(&course, &region, &iceCream);

        // Go Up Ramp
        Robot.dt.EncoderForward(5, 20); // To Middle
        Robot.dt.EncoderTurn(45, 20); // Turn to Ramp
        Robot.dt.EncoderForward(20, 20); // Up Ramp

        // Sink Dump
        Robot.dt.EncoderTurn(-90, 20); // Turn left
        Robot.dt.EncoderForward(10, 20); // Align with sink
        Robot.dt.EncoderTurn(90, 20); // Turn back to sink
        Robot.dt.EncoderBackward(10, 20); // Back into Sink
        // trayFlip.dump();
        Robot.dt.EncoderBackward(10, 20); // Back away from sink

        // Order slide
        Robot.dt.EncoderTurn(90, 20); //Turn to order
        Robot.dt.EncoderForward(20, 20); //Drive to order
        Robot.dt.EncoderTurn(90, 20); //Turn to order
        Robot.dt.EncoderForward(10, 20); // Go into order slide
        //burgerFlip.moveOrder();

        // Hit hot plate
        Robot.dt.EncoderBackward(30, 20); 


    } else if(input == TestingCode){

        int choice = 1;

        while(choice != Stop){

            printTestMenu();
            choice = getTestMenuInput();
            
            switch(choice){
                case Encoder:
                    Test.getEncValues();
                    break;
                case Forward:
                    Test.forwardXInches(10.0);
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
    
    while(!Robot.CdS.onStartLight()){
      
        LCD.WriteAt(Robot.CdS.Value(), 5,5);
        Sleep(5);
        LCD.Clear();
    
    }  
    
}

void printStartMenu(){
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.DrawLine(0, 120, LCDRight, 120);
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
    LCD.WriteAt("Get CdS", TestMenuXOffset + TestMenuX * 2, TestMenuYOffset + TestMenuY);
    LCD.WriteAt("Return", TestMenuXOffset, TestMenuYOffset + TestMenuY * 2);

    
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

    return (int) (x / TestMenuX) + 3 * (int) (y / TestMenuY);

}