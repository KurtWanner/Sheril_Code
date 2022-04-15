#include <FEHLCD.h>
#include <FEHIO.h>
#include "Constants.h"
#include "Robot.h"
#include "math.h"

// Method prototypes
void start(int *, char *, int *);
void printStartMenu();
void printRPSValues();
void calibrate();

float JukeboxX;

// Robot Initialization
RobotClass Robot = RobotClass();

int main(void){

    int course = 0;
    char region = 'a';
    int iceCream = -1;

    printStartMenu();

    LCD.WriteAt("RunCode", 5, 5);

    start(&course, &region, &iceCream);

    // Drive towards ramp
    Robot.drivetrain.encoderBackward(15.7, 30);
    Robot.drivetrain.checkX(14.7);
    Robot.drivetrain.encoderLeftMotorTurn(45, 25);
    Robot.drivetrain.checkHeading(270);

    // Drive up ramp
    Robot.drivetrain.encoderBackward(36.5, 35);
    Robot.drivetrain.checkY(55.4);

    // Get ice cream flavor in case it has changed since start 
    iceCream = RPS.GetIceCream();

    // Turn towards sink
    Robot.drivetrain.encoderRightMotorTurn(90 + 33, 35);
    Robot.drivetrain.checkHeading(31);
    Robot.drivetrain.encoderBackward(2, 35);

    // Dump tray
    Robot.iceCreamTrayServo.dumpTray();
    Sleep(1.0);
    Robot.iceCreamTrayServo.restingPosition();

    // Line up for ice cream levers
    Robot.drivetrain.encoderRightMotorTurn(11, 25);
    Robot.drivetrain.checkHeading(45);

    // Ice cream distances
    switch (iceCream){
        case 0:
            // Line up with vanilla
            Robot.drivetrain.encoderForward(.70, 25);
            break;
        case 1:
            // Line up with twist
            Robot.drivetrain.encoderForward(5, 25);
            break;
        default:
            // Line up with chocolate;
            Robot.drivetrain.encoderForward(8.7, 25);
            break;
    }

    // Turn towards ice cream lever
    Robot.drivetrain.encoderRightMotorTurn(-90, 35);
    Robot.drivetrain.checkHeading(315);

    switch (iceCream){
        case 0:
            // Drive to vanilla
            Robot.drivetrain.encoderBackward(3.6, 25);
            break;
        case 1:
            // Drive to twist
            Robot.drivetrain.encoderBackward(3.6, 25);
            break;
        default:
            // Drive to chocolate;
            Robot.drivetrain.encoderBackward(3.35, 25);
            break;
    }

    // Flip lever
    Robot.iceCreamTrayServo.flipLeverFromAbove();
    int start = TimeNowSec();
    int end = TimeNowSec();
    Sleep(3.0);

    // Prepare to flip lever up
    Robot.iceCreamTrayServo.setAboveLever();
    Robot.drivetrain.encoderForward(3, 25);
    Robot.iceCreamTrayServo.SetDegree(140); // Leverdown + 10
    Robot.drivetrain.checkHeading(315);
    LCD.Clear();

    // Wait until 8 seconds has elapsed
    while (end - start < 8){
        end = TimeNowSec();
        LCD.WriteAt("Getting Ice Cream...", 5, 5);
    }
    Robot.drivetrain.encoderBackward(3, 35);
    Robot.iceCreamTrayServo.flipLeverFromBelow();

    // Back away from ice cream
    Sleep(2.0);
    Robot.iceCreamTrayServo.SetDegree(140);
    Robot.drivetrain.encoderForward(2.0, 35);
    Robot.drivetrain.encoderRightMotorTurn(45, 35);
    Robot.iceCreamTrayServo.setAboveLever();
    Robot.drivetrain.checkHeading(0);

    // Drive to burger flip
    switch (iceCream){
        case 0:
            // vanilla
            Robot.drivetrain.encoderForward(5.2, 20);
            break;
        case 1:
            // twist
            Robot.drivetrain.encoderForward(2.7, 20);
            break;
        default:
            // chocolate
            Robot.drivetrain.encoderForward(0.5, 20);
            break;
    }

    // Check against left wall
    Robot.drivetrain.checkX(22.3);
    Robot.drivetrain.checkHeading(0);
    Robot.drivetrain.checkX(22.3);

    // Turn towards hotplate
    Robot.drivetrain.encoderRightMotorTurn(90, 25);
    Robot.drivetrain.checkHeading(90);

    // Drive to hotplate
    Robot.drivetrain.encoderForwardToY(62, 30);
    Robot.drivetrain.checkY(62);
    Robot.drivetrain.checkHeading(90);

    // Burger correction
    float diffX = RPS.X();
    while (RPS.X() < 0){
        diffX = RPS.X();
    }

    // If too far right,
    if (diffX > 29.6){

        // Turn left
        Robot.drivetrain.encoderRightMotorTurn(5, 20);
        Robot.drivetrain.leftMotor.SetPercent(20);

    // If too far left
    } else if (diffX < 29.1){

        // Turn right
        Robot.drivetrain.encoderLeftMotorTurn(5, 20);
        Robot.drivetrain.rightMotor.SetPercent(20);
    }
    Sleep(0.5);

    // Straighten out against hotplate
    Robot.drivetrain.leftMotor.SetPercent(20);
    Robot.drivetrain.rightMotor.SetPercent(20);
    Sleep(0.75);
    Robot.drivetrain.leftMotor.Stop();
    Robot.drivetrain.rightMotor.Stop();

    // Flip hotplate
    Robot.burgerServo.SetDegree(85);
    Sleep(2.0);
    Robot.burgerServo.returnPlate();

    // Backup and readjust
    Robot.drivetrain.encoderBackward(2, 20);
    Robot.drivetrain.checkHeading(90);

    // Drop lever arm
    Robot.iceCreamTrayServo.SetDegree(180);

    // Drive to ticket slider
    Robot.drivetrain.encoderBackward(10, 35);
    Robot.drivetrain.checkY(49.5);
    Robot.drivetrain.encoderLeftMotorTurn(-10, 20);
    Robot.drivetrain.encoderBackward(1, 20);
    Robot.drivetrain.driveTurn(-30, 0, 1.0);

    // Slide ticket slider
    Robot.drivetrain.drive(-35, 1);
    Robot.drivetrain.driveTurn(50, -5, 0.75);

    // Line up to return to ground level
    Robot.drivetrain.encoderRightMotorTurn(20, 25);
    Robot.iceCreamTrayServo.setAboveLever();
    Robot.drivetrain.checkHeading(90);

    // Line up to go down ramp
    Robot.drivetrain.encoderRightMotorTurn(-90, 30);
    Robot.drivetrain.checkHeading(0);
    Robot.drivetrain.encoderBackward(13, 25);
    Robot.drivetrain.checkX(11.1);
    Robot.drivetrain.encoderLeftMotorTurn(90, 30);
    Robot.drivetrain.checkHeading(270);

    // Drive down ramp
    Robot.drivetrain.encoderForward(15 + 8 + 2, 35);

    // Drive towards jukebox
    Robot.drivetrain.encoderLeftMotorTurn(90, 35);
    Robot.drivetrain.checkHeading(180);
    Robot.drivetrain.encoderForward(1, 20);

    // Check using calibration value
    Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.3));
    Robot.drivetrain.checkHeading(180);
    Robot.drivetrain.checkX(15.1 + (JukeboxX - 9.3));
    Robot.drivetrain.encoderRightMotorTurn(90, 35);
    Robot.drivetrain.checkHeading(270);

    // Read CdS value
    Robot.drivetrain.encoderBackward(3, 25);
    int CdSValue = Robot.readCdSEncoderForward(4, 20);
    LCD.Clear();
    LCD.WriteAt(CdSValue, 5, 5);

    // Depending on color of jukebox button, use math to turn to correct angle to drive straight to it
    float diffx = 0;
    float angle = 0;
    if (CdSValue == Red){
        Robot.burgerServo.SetDegree(180);
        diffx = RPS.X() - JukeboxX + 0.2;
        angle = atan(diffx / 4.2);
        if (angle > 0){
            Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
        } else {
            Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
        }
    } else {
        Robot.burgerServo.SetDegree(0);
        diffx = RPS.X() - JukeboxX;
        angle = atan(diffx / 4.2);
        if (angle > 0){
            Robot.drivetrain.encoderLeftMotorTurn(angle * 180 / PI, 20);
        } else {
            Robot.drivetrain.encoderRightMotorTurn(abs(angle * 180 / PI), 20);
        }
    }
    Sleep(0.75);

    // Press button
    Robot.drivetrain.encoderForward(4, 40);
    Robot.drivetrain.encoderBackward(1, 35);

    // Reverse angle adjustment
    if (CdSValue == Red){
        if (angle > 0){
            Robot.drivetrain.encoderLeftMotorTurn(-angle * 180 / PI, 20);
        } else {
            Robot.drivetrain.encoderRightMotorTurn(-abs(angle * 180 / PI), 20);
        }
    } else {
        if (angle > 0){
            Robot.drivetrain.encoderLeftMotorTurn(-angle * 180 / PI, 20);
        } else {
            Robot.drivetrain.encoderRightMotorTurn(-abs(angle * 180 / PI), 20);
        }
    }
    Robot.drivetrain.checkHeading(270);

    // Backup and end run
    Robot.drivetrain.encoderBackward(5, 35);
    Robot.drivetrain.encoderRightMotorTurn(-90, 35);
    Robot.drivetrain.encoderBackward(3, 35);
    Robot.drivetrain.encoderRightMotorTurn(-45, 35);
    Robot.drivetrain.encoderBackward(50, 80);

    return 0;
}

