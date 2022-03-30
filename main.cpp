#include <FEHLCD.h>
#include <FEHIO.h>
#include "Constants.h"
#include "Testing.h"
#include "Robot.h"
#include "math.h"

void start(int*, char*, int*);

void printStartMenu();
int getMenuInput();

void printTestMenu();
int getTestMenuInput();

void printRPSValues();

void calibrate();

void performanceTestRuns();

RobotClass Robot = RobotClass();

int main(void)
{

    int x, y, i;

    int course = 0;
    char region = 'a';
    int iceCream = -1;

    Testing Test = Testing();
    while(true){

    printStartMenu();

    int input = getMenuInput();

    if(input == RunCode){
        LCD.WriteAt("RunCode", 5, 5);
        /*
        Robot.iceCreamTrayServo.setBelowLever();
        Sleep(5.0);
        Robot.iceCreamTrayServo.setAboveLever();
        Sleep(10.0);
        */
        
        start(&course, &region, &iceCream);

        //Drive towards ramp
        Robot.drivetrain.encoderBackward(15.3, 30);
        Robot.drivetrain.checkX(14.7);
        Robot.drivetrain.encoderLeftMotorTurn(45, 25);
        Robot.drivetrain.checkHeading(270);

        //Drive up ramp
        Robot.drivetrain.encoderBackward(36.3, 35);
        Robot.drivetrain.checkY(55.4);
        
        //turn towards sink
        Robot.drivetrain.encoderRightMotorTurn(90 + 30, 35);
        Robot.drivetrain.checkHeading(30);
        Robot.drivetrain.encoderBackward(1.5, 35);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.encoderRightMotorTurn(11, 25);
        Robot.drivetrain.checkHeading(45);

        //ice cream
        switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderForward(1, 25);
                    break;
                case 1:
                    //turn towards twist
                    Robot.drivetrain.encoderForward(5.3, 25);
                    break;
                case 2:
                    //turn towards chocolate;
                    Robot.drivetrain.encoderForward(8.7, 25);
                    break;
        }

        //go towards ice cream machine
        Robot.drivetrain.encoderRightMotorTurn(-90, 35);
        Robot.drivetrain.checkHeading(315);
        Robot.drivetrain.encoderBackward(2.25, 35);
        
        Sleep(1.0);
        Robot.iceCreamTrayServo.flipLeverFromAbove();
        //Robot.iceCreamTrayServo.SetDegree(135);
        int start = TimeNowSec();
        int end = TimeNowSec();
        Sleep(2.0);
        Robot.iceCreamTrayServo.setAboveLever();

        //Robot.iceCreamTrayServo.setAboveLever();
        Robot.drivetrain.encoderForward(3, 35);           
        Robot.iceCreamTrayServo.setBelowLever();

        Robot.drivetrain.encoderBackward(3, 35);
        while(end - start <= 8){
            end = TimeNowSec();
        }
        
        Robot.iceCreamTrayServo.flipLeverFromBelow();

        // Back away from ice cream
        Sleep(3.0);
        Robot.drivetrain.encoderForward(2.0, 35);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.encoderLeftMotorTurn(45, 35);
        Robot.drivetrain.checkHeading(270);
        switch(iceCream){
            case 0:
                //vanilla
                Robot.drivetrain.encoderBackward(4, 35);
                break;
            case 1:
                // twist
                Robot.drivetrain.encoderBackward(2, 35);
                break;
            case 2:
                // chocolate
                //Robot.drivetrain.encoderForward(2, 35);
            break;
        }
        //turn towards and drive left wall
        Robot.drivetrain.encoderRightMotorTurn(90, 35);
        Robot.drivetrain.checkHeading(0);
        Robot.drivetrain.encoderForwardToX(22.6, 35);
        //turn towards  and drive burger flip
        Robot.drivetrain.encoderRightMotorTurn(90, 35);
        Robot.drivetrain.checkHeading(90);
        Robot.drivetrain.encoderForwardToY(Y_BASELINE, 35);
        //flip the hot plate then return to rest position
        Robot.burgerServo.flipBurger();
        Sleep(2.0);
        Robot.burgerServo.returnPlate();
        while(true){
            printRPSValues();
            Sleep(10);
        }
        

        //Robot.drivetrain.encoderForward(1.5, 35);
        /*
        
        
        start(&course, &region, &iceCream);
        Robot.drivetrain.encoderForward(10, 35);
        //Robot.drivetrain.encoderForwardToX(17, 35);
        Robot.drivetrain.encoderRightMotorTurn(-45, 35);
        Robot.drivetrain.checkHeading(90);
        Robot.drivetrain.encoderForwardToY(55.4, 35);
        Robot.drivetrain.encoderRightMotorTurn(90 + 32.1, 35);
        Robot.drivetrain.checkHeading(32.1);
        Robot.drivetrain.encoderForwardToX(18.9, 35);
        Robot.iceCreamTrayServo.dumpTray();
        */
    
        
       return 0;
        


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

    }
}

