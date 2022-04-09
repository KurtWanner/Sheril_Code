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
void fastRun();

float JukeboxX;

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
       while(true){
           LCD.WriteAt(Robot.CdS.Value(), 10, 10);
           Sleep(15);
       }
       */

       Robot.drivetrain.encoderForward(10, 90);
       for(int i = 0; i < 30; i++){
            LCD.Clear();
            LCD.WriteAt("Left 1 Enc:", 5, 5);
            LCD.WriteAt("Left 2 Enc:", 5, 30);
            LCD.WriteAt("Right 1 Enc:", 5, 55);
            LCD.WriteAt("Right 2 Enc:", 5, 80);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc1(), 180, 5);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc2(), 180, 30);
            LCD.WriteAt(Robot.drivetrain.getRightEnc1(), 180, 55);
            LCD.WriteAt(Robot.drivetrain.getRightEnc2(), 180, 80);   
            Sleep(30);
       }
       Robot.drivetrain.encoderBackward(10, 90);
       for(int i = 0; i < 30; i++){
            LCD.Clear();
            LCD.WriteAt("Left 1 Enc:", 5, 5);
            LCD.WriteAt("Left 2 Enc:", 5, 30);
            LCD.WriteAt("Right 1 Enc:", 5, 55);
            LCD.WriteAt("Right 2 Enc:", 5, 80);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc1(), 180, 5);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc2(), 180, 30);
            LCD.WriteAt(Robot.drivetrain.getRightEnc1(), 180, 55);
            LCD.WriteAt(Robot.drivetrain.getRightEnc2(), 180, 80);   
            Sleep(30);
       }

       Robot.drivetrain.encoderLeftMotorTurn(90, 90);
       for(int i = 0; i < 30; i++){
            LCD.Clear();
            LCD.WriteAt("Left 1 Enc:", 5, 5);
            LCD.WriteAt("Left 2 Enc:", 5, 30);
            LCD.WriteAt("Right 1 Enc:", 5, 55);
            LCD.WriteAt("Right 2 Enc:", 5, 80);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc1(), 180, 5);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc2(), 180, 30);
            LCD.WriteAt(Robot.drivetrain.getRightEnc1(), 180, 55);
            LCD.WriteAt(Robot.drivetrain.getRightEnc2(), 180, 80);   
            Sleep(30);
       }
       Robot.drivetrain.encoderRightMotorTurn(90, 90);
       for(int i = 0; i < 30; i++){
            LCD.Clear();
            LCD.WriteAt("Left 1 Enc:", 5, 5);
            LCD.WriteAt("Left 2 Enc:", 5, 30);
            LCD.WriteAt("Right 1 Enc:", 5, 55);
            LCD.WriteAt("Right 2 Enc:", 5, 80);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc1(), 180, 5);
            LCD.WriteAt(Robot.drivetrain.getLeftEnc2(), 180, 30);
            LCD.WriteAt(Robot.drivetrain.getRightEnc1(), 180, 55);
            LCD.WriteAt(Robot.drivetrain.getRightEnc2(), 180, 80);   
            Sleep(30);
       }

       Sleep(30.0);

       



        start(&course, &region, &iceCream);

        //Drive towards ramp
        Robot.drivetrain.encoderBackward(15.7, 30);
        Robot.drivetrain.checkX(14.7);
        Robot.drivetrain.encoderLeftMotorTurn(45, 25);
        Robot.drivetrain.checkHeading(270);

        //Drive up ramp
        Robot.drivetrain.encoderBackward(36, 35);
        Robot.drivetrain.checkY(55.4);
        
        iceCream = RPS.GetIceCream();

        //turn towards sink
        Robot.drivetrain.encoderRightMotorTurn(90 + 31, 35);
        Robot.drivetrain.checkHeading(31);
        Robot.drivetrain.encoderBackward(2, 35);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.encoderRightMotorTurn(11, 25);
        Robot.drivetrain.checkHeading(45);

        //ice cream
        switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderForward(.70, 25);
                    break;
                case 1:
                    //turn towards twist
                    Robot.drivetrain.encoderForward(5, 25);
                    break;
                default:
                    //turn towards chocolate;
                    Robot.drivetrain.encoderForward(8.7, 25);
                    break;
        }

        //go towards ice cream machine
        Robot.drivetrain.encoderRightMotorTurn(-90, 35);
        Robot.drivetrain.checkHeading(315);

        switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderBackward(3.6, 25);
                    break;
                case 1:
                    //turn towards twist
                    Robot.drivetrain.encoderBackward(3.6, 25);
                    break;
                default:
                    //turn towards chocolate;
                    Robot.drivetrain.encoderBackward(3.35, 25);
                    break;
        }
        
        Robot.iceCreamTrayServo.flipLeverFromAbove();
        //Sleep(8.0);
        int start = TimeNowSec();
        int end = TimeNowSec();
        Sleep(3.0);
        Robot.iceCreamTrayServo.setAboveLever();

        Robot.drivetrain.encoderForward(3, 25);           
        Robot.iceCreamTrayServo.SetDegree(140); //Leverdown + 10
        Robot.drivetrain.checkHeading(315);
        LCD.Clear();
        while(end - start < 8){
        
            end = TimeNowSec();
            LCD.WriteAt("Getting Ice Cream...", 5, 5);    
        }
        Robot.drivetrain.encoderBackward(3, 35);
        Robot.iceCreamTrayServo.flipLeverFromBelow();

        // Back away from ice cream
        Sleep(2.0);
        Robot.drivetrain.encoderForward(2.0, 35);
        Robot.iceCreamTrayServo.setAboveLever();
        Robot.drivetrain.encoderRightMotorTurn(45, 35);
        Robot.drivetrain.checkHeading(0);
        
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
        
       switch(iceCream){
            case 0:
                //vanilla
                Robot.drivetrain.encoderForward(4, 20);
                break;
            case 1:
                // twist
                Robot.drivetrain.encoderForward(2, 20);
                break;
            default:
                // chocolate
                Robot.drivetrain.encoderForward(0.5, 20);
                //Robot.drivetrain.encoderForward(2, 35);
                break;
        }

        //drive to left wall
        Robot.drivetrain.checkX(22.3);
        Robot.drivetrain.checkHeading(0);
        Robot.drivetrain.checkX(22.3);

        //Robot.drivetrain.encoderForwardToX(22.6, 35);

        //turn towards/drives hotplate
        Robot.drivetrain.encoderRightMotorTurn(90, 25);
        Robot.drivetrain.checkHeading(90);
        Robot.drivetrain.encoderForwardToY(62.1, 30);
        Robot.drivetrain.checkY(62.1);
        Robot.drivetrain.checkHeading(90);

        //Burger correction
        float diffX = RPS.X();
        while(RPS.X() < 0){
            diffX = RPS.X();
        }

        if(diffX > 29.6){
            Robot.drivetrain.encoderRightMotorTurn(5, 20);
            Robot.drivetrain.leftMotor.SetPercent(20);
            
        } else if(diffX < 29.1){
            Robot.drivetrain.encoderLeftMotorTurn(5, 20);
            Robot.drivetrain.rightMotor.SetPercent(20);
        }
        Sleep(0.5);

        Robot.drivetrain.leftMotor.SetPercent(20);
        Robot.drivetrain.rightMotor.SetPercent(20);
        Sleep(0.75);
        Robot.drivetrain.leftMotor.Stop();
        Robot.drivetrain.rightMotor.Stop();
        

        //flip hotplate
        Robot.burgerServo.SetDegree(80);
        Sleep(2.0);
        Robot.burgerServo.returnPlate();

        //backup and readjust
        Robot.drivetrain.encoderBackward(2, 20);
        Robot.drivetrain.checkHeading(90);
        Robot.iceCreamTrayServo.setToTicket();

        //drive to ticket slider
        //Robot.drivetrain.encoderForwardToY(53, 35);
        Robot.drivetrain.encoderBackward(10, 35);
        Robot.drivetrain.checkY(49.7);
        Robot.drivetrain.driveTurn(-30, 0, 1.0);
        /*
        Robot.drivetrain.encoderRightMotorTurn(14, 20);
        Robot.drivetrain.checkHeading(103);
        */
        //Robot.drivetrain.encoderBackward(2, 35);

        //slide ticket slider
        Robot.drivetrain.drive(-35, 1);
        Robot.drivetrain.driveTurn(50, -5, 0.75);

        //Line up to return to ground level
        Robot.drivetrain.encoderRightMotorTurn(20, 25);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.checkHeading(90);

        //Line up to go down ramp
        Robot.drivetrain.encoderRightMotorTurn(-90, 30);
        Robot.drivetrain.checkHeading(0);
        Robot.drivetrain.encoderBackward(13, 25);
        Robot.drivetrain.checkX(11.1);
        Robot.drivetrain.encoderLeftMotorTurn(90, 30);
        Robot.drivetrain.checkHeading(270);

        //Drive down ramp
        Robot.drivetrain.encoderForward(15+8+2, 35);

        //drive towards jukebox
        Robot.drivetrain.encoderLeftMotorTurn(90, 35);
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.encoderForward(1, 20);
        Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.5));
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.5));
        Robot.drivetrain.encoderRightMotorTurn(90, 35);
        Robot.drivetrain.checkHeading(270);
        //Robot.drivetrain.checkY();

        //read CdS value
        Robot.drivetrain.encoderBackward(3, 25);
        int CdSValue = Robot.readCdSEncoderForward(4, 20);
        LCD.Clear();
        LCD.WriteAt(CdSValue, 5, 5);
        float diffx = 0;
        float angle = 0;
        if(CdSValue == Red){
            Robot.burgerServo.SetDegree(180);
            diffx = RPS.X() - JukeboxX + 0.2;
            angle = atan(diffx / 4.0);
            if (angle > 0){
                Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
            } else {
                Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
            }
        } else {
            Robot.burgerServo.SetDegree(0);
            diffx = RPS.X() - JukeboxX;
            angle = atan(diffx / 4.0);
            if (angle > 0){
                Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
            } else {
                Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
            }
        }
        Sleep(0.75);

        //press button
        Robot.drivetrain.encoderForward(4, 40);
        Robot.drivetrain.encoderBackward(1, 35);
        Robot.drivetrain.checkHeading(270);
        //press button again
        Robot.drivetrain.checkHeading(266);
        Robot.drivetrain.drive(35, 1);
        Robot.drivetrain.encoderBackward(1, 35);
        Robot.drivetrain.checkHeading(270);

        //backup and end run
        Robot.drivetrain.encoderBackward(5, 35); 
        Robot.drivetrain.encoderRightMotorTurn(-90, 35);
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.encoderBackward(3, 35);
        Robot.drivetrain.encoderRightMotorTurn(-45, 35);
        Robot.drivetrain.encoderBackward(50, 50);

        while(true){
            printRPSValues();
            Sleep(10);
        }
    
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
    RPS.Calibrate();
    while(LCD.Touch(&x, &y)){
        printRPSValues();
    }
    while(!LCD.Touch(&x, &y)){
        printRPSValues();
    }

    JukeboxX = RPS.X();
    LCD.Clear();
    LCD.WriteAt(JukeboxX, 5, 5);

    //Final Action
    WaitForTouch();
    
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
    for(int i = 0; i < restAngle; i++){
        Robot.iceCreamTrayServo.SetDegree(i);
        Sleep(10);
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
            
}

