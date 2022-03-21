#include "Drivetrain.h"
#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHUtility.h"
#include "Constants.h"
#include "math.h"
#include "FEHLCD.h"
#include "math.h"


Drivetrain::Drivetrain(){
    leftMotor.SetPolarity(false);
    rightMotor.SetPolarity(true);
}

void Drivetrain::PIDForward(double dist){

}
void Drivetrain::PIDForwardToX(double x){

}
void Drivetrain::PIDForwardToY(double y){

}
void Drivetrain::PIDTurn(double angle){

}
void Drivetrain::PIDTurnToHeading(double heading){

}

double Drivetrain::sigmoid(double x){
    double e = 2.718;

    return (30 / (1 + pow(e, -(x/8)))) - 15;
}

void Drivetrain::EncoderForward(double dist, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    leftMotor.SetPercent(speed * 0.88);
    rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        int diff = GetRightEnc1() - GetLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(GetLeftEnc1(), 190, 5);
        LCD.WriteAt(GetLeftEnc2(), 190, 30);
        LCD.WriteAt(GetRightEnc1(), 190, 55);
        LCD.WriteAt(GetRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (speed + sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(speed - sigmoid(diff));
        }
        if(GetRightEnc1() > dist * CountsPerInch){
            rightDone = true;
            rightMotor.Stop();
        }
        if(GetLeftEnc1() > dist * CountsPerInch){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.01);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

void Drivetrain::EncoderBackward(double dist, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    leftMotor.SetPercent(-speed * 0.88);
    rightMotor.SetPercent(-speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        int diff = GetRightEnc1() - GetLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(GetLeftEnc1(), 190, 5);
        LCD.WriteAt(GetLeftEnc2(), 190, 30);
        LCD.WriteAt(GetRightEnc1(), 190, 55);
        LCD.WriteAt(GetRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (-speed - sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(-speed + sigmoid(diff));
        }
        if(GetRightEnc1() > dist * CountsPerInch){
            rightDone = true;
            rightMotor.Stop();
        }
        if(GetLeftEnc1() > dist * CountsPerInch){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.02);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

// TODO Add functionality
void Drivetrain::EncoderForwardToX(double x, double speed){

}
void Drivetrain::EncoderForwardToY(double y, double speed){

}
void Drivetrain::EncoderTurn(double angle, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    if(angle < 0){
        rightMotor.SetPercent(speed);
    } else {
        leftMotor.SetPercent(speed);
    }

    while(abs(GetLeftEnc1() - GetRightEnc1()) < a90 * abs(angle) / 90){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(GetLeftEnc1(), 180, 5);
        LCD.WriteAt(GetLeftEnc2(), 180, 30);
        LCD.WriteAt(GetRightEnc1(), 180, 55);
        LCD.WriteAt(GetRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(GetLeftEnc1() - GetRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::EncoderLeftMotorTurn(double angle, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    if(angle > 0){
        leftMotor.SetPercent(speed);
    } else {
        leftMotor.SetPercent(-speed);
    }

    while(abs(GetLeftEnc1() - GetRightEnc1()) < a90 * abs(angle) / 90){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(GetLeftEnc1(), 180, 5);
        LCD.WriteAt(GetLeftEnc2(), 180, 30);
        LCD.WriteAt(GetRightEnc1(), 180, 55);
        LCD.WriteAt(GetRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(GetLeftEnc1() - GetRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::EncoderRightMotorTurn(double angle, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    if(angle > 0){
        rightMotor.SetPercent(speed);
    } else {
        rightMotor.SetPercent(-speed);
    }

    while(abs(GetLeftEnc1() - GetRightEnc1()) < a90 * abs(angle) / 90){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(GetLeftEnc1(), 180, 5);
        LCD.WriteAt(GetLeftEnc2(), 180, 30);
        LCD.WriteAt(GetRightEnc1(), 180, 55);
        LCD.WriteAt(GetRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(GetLeftEnc1() - GetRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::EncoderTurnToHeading(double heading, double speed){

}

void Drivetrain::Drive(double speed, double time){
    leftMotor.SetPercent(speed);
    rightMotor.SetPercent(speed);
    Sleep(time);
    leftMotor.Stop();
    rightMotor.Stop();
}
void Drivetrain::DriveTurn(double speedLeft, double speedRight, double time){
    leftMotor.SetPercent(speedLeft);
    rightMotor.SetPercent(speedRight);
    Sleep(time);
    leftMotor.Stop();
    leftMotor.Stop();
}

int Drivetrain::GetLeftEnc1(){
    return leftEncoder1.Counts();
}

int Drivetrain::GetLeftEnc2(){
    return leftEncoder2.Counts();
}

int Drivetrain::GetRightEnc1(){
    return rightEncoder1.Counts();
}

int Drivetrain::GetRightEnc2(){
    return rightEncoder2.Counts();
}

void Drivetrain::ResetLeftCounts(){
    leftEncoder1.ResetCounts();
    leftEncoder2.ResetCounts();
}

void Drivetrain::ResetRightCounts(){
    rightEncoder1.ResetCounts();
    rightEncoder2.ResetCounts();
}

void Drivetrain::SetLeftPolarity(bool b){
    leftMotor.SetPolarity(b);
}

void Drivetrain::SetRightPolarity(bool b){
    rightMotor.SetPolarity(b);
}

void Drivetrain::pulse_forward(int leftPercent, int rightPercent) 
{
    // Set both motors to desired percent
    rightMotor.SetPercent(rightPercent);
    leftMotor.SetPercent(leftPercent);


    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);


    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();


}

// Pulse counterclockwise a short distance using time 
void Drivetrain::pulse_counterclockwise(int leftPercent, int rightPercent) 
{
    // Set both motors to desired percent
    rightMotor.SetPercent(rightPercent);
    leftMotor.SetPercent(-leftPercent);


    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);


    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

// Use RPS to move to the desired x_coordinate based on the orientation of the QR code
void Drivetrain::check_x(float x_coordinate)
{
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while(RPS.X() >= 0 && (RPS.X() < x_coordinate - .5 || RPS.X() > x_coordinate + .55))
    {
        if(RPS.X() > x_coordinate + .5)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-PULSE_POWER_LEFT, -PULSE_POWER_RIGHT);
        }
        else if(RPS.X() < x_coordinate - .5)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(PULSE_POWER_LEFT, PULSE_POWER_RIGHT);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}


// Use RPS to move to the desired y_coordinate based on the orientation of the QR code
void Drivetrain::check_y(float y_coordinate)
{
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while(RPS.Y() >= 0 && (RPS.Y() < y_coordinate -.5 || RPS.Y() > y_coordinate + .5))
    {
        if( RPS.Y() > y_coordinate + .5)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-PULSE_POWER_LEFT, -PULSE_POWER_RIGHT);
        }
        else if(RPS.Y() < y_coordinate - .5)
        {
            // Pulse the motors for a short duration in the correct direction
           pulse_forward(PULSE_POWER_LEFT, PULSE_POWER_RIGHT);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}


//Use RPS to move to the desired heading
 
void Drivetrain::check_heading(float heading)
{


   while (RPS.Heading() >= 0 && (RPS.Heading() > heading + 1 || RPS.Heading() < heading - 1)){

        if(RPS.Heading() < 5 && heading == 0){
            if(RPS.Heading() > heading + 2){
                pulse_counterclockwise(-PULSE_POWER_LEFT, -PULSE_POWER_RIGHT);
            }
        }
        if(RPS.Heading() > 355 && heading == 0){
            if(RPS.Heading() < 360 - 2){
                pulse_counterclockwise(PULSE_POWER_LEFT, PULSE_POWER_RIGHT);
            }
        }
        if(((RPS.Heading() > heading + 1)) && heading != 0){
            pulse_counterclockwise(-PULSE_POWER_LEFT, -PULSE_POWER_RIGHT);
        }
        else if((RPS.Heading() < heading - 1) && heading != 0){
            pulse_counterclockwise(PULSE_POWER_LEFT, PULSE_POWER_RIGHT);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
   }
}