void start(int *course, char *region, int *iceCream){
    RPS.InitializeTouchMenu();
    *course = RPS.CurrentCourse();
    *region = RPS.CurrentRegionLetter();
    while(*iceCream < 0){
        *iceCream = RPS.GetIceCream();
    }

    LCD.Clear();
    LCD.WriteAt("Touch To Calibrate", 10, 10);
    int x, y;
    while(!LCD.Touch(&x, &y)){
        printRPSValues();
    }
    WaitForTouch();
    RPS.Calibrate();
    while(!LCD.Touch(&x, &y)){
        printRPSValues();
    }
    
    LCD.Clear();
    LCD.WriteAt("Welcome to Carmen's Dinner!", 5, 5);
    Sleep(1.0);
    LCD.Clear();

    int start = TimeNowSec();
    int end = TimeNowSec();
    while(!Robot.CdS.onStartLight() && (end - start < 30)){
        
        end = TimeNowSec();
        LCD.WriteAt(Robot.CdS.Value(), 5,5);
        LCD.WriteAt(RPS.X(), 5, 32);
        LCD.WriteAt(RPS.Y(), 5, 59);
        LCD.WriteAt(RPS.Heading(), 5, 86);
        Sleep(10);
        LCD.Clear();
    
    }

    Robot.burgerServo.SetDegree(burgerDown);
    Robot.iceCreamTrayServo.restingPosition();    
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
    WaitForTouch(&x, &y);
    return RunCode;
    if(y > 120){
        return TestingCode;
    } else {
        return RunCode;
    }
}

int getTestMenuInput(){
    int x, y;
    WaitForTouch(&x, &y);

    return (int) (x / TestMenuX) + 3 * (int) (y / TestMenuY);

}

void printRPSValues(){
    LCD.Clear();
    LCD.WriteAt(RPS.X(), 5, 5);
    LCD.WriteAt(RPS.Y(), 5, 32);
    LCD.WriteAt(RPS.Heading(), 5, 59);
    LCD.WriteAt(RPS.BaseX(), 100, 5);
    LCD.WriteAt(RPS.BaseY(), 100, 32);
    LCD.WriteAt(RPS.xDiff, 5, 100);
    LCD.WriteAt(RPS.yDiff, 100, 100);
    LCD.WriteAt(X_BASELINE, 5, 130);
    LCD.WriteAt(Y_BASELINE, 100, 130);
}