void fastRun(){
    int x, y, i;

    int course = 0;
    char region = 'a';
    int iceCream = -1;

    start(&course, &region, &iceCream);

        //Drive towards ramp
        Robot.drivetrain.encoderBackward(15.7, 90);
        Robot.drivetrain.checkX(14.7);
        Robot.drivetrain.encoderLeftMotorTurn(45, 90);
        Robot.drivetrain.checkHeading(270);

        //Drive up ramp
        Robot.drivetrain.encoderBackward(36, 90);
        Robot.drivetrain.checkY(55.4);
        
        iceCream = RPS.GetIceCream();

        //turn towards sink
        Robot.drivetrain.encoderRightMotorTurn(90 + 31, 90);
        Robot.drivetrain.checkHeading(31);
        Robot.drivetrain.encoderBackward(2, 35);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.encoderRightMotorTurn(11, 25);
        Robot.drivetrain.checkHeading(45);

        //ice cream
        switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderForward(.70, 25);
                    break;
                case 1:
                    //turn towards twist
                    Robot.drivetrain.encoderForward(5, 25);
                    break;
                default:
                    //turn towards chocolate;
                    Robot.drivetrain.encoderForward(8.7, 25);
                    break;
        }

        //go towards ice cream machine
        Robot.drivetrain.encoderRightMotorTurn(-90, 90);
        Robot.drivetrain.checkHeading(315);

        switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderBackward(3.6, 25);
                    break;
                case 1:
                    //turn towards twist
                    Robot.drivetrain.encoderBackward(3.6, 25);
                    break;
                default:
                    //turn towards chocolate;
                    Robot.drivetrain.encoderBackward(3.35, 25);
                    break;
        }
        
        Robot.iceCreamTrayServo.flipLeverFromAbove();
        //Sleep(8.0);
        int start = TimeNowSec();
        int end = TimeNowSec();
        Sleep(3.0);
        Robot.iceCreamTrayServo.setAboveLever();

        Robot.drivetrain.encoderForward(3, 25);           
        Robot.iceCreamTrayServo.SetDegree(140); //Leverdown + 10
        Robot.drivetrain.checkHeading(315);
        LCD.Clear();
        while(end - start < 8){
        
            end = TimeNowSec();
            LCD.WriteAt("Getting Ice Cream...", 5, 5);    
        }
        Robot.drivetrain.encoderBackward(3, 35);
        Robot.iceCreamTrayServo.flipLeverFromBelow();

        // Back away from ice cream
        Sleep(2.0);
        Robot.drivetrain.encoderForward(2.0, 35);
        Robot.iceCreamTrayServo.setAboveLever();
        Robot.drivetrain.encoderRightMotorTurn(45, 35);
        Robot.drivetrain.checkHeading(0);
        
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
        Robot.drivetrain.encoderRightMotorTurn(90, 90);
        Robot.drivetrain.checkHeading(0);
        
       switch(iceCream){
            case 0:
                //vanilla
                Robot.drivetrain.encoderForward(4, 20);
                break;
            case 1:
                // twist
                Robot.drivetrain.encoderForward(2, 20);
                break;
            default:
                // chocolate
                Robot.drivetrain.encoderForward(0.5, 20);
                //Robot.drivetrain.encoderForward(2, 35);
                break;
        }

        //drive to left wall
        Robot.drivetrain.checkX(22.3);
        Robot.drivetrain.checkHeading(0);
        Robot.drivetrain.checkX(22.3);

        //Robot.drivetrain.encoderForwardToX(22.6, 35);

        //turn towards/drives hotplate
        Robot.drivetrain.encoderRightMotorTurn(90, 25);
        Robot.drivetrain.checkHeading(90);
        Robot.drivetrain.encoderForwardToY(62.1, 30);
        Robot.drivetrain.checkY(62.1);
        Robot.drivetrain.checkHeading(90);

        //Burger correction
        float diffX = RPS.X();
        while(RPS.X() < 0){
            diffX = RPS.X();
        }

        if(diffX > 29.6){
            Robot.drivetrain.encoderRightMotorTurn(5, 20);
            Robot.drivetrain.leftMotor.SetPercent(20);
            
        } else if(diffX < 29.1){
            Robot.drivetrain.encoderLeftMotorTurn(5, 20);
            Robot.drivetrain.rightMotor.SetPercent(20);
        }
        Sleep(0.5);

        Robot.drivetrain.leftMotor.SetPercent(20);
        Robot.drivetrain.rightMotor.SetPercent(20);
        Sleep(0.75);
        Robot.drivetrain.leftMotor.Stop();
        Robot.drivetrain.rightMotor.Stop();
        

        //flip hotplate
        Robot.burgerServo.SetDegree(80);
        Sleep(2.0);
        Robot.burgerServo.returnPlate();

        //backup and readjust
        Robot.drivetrain.encoderBackward(2, 20);
        Robot.drivetrain.checkHeading(90);
        Robot.iceCreamTrayServo.setToTicket();

        //drive to ticket slider
        //Robot.drivetrain.encoderForwardToY(53, 35);
        Robot.drivetrain.encoderBackward(10, 35);
        Robot.drivetrain.checkY(49.7);
        Robot.drivetrain.driveTurn(-30, 0, 1.0);
        /*
        Robot.drivetrain.encoderRightMotorTurn(14, 20);
        Robot.drivetrain.checkHeading(103);
        */
        //Robot.drivetrain.encoderBackward(2, 35);

        //slide ticket slider
        Robot.drivetrain.drive(-35, 1);
        Robot.drivetrain.driveTurn(50, -5, 0.75);

        //Line up to return to ground level
        Robot.drivetrain.encoderRightMotorTurn(20, 25);
        Robot.iceCreamTrayServo.restingPosition();
        Robot.drivetrain.checkHeading(90);

        //Line up to go down ramp
        Robot.drivetrain.encoderRightMotorTurn(-90, 90);
        Robot.drivetrain.checkHeading(0);
        Robot.drivetrain.encoderBackward(13, 90);
        Robot.drivetrain.checkX(11.1);
        Robot.drivetrain.encoderLeftMotorTurn(90, 90);
        Robot.drivetrain.checkHeading(270);

        //Drive down ramp
        Robot.drivetrain.encoderForward(15+8+2, 90);

        //drive towards jukebox
        Robot.drivetrain.encoderLeftMotorTurn(90, 90);
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.encoderForward(1, 20);
        Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.5));
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.5));
        Robot.drivetrain.encoderRightMotorTurn(90, 35);
        Robot.drivetrain.checkHeading(270);
        //Robot.drivetrain.checkY();

        //read CdS value
        Robot.drivetrain.encoderBackward(3, 25);
        int CdSValue = Robot.readCdSEncoderForward(4, 20);
        LCD.Clear();
        LCD.WriteAt(CdSValue, 5, 5);
        float diffx = 0;
        float angle = 0;
        if(CdSValue == Red){
            Robot.burgerServo.SetDegree(180);
            diffx = RPS.X() - JukeboxX + 0.2;
            angle = atan(diffx / 4.0);
            if (angle > 0){
                Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
            } else {
                Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
            }
        } else {
            Robot.burgerServo.SetDegree(0);
            diffx = RPS.X() - JukeboxX;
            angle = atan(diffx / 4.0);
            if (angle > 0){
                Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
            } else {
                Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
            }
        }
        Sleep(0.75);

        //press button
        Robot.drivetrain.encoderForward(4, 40);
        Robot.drivetrain.encoderBackward(1, 35);
        Robot.drivetrain.checkHeading(270);
        /*//press button again
        Robot.drivetrain.checkHeading(266);
        Robot.drivetrain.drive(35, 1);
        Robot.drivetrain.encoderBackward(1, 35);
        Robot.drivetrain.checkHeading(270);*/

        //backup and end run
        Robot.drivetrain.encoderBackward(5, 35); 
        Robot.drivetrain.encoderRightMotorTurn(-90, 90);
        Robot.drivetrain.checkHeading(180);
        Robot.drivetrain.encoderBackward(3, 35);
        Robot.drivetrain.encoderRightMotorTurn(-45, 35);
        Robot.drivetrain.encoderBackward(50, 90);

        while(true){
            printRPSValues();
            Sleep(10);
        }
}