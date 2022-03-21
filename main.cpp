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
        
        // Go Up Ramp
        
        /*Robot.drivetrain.EncoderBackward(12.5, 35); // To Middle
        Sleep(0.5);
        Robot.drivetrain.EncoderRightMotorTurn(-45, 30);
        //Robot.drivetrain.EncoderTurn(45, 35); // Turn to Ramp
        Sleep(0.5);
        Robot.drivetrain.EncoderBackward(34, 35);
        Sleep(0.5);
  

        // Sink Dump
        Robot.drivetrain.EncoderLeftMotorTurn(-165, 35); // Turn left
        Sleep(0.5);
        //Robot.drivetrain.EncoderBackward(2.0, 35); // Align with sink
        //Sleep(0.5);
        //Robot.drivetrain.EncoderLeftMotorTurn(-90, 35); // Turn back to sink
        
        //Sleep(0.5);
        Robot.drivetrain.EncoderBackward(1, 25); // Back into Sink
        Sleep(0.5);
        Robot.iceCreamTrayServo.dumpTray();
        Sleep(1.0);
        Robot.iceCreamTrayServo.restingPosition();
        
        Robot.drivetrain.EncoderForward(8, 35); // Back away from sink
        Sleep(0.5);
        // Order slide
        Robot.drivetrain.EncoderLeftMotorTurn(-105, 30);
        
        //Robot.drivetrain.EncoderTurn(-60, 30); //Turn to order
        Sleep(0.5);
        Robot.drivetrain.EncoderBackward(3, 30);
        Sleep(0.5);
        Robot.drivetrain.EncoderRightMotorTurn(-59, 25);
        Sleep(0.5);
        Robot.iceCreamTrayServo.SetDegree(170);
        Robot.drivetrain.EncoderBackward(7.2, 30); //Drive to order
        //Robot.drivetrain.Drive(-30, 1);
        Sleep(0.5);
        Robot.drivetrain.DriveTurn(40, -40, 2);
        //Robot.drivetrain.EncoderTurn(65, 35); //Turn to order


        // Hit hot plate
        Robot.drivetrain.EncoderForward(30, 30); */
        
        //performance test #3
        /*


        //Align with ramp
        Robot.drivetrain.EncoderBackward(15.4, 35);
        Robot.drivetrain.check_x(14.8);
        Robot.drivetrain.EncoderLeftMotorTurn(45, 35);
        Robot.drivetrain.check_heading(270);
        printRPSValues();

        //To bottom of ramp
        Robot.drivetrain.EncoderBackward(4.3, 35);

        //Go up ramp
        Robot.drivetrain.EncoderBackward(28.5, 35);
        printRPSValues();
        Robot.drivetrain.check_heading(270);
        
        Robot.drivetrain.EncoderLeftMotorTurn(-90, 35);
   
        Robot.drivetrain.EncoderForward(18.9, 35);
        Robot.drivetrain.check_x(30.8);
        printRPSValues();
        
        Robot.drivetrain.EncoderLeftMotorTurn(-90, 35);
        Robot.drivetrain.check_heading(90);
        printRPSValues();

        Robot.drivetrain.EncoderForward(14, 35);
        Robot.drivetrain.check_y(62);
        printRPSValues();
        Sleep(2.0);

        Robot.burgerServo.flipBurger();
        Sleep(3.0);
        Robot.burgerServo.returnPlate();

        */

        start(&course, &region, &iceCream);
        
        //Drive towards ramp
        Robot.drivetrain.encoderBackward(15.4, 35);
        Robot.drivetrain.checkX(14.8);
        Robot.drivetrain.encoderLeftMotorTurn(45, 35);
        Robot.drivetrain.checkHeading(270);
        Robot.drivetrain.encoderBackward(4.3, 35);

        //Drive up ramp
        Robot.drivetrain.encoderBackward(28.5, 35);
        Robot.drivetrain.checkY(10);
        
        bool iceCreamRead;

        if(iceCream >= 0){
            iceCreamRead = true;
        } else {
            iceCreamRead = false;
        }

        if(iceCreamRead){
            //TODO go to iceCreamFlip

            Robot.drivetrain.encoderBackward(15, 35);
            Robot.drivetrain.checkY(10);
            printRPSValues();
            Robot.drivetrain.encoderLeftMotorTurn(90, 35);
            Robot.drivetrain.encoderBackward(16, 35);
            Robot.drivetrain.encoderLeftMotorTurn(-45, 35);
            Robot.drivetrain.checkHeading(45);
            printRPSValues();
            Robot.drivetrain.encoderBackward(2, 35);


            switch(iceCream){
                case 0:
                    //turn towards vanilla
                    Robot.drivetrain.encoderLeftMotorTurn(-30, 35);
                    break;
                case 1:
                    //turn towards twist
                    break;
                case 2:
                    //turn towards chocolate
                    Robot.drivetrain.encoderRightMotorTurn(-30, 35);
                    break;
            }

            Robot.iceCreamTrayServo.setAboveLever();
            Robot.drivetrain.encoderForward(1, 35);
            Robot.iceCreamTrayServo.flipLeverFromAbove();
            Sleep(1.0);
            Robot.iceCreamTrayServo.setAboveLever();
            Robot.drivetrain.encoderBackward(2, 35);
            Robot.iceCreamTrayServo.setBelowLever();
            Robot.drivetrain.encoderForward(2, 35);
            Sleep(8.0);
            Robot.iceCreamTrayServo.flipLeverFromBelow();
            Sleep(1.0);
            Robot.iceCreamTrayServo.setBelowLever();
        }
        
        /*Robot.iceCreamTrayServo.setAboveLever();
        Sleep(3.0);
        Robot.iceCreamTrayServo.flipLeverFromAbove();
        Sleep(5.0);
        Robot.iceCreamTrayServo.setBelowLever();
        Sleep(3.0);
        Robot.iceCreamTrayServo.flipLeverFromBelow();
        RPS.InitializeTouchMenu();*/
        /*while(true){
            LCD.WriteAt(RPS.X(), 5, 5);
            LCD.WriteAt(RPS.Y(), 5, 32);
            LCD.WriteAt(RPS.Heading(), 5, 59);
            Sleep(10);
        }*/
        
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
    *iceCream = RPS.GetIceCream();
    
    LCD.Clear();
    LCD.WriteAt("Welcome to Carmen's Dinner!", 5, 5);
    Sleep(1.0);
    LCD.Clear();
    
    while(!Robot.CdS.onStartLight()){
      
        LCD.WriteAt(Robot.CdS.Value(), 5,5);
        LCD.WriteAt(RPS.X(), 5, 32);
        LCD.WriteAt(RPS.Y(), 5, 59);
        LCD.WriteAt(RPS.Heading(), 5, 86);
        Sleep(10);
        LCD.Clear();
    
    }

    Robot.burgerServo.SetDegree(BurgerDown);
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
}