void performanceTestRuns(){
    int x, y, i;

    int course = 0;
    char region = 'a';
    int iceCream = -1;

        //performance test #2
        // Go Up Ramp        
        Robot.drivetrain.encoderBackward(12.5, 35); // To Middle
        Sleep(0.5);
        Robot.drivetrain.encoderRightMotorTurn(-45, 30);
        //Robot.drivetrain.EncoderTurn(45, 35); // Turn to Ramp
        Sleep(0.5);
        Robot.drivetrain.encoderBackward(34, 35);
        Sleep(0.5);
  

        // Sink Dump
        Robot.drivetrain.encoderLeftMotorTurn(-165, 35); // Turn left
        Sleep(0.5);
        //Robot.drivetrain.EncoderBackward(2.0, 35); // Align with sink
        //Sleep(0.5);
        //Robot.drivetrain.EncoderLeftMotorTurn(-90, 35); // Turn back to sink
        
        //Sleep(0.5);
        Robot.drivetrain.encoderBackward(1, 25); // Back into Sink
        Sleep(0.5);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        
        Robot.drivetrain.encoderForward(8, 35); // Back away from sink
        Sleep(0.5);
        // Order slide
        Robot.drivetrain.encoderLeftMotorTurn(-105, 30);
        
        //Robot.drivetrain.EncoderTurn(-60, 30); //Turn to order
        Sleep(0.5);
        Robot.drivetrain.encoderBackward(3, 30);
        Sleep(0.5);
        Robot.drivetrain.encoderRightMotorTurn(-59, 25);
        Sleep(0.5);
        Robot.iceCreamTrayServo.SetDegree(170);
        Robot.drivetrain.encoderBackward(7.2, 30); //Drive to order
        //Robot.drivetrain.Drive(-30, 1);
        Sleep(0.5);
        Robot.drivetrain.driveTurn(40, -40, 2);
        //Robot.drivetrain.EncoderTurn(65, 35); //Turn to order


        // Hit hot plate
        Robot.drivetrain.encoderForward(30, 30); 
        
        //performance test #3
        //Align with ramp
        Robot.drivetrain.encoderBackward(15.4, 35);
        Robot.drivetrain.checkX(14.8);
        Robot.drivetrain.encoderLeftMotorTurn(45, 35);
        Robot.drivetrain.checkHeading(270);
        printRPSValues();

        //To bottom of ramp
        Robot.drivetrain.encoderBackward(4.3, 35);

        //Go up ramp
        Robot.drivetrain.encoderBackward(28.5, 35);
        printRPSValues();
        Robot.drivetrain.checkHeading(270);
        
        Robot.drivetrain.encoderLeftMotorTurn(-90, 35);
   
        Robot.drivetrain.encoderForward(18.9, 35);
        Robot.drivetrain.checkX(30.8);
        printRPSValues();
        
        Robot.drivetrain.encoderLeftMotorTurn(-90, 35);
        Robot.drivetrain.checkHeading(90);
        printRPSValues();

        Robot.drivetrain.encoderForward(14, 35);
        Robot.drivetrain.checkY(62);
        printRPSValues();
        Sleep(2.0);

        Robot.burgerServo.flipBurger();
        Sleep(3.0);
        Robot.burgerServo.returnPlate();

        
        //perfromance test 4
        start(&course, &region, &iceCream);
        
        
        //Drive towards ramp
        Robot.drivetrain.encoderBackward(15.4, 35);
        Robot.drivetrain.checkX(14.8);
        Robot.drivetrain.encoderLeftMotorTurn(45, 25);
        Robot.drivetrain.checkHeading(270);
        Robot.drivetrain.encoderBackward(4.3, 35);

        //Drive up ramp
        Robot.drivetrain.encoderBackward(31.2, 35);
        Robot.drivetrain.checkY(55.6);
        Robot.iceCreamTrayServo.setAboveLever();

        Robot.drivetrain.encoderLeftMotorTurn(-45, 25);
        Robot.drivetrain.checkHeading(315);

            switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderRightMotorTurn(10, 25);
                    Robot.drivetrain.encoderBackward(2, 25);
                    break;
                case 1:
                    //turn towards twist
                    break;
                case 2:
                    //turn towards chocolate
                    Robot.drivetrain.encoderLeftMotorTurn(17, 25);
                    Robot.drivetrain.encoderBackward(3, 25);
                    break;
            }

            Sleep(2.0);
            Robot.iceCreamTrayServo.flipLeverFromAbove();
            Sleep(8.0);
            Robot.iceCreamTrayServo.setAboveLever();
            Robot.drivetrain.encoderForward(2, 35);           
            Robot.iceCreamTrayServo.setBelowLever();
            Sleep(1.0);
            Robot.drivetrain.encoderBackward(2, 35);
            Robot.iceCreamTrayServo.flipLeverFromBelow();
            Sleep(3.0);
            Robot.drivetrain.encoderForward(2.0, 35);
            

            switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderLeftMotorTurn(10, 25);
                    break;
                case 1:
                    //turn towards twist
                    break;
                case 2:
                    //turn towards chocolate
                    Robot.drivetrain.encoderRightMotorTurn(17, 25);
                    break;
            }

            //turn towards ramp
            Robot.drivetrain.encoderRightMotorTurn(-45, 25);

            //drive down ramp
            Robot.drivetrain.encoderForward(36.2, 35);
            Robot.drivetrain.checkY(23.4);

            //drive towards end button
            Robot.drivetrain.encoderRightMotorTurn(45.0, 25.0);
            Robot.drivetrain.checkHeading(315);
            Robot.drivetrain.encoderForward(50.0, 35.0);
            
}

