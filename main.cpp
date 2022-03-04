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

    int x, y;

    Robot.drivetrain.SetLeftPolarity(true);

    int course = 0;
    char region = 'a';
    int iceCream;

    Testing Test = Testing();

    printStartMenu();

    int input = getMenuInput();

    if(input == RunCode){


        //start(&course, &region, &iceCream);
        
        Robot.drivetrain.EncoderForward(5, 50);
        // Go Up Ramp
        /*
        Robot.drivetrain.EncoderForward(8, 35); // To Middle
        Sleep(0.5);
        Robot.drivetrain.EncoderTurn(45, 35); // Turn to Ramp
        Sleep(0.5);
        Robot.drivetrain.EncoderForward(34, 35);
        Sleep(0.5);
  

        // Sink Dump
        Robot.drivetrain.EncoderTurn(-90, 35); // Turn left
        Sleep(0.5);
        Robot.drivetrain.EncoderForward(1.5, 35); // Align with sink
        Sleep(0.5);
        Robot.drivetrain.EncoderTurn(90, 35); // Turn back to sink
        
        Sleep(0.5);
        Robot.drivetrain.EncoderBackward(5.5, 35); // Back into Sink
        Sleep(0.5);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        
        Robot.drivetrain.EncoderForward(1, 35); // Back away from sink
        Sleep(1.0);
        // Order slide
        
        Robot.drivetrain.EncoderTurn(-60, 30); //Turn to order
        Sleep(0.5);
        Robot.drivetrain.EncoderBackward(3, 30);
        Sleep(0.5);
        Robot.drivetrain.EncoderTurn(-30, 25);
        Robot.drivetrain.EncoderBackward(19, 30); //Drive to order
        Sleep(0.5);
        Robot.drivetrain.EncoderTurn(65, 35); //Turn to order

        Robot.iceCreamTrayServo.SetDegree(170);
        
        Robot.drivetrain.EncoderBackward(13.5, 35); // Go into order slide

        Robot.drivetrain.EncoderTurn(45, 30);
        Sleep(1.5);
        Robot.drivetrain.EncoderForward(30, 60);
        
        
        //burgerFlip.moveOrder();

        // Hit hot plate
        Robot.drivetrain.EncoderBackward(30, 20); 
        */
        


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