// Robot start method
void start(int *course, char *region, int *iceCream){

    // Initialize RPS ang get course, region, and ice cream flavor
    RPS.InitializeTouchMenu();
    *course = RPS.CurrentCourse();
    *region = RPS.CurrentRegionLetter();
    while (*iceCream < 0){
        *iceCream = RPS.GetIceCream();
    }

    // Calibrate RPS values
    LCD.Clear();
    LCD.WriteAt("Touch To Calibrate", 10, 10);
    int x, y;
    while (!LCD.Touch(&x, &y)){
        printRPSValues();
    }
    RPS.Calibrate();
    LCD.ClearBuffer();
    while (LCD.Touch(&x, &y)){
        printRPSValues();
    }
    while (!LCD.Touch(&x, &y)){
        printRPSValues();
    }

    // Get correct jukebox position
    JukeboxX = RPS.X();
    LCD.Clear();
    LCD.WriteAt(JukeboxX, 5, 5);

    // Final Action
    WaitForTouch();

    LCD.Clear();
    LCD.WriteAt("Welcome to Carmen's Dinner!", 5, 5);
    Sleep(1.0);
    LCD.Clear();

    // Wait for startlight or 30 second timeout
    int start = TimeNowSec();
    int end = TimeNowSec();
    while (!Robot.CdS.onStartLight() && (end - start < 30)){

        end = TimeNowSec();
        LCD.WriteAt(Robot.CdS.Value(), 5, 5);
        LCD.WriteAt(RPS.X(), 5, 32);
        LCD.WriteAt(RPS.Y(), 5, 59);
        LCD.WriteAt(RPS.Heading(), 5, 86);
        Sleep(10);
        LCD.Clear();
    }

    // Set servos to starting position
    Robot.burgerServo.SetDegree(burgerDown);

    // Slowly lover lever arm so tray isn't flung out
    for (int i = 0; i < restAngle; i++){
        Robot.iceCreamTrayServo.SetDegree(i);
        Sleep(10);
    }
}

void printStartMenu(){
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Start Run", 140, 180);
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
