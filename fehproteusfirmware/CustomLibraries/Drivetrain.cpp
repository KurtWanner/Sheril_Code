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

void Drivetrain::encoderForward(double dist, double speed){
    resetLeftCounts();
    resetRightCounts();
    leftMotor.SetPercent(speed * 0.88);
    rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        int diff = getRightEnc1() - getLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(getLeftEnc1(), 190, 5);
        LCD.WriteAt(getLeftEnc2(), 190, 30);
        LCD.WriteAt(getRightEnc1(), 190, 55);
        LCD.WriteAt(getRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (speed + sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(speed - sigmoid(diff));
        }
        if(getRightEnc1() > dist * CountsPerInch){
            rightDone = true;
            rightMotor.Stop();
        }
        if(getLeftEnc1() > dist * CountsPerInch){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.01);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

void Drivetrain::encoderBackward(double dist, double speed){
    resetLeftCounts();
    resetRightCounts();
    leftMotor.SetPercent(-speed * 0.88);
    rightMotor.SetPercent(-speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        int diff = getRightEnc1() - getLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(getLeftEnc1(), 190, 5);
        LCD.WriteAt(getLeftEnc2(), 190, 30);
        LCD.WriteAt(getRightEnc1(), 190, 55);
        LCD.WriteAt(getRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (-speed - sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(-speed + sigmoid(diff));
        }
        if(getRightEnc1() > dist * CountsPerInch){
            rightDone = true;
            rightMotor.Stop();
        }
        if(getLeftEnc1() > dist * CountsPerInch){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.02);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

// TODO Add functionality
void Drivetrain::encoderForwardToX(double x, double speed){
    double dist = getDistToX(x);
    double currX = RPS.X();
    double heading = RPS.Heading();
    if(heading < 90 || heading > 270){

    }

}

void Drivetrain::encoderForwardToY(double y, double speed){

}

void Drivetrain::encoderTurn(double angle, double speed){
    resetLeftCounts();
    resetRightCounts();
    if(angle < 0){
        rightMotor.SetPercent(speed);
    } else {
        leftMotor.SetPercent(speed);
    }

    while(abs(getLeftEnc1() - getRightEnc1()) < a90 * abs(angle) / 90){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(getLeftEnc1(), 180, 5);
        LCD.WriteAt(getLeftEnc2(), 180, 30);
        LCD.WriteAt(getRightEnc1(), 180, 55);
        LCD.WriteAt(getRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(getLeftEnc1() - getRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::encoderLeftMotorTurn(double angle, double speed){
    resetLeftCounts();
    resetRightCounts();
    if(angle > 0){
        leftMotor.SetPercent(speed);
    } else {
        leftMotor.SetPercent(-speed);
    }

    while(abs(getLeftEnc1() - getRightEnc1()) < COUNTS_PER_DEGREE * abs(angle)){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(getLeftEnc1(), 180, 5);
        LCD.WriteAt(getLeftEnc2(), 180, 30);
        LCD.WriteAt(getRightEnc1(), 180, 55);
        LCD.WriteAt(getRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(getLeftEnc1() - getRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::encoderRightMotorTurn(double angle, double speed){
    resetLeftCounts();
    resetRightCounts();
    if(angle > 0){
        rightMotor.SetPercent(speed);
    } else {
        rightMotor.SetPercent(-speed);
    }

    while(abs(getLeftEnc1() - getRightEnc1()) < COUNTS_PER_DEGREE * abs(angle)){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(getLeftEnc1(), 180, 5);
        LCD.WriteAt(getLeftEnc2(), 180, 30);
        LCD.WriteAt(getRightEnc1(), 180, 55);
        LCD.WriteAt(getRightEnc2(), 180, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(getLeftEnc1() - getRightEnc1(), 180, 105);

        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::encoderTurnToHeading(double heading, double speed){

}

int Drivetrain::readCdSEncoderForward(double distance, double speed){
    resetLeftCounts();
    resetRightCounts();
    double CdSmin = 3.0;
    leftMotor.SetPercent(speed * 0.88);
    rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    // TODO See if using average of encoders is better
    while(!leftDone || !rightDone){
        if(CdS.Value() < CdSmin){
            CdSmin = CdS.Value();
        }
        int diff = getRightEnc1() - getLeftEnc1();
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt("Left M S", 5, 110);
        LCD.WriteAt("Right M S", 5, 140);
        LCD.WriteAt(getLeftEnc1(), 190, 5);
        LCD.WriteAt(getLeftEnc2(), 190, 30);
        LCD.WriteAt(getRightEnc1(), 190, 55);
        LCD.WriteAt(getRightEnc2(), 190, 80);
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (speed + sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(speed - sigmoid(diff));
        }
        if(getRightEnc1() > dist * CountsPerInch){
            rightDone = true;
            rightMotor.Stop();
        }
        if(getLeftEnc1() > dist * CountsPerInch){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.01);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

void Drivetrain::drive(double speed, double time){
    leftMotor.SetPercent(speed);
    rightMotor.SetPercent(-speed);
    Sleep(time);
    leftMotor.Stop();
    rightMotor.Stop();
}
void Drivetrain::driveTurn(double speedLeft, double speedRight, double time){
    leftMotor.SetPercent(speedLeft);
    rightMotor.SetPercent(speedRight);
    Sleep(time);
    leftMotor.Stop();
    leftMotor.Stop();
}

int Drivetrain::getLeftEnc1(){
    return leftEncoder1.Counts();
}

int Drivetrain::getLeftEnc2(){
    return leftEncoder2.Counts();
}

int Drivetrain::getRightEnc1(){
    return rightEncoder1.Counts();
}

int Drivetrain::getRightEnc2(){
    return rightEncoder2.Counts();
}

void Drivetrain::resetLeftCounts(){
    leftEncoder1.ResetCounts();
    leftEncoder2.ResetCounts();
}

void Drivetrain::resetRightCounts(){
    rightEncoder1.ResetCounts();
    rightEncoder2.ResetCounts();
}

void Drivetrain::SetLeftPolarity(bool b){
    leftMotor.SetPolarity(b);
}

void Drivetrain::SetRightPolarity(bool b){
    rightMotor.SetPolarity(b);
}

void Drivetrain::pulseForward() {
    // Set both motors to desired percent
    rightMotor.SetPercent(PULSE_POWER_RIGHT);
    leftMotor.SetPercent(PULSE_POWER_LEFT);


    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);


    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();

}

void Drivetrain::pulseBackward(){
    // Set both motors to desired percent
    rightMotor.SetPercent(-PULSE_POWER_RIGHT);
    leftMotor.SetPercent(-PULSE_POWER_LEFT);


    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);


    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::pulseClockwise(){
    rightMotor.SetPercent(-PULSE_POWER_RIGHT);
    leftMotor.SetPercent(PULSE_POWER_LEFT);

    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);

    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

// Pulse counterclockwise a short distance using time 
void Drivetrain::pulseCounterclockwise() {
    // Set both motors to desired percent
    rightMotor.SetPercent(PULSE_POWER_RIGHT);
    leftMotor.SetPercent(-PULSE_POWER_LEFT);

    // Wait for the correct number of seconds
    Sleep(PULSE_TIME);

    // Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

// Use RPS to move to the desired x_coordinate based on the orientation of the QR code
void Drivetrain::checkX(float x_coordinate){
    float heading;
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while(RPS.X() == -1 || (RPS.X() < x_coordinate - .5 || RPS.X() > x_coordinate + .55))
    {
        if(RPS.X() != -1){
            heading = RPS.Heading();

            // Pulse the motors for a short duration in the correct direction
            if(RPS.X() > x_coordinate + .5)
            {
                if(heading < 90 || heading > 270){ //Facing right
                    pulseBackward();
                } else { //Facing left
                    pulseForward();
                }
                
            }
            else if((RPS.X() < x_coordinate - .5))
            {
                // Pulse the motors for a short duration in the correct direction
                if(heading < 90 || heading > 270){ //Facing right
                    pulseForward();
                } else {
                    pulseBackward();
                }
                
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
        }
    }
}


// Use RPS to move to the desired y_coordinate based on the orientation of the QR code
void Drivetrain::checkY(float y_coordinate){
    float heading;
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while(RPS.Y() == -1 || (RPS.Y() < y_coordinate -.5 || RPS.Y() > y_coordinate + .5))
    {
        if(RPS.X() != -1){
            heading = RPS.Heading();
            if( RPS.Y() > y_coordinate + .5)
            {
                // Pulse the motors for a short duration in the correct direction
                if(heading > 0 && heading < 180){
                    pulseBackward();
                } else {
                    pulseForward();
                }
            }
            else if((RPS.Y() < y_coordinate - .5))
            {
                if(heading > 0 && heading < 180){
                    pulseForward();
                } else {
                    pulseBackward();
                }
                // Pulse the motors for a short duration in the correct direction
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
        }
    }
}


//Use RPS to move to the desired heading
void Drivetrain::checkHeading(float heading){

   while (RPS.Heading() == -1 || (RPS.Heading() > heading + 1 || RPS.Heading() < heading - 1)){
       if(RPS.X() != -1){
            if(heading == 0){
                if(RPS.Heading() < 5){
                    if(RPS.Heading() > heading + 2){
                        pulseClockwise();
                    }
                }
                else if(RPS.Heading() > 355){
                    if(RPS.Heading() < 360 - 2){
                        pulseCounterclockwise();
                    }
                }
            }
            else {
                if(((RPS.Heading() > heading + 1))){
                    pulseClockwise();
                }
                else if((RPS.Heading() < heading - 1)){
                    pulseCounterclockwise();
                }
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
       }
   }
}
/*
double Drivetrain::getDistToX(double x){
    double diffX = abs(RPS.X() - x);
    double heading = RPS.Heading();

    double diffY = tan(convertToRadians(heading)) * diffX;
    return sqrt(pow(diffX, 2.0) + pow(diffY, 2.0));
}
/*
double Drivetrain::getDistToY(double y){
    double diffY = abs(RPS.Y() - y);
    double heading = RPS.Heading();

    double diffX = diffY / tan(convertToRadians(heading));
    return sqrt(pow(diffX, 2.0) + pow(diffY, 2.0));
}

double convertToRadians(double degree){
    return degree * PI / 180.0;
}

double Drivetrain::getDistToPt(double x, double y){
    double diffX = abs(RPS.X() - x);
    double diffY = abs(RPS.Y() - y);
    if(diffx < .1){
        diffx = 0;
    }
    if(diffx < .1){
        diffy = 0;
    }
    return sqrt(pow(diffX, 2.0) + pow(diffY, 2.0));
}
*/