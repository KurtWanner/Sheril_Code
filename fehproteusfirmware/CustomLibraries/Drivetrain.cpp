#include "Drivetrain.h"
#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHUtility.h"
#include "Constants.h"
#include "math.h"
#include "FEHLCD.h"
#include "math.h"
#include "Robot.h"

Drivetrain::Drivetrain(){

    // Set polarity of motors
    leftMotor.SetPolarity(false);
    rightMotor.SetPolarity(true);
}

double convertToRadians(double);

// Used for encoder forward and backward driving
// TODO Explain more
double Drivetrain::sigmoid(double x){
    double e = 2.718;
    return (30 / (1 + pow(e, -(x/8)))) - 15;
}

// Move forward a certain distance at a certain speed using encoders
void Drivetrain::encoderForward(double dist, double speed){
    resetLeftCounts();
    resetRightCounts();
    leftMotor.SetPercent(speed * 0.88);
    rightMotor.SetPercent(speed);

    bool leftDone = false;
    bool rightDone = false;
    int oldLeft1;
    int timeout = 0;

    // Continue until both left and right motors have reached their desired values
    while(!leftDone || !rightDone){

        // If encoder counts haven't updated since last loop,
        if(oldLeft1 == getLeftEnc1()){
        
            // Increment timeout variable
            timeout++;
        } else {
            timeout = 0;
        }

        // If encoder counts haven't update for 30 cycles (0.3 Seconds)
        if(timeout > 30){

            //Exit method
            leftMotor.Stop();
            rightMotor.Stop();
            return;
        }
        
        int diff = getRightEnc1() - getLeftEnc1();
        oldLeft1 = getLeftEnc1();

        printEncoderValues();
        LCD.WriteAt(0.88 * (-speed - sigmoid(diff)), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (speed + sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(speed - sigmoid(diff));
        }
        if(getRightEnc1() > dist * COUNTS_PER_INCH){
            rightDone = true;
            rightMotor.Stop();
        }
        if(getLeftEnc1() > dist * COUNTS_PER_INCH){
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
    int oldLeft1;
    int timeout = 0;

    while(!leftDone || !rightDone){
        
        if(oldLeft1 == getLeftEnc1()){
            timeout++;
        } else {
            timeout = 0;
        }
        if(timeout > 30){
            leftMotor.Stop();
            rightMotor.Stop();
            return;
        }

        int diff = getRightEnc1() - getLeftEnc1();
        oldLeft1 = getLeftEnc1();
        
        printEncoderValues();
        LCD.WriteAt(-speed - sigmoid(diff), 190, 110);
        LCD.WriteAt(speed - sigmoid(diff), 190, 140);
        if(!leftDone){
            leftMotor.SetPercent(0.88 * (-speed - sigmoid(diff)));
        }
        if(!rightDone){
            rightMotor.SetPercent(-speed + sigmoid(diff));
        }
        if(getRightEnc1() > dist * COUNTS_PER_INCH){
            rightDone = true;
            rightMotor.Stop();
        }
        if(getLeftEnc1() > dist * COUNTS_PER_INCH){
            leftDone = true;
            leftMotor.Stop();
        }
        Sleep(.02);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

void Drivetrain::encoderForwardToX(double x, double speed){
    double dist = getDistToX(x);
    double diffX, heading;
    diffX = RPS.X() - x;
    while(RPS.X() < 0){
        diffX = RPS.X() - x;
    }
    heading = RPS.Heading();
    while(RPS.Y() < 0){
        heading = RPS.Heading();
    }
    
    if(heading < 90 || heading > 270){
        if(diffX < 0){
            encoderBackward(dist, speed);
        } else {
            encoderForward(dist, speed);
        }
    } else {
        if(diffX > 0){
            encoderForward(dist, speed);
        } else {
            encoderBackward(dist, speed);
        }
    }
    checkX(x);
}

void Drivetrain::encoderForwardToY(double y, double speed){
    double dist = getDistToY(y);
    double diffY, heading;
    diffY = RPS.Y() - y;
    while(RPS.Y() < 0){
        diffY = RPS.Y() - y;
    }
    heading = RPS.Heading();
    while(RPS.Heading() < 0){
        heading = RPS.Heading();
    }
    if(heading > 0 && heading < 180){
        if(diffY < 0){
            encoderForward(dist, speed);
        } else {
            encoderBackward(dist, speed);
        }
    } else {
        if(diffY > 0){
            encoderForward(dist, speed);
        } else {
            encoderBackward(dist, speed);
        }
    }
}

void Drivetrain::encoderLeftMotorTurn(double angle, double speed){
    resetLeftCounts();
    resetRightCounts();

    int timeout = 0;
    int oldLeft;
    if(angle > 0){
        leftMotor.SetPercent(speed);
    } else {
        leftMotor.SetPercent(-speed);
    }

    while(abs(getLeftEnc1() + getLeftEnc2() - getRightEnc1() - getRightEnc2()) / 2 < COUNTS_PER_DEGREE * abs(angle)){
        if(oldLeft == getLeftEnc1()){
            timeout++;
        } else {
            timeout = 0;
        }
        if(timeout > 10){
            return;
        }

        oldLeft = getLeftEnc1();
        printEncoderValues();
        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();

}

void Drivetrain::encoderRightMotorTurn(double angle, double speed){

    int timeout = 0;
    int oldRight;
    resetLeftCounts();
    resetRightCounts();
    if(angle > 0){
        rightMotor.SetPercent(speed);
    } else {
        rightMotor.SetPercent(-speed);
    }

    while(abs(getLeftEnc1() + getLeftEnc2() - getRightEnc1() - getRightEnc2()) / 2 < COUNTS_PER_DEGREE * abs(angle)){

        if(oldRight == getRightEnc1()){
            timeout++;
        } else {
            timeout = 0;
        }
        if(timeout > 10){
            return;
        }

        oldRight = getRightEnc1();
        printEncoderValues();
        Sleep(.02);
    }

    rightMotor.Stop();
    leftMotor.Stop();
}

void Drivetrain::drive(double speed, double time){
    leftMotor.SetPercent(speed);
    rightMotor.SetPercent(speed);
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

void Drivetrain::printEncoderValues(){
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
    LCD.Clear();
    LCD.WriteAt(PULSE_TOLERANCE, 5, 5);
    float heading;
    int timeOut = 0;
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while((RPS.X() < 0 && RPS.X() > -1.75) || (RPS.X() < x_coordinate - PULSE_TOLERANCE || RPS.X() > x_coordinate + PULSE_TOLERANCE))
    {
        timeOut++;
        LCD.WriteAt(timeOut, 5, 5);
        if(timeOut > 10){
            return;
        }
        if(RPS.X() > 0){
            heading = RPS.Heading();

            // Pulse the motors for a short duration in the correct direction
            if(RPS.X() > x_coordinate + PULSE_TOLERANCE)
            {
                if(heading < 90 || heading > 270){ //Facing right
                    pulseBackward();
                } else { //Facing left
                    pulseForward();
                }
                
            }
            else if((RPS.X() < x_coordinate - PULSE_TOLERANCE))
            {
                // Pulse the motors for a short duration in the correct direction
                if(heading < 90 || heading > 270){ //Facing right
                    pulseForward();
                } else {
                    pulseBackward();
                }
                
            } else {
                LCD.WriteAt("Fuck you robot", 100, 150);
                Sleep(3.0);
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
            LCD.WriteAt("CheckX", 100, 100);
            } else {
                LCD.WriteAt("RPS.X is prob neg", 100, 200);
            }
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
}


// Use RPS to move to the desired y_coordinate based on the orientation of the QR code
void Drivetrain::checkY(float y_coordinate){
    LCD.Clear();
    LCD.WriteAt(PULSE_TOLERANCE, 5, 5);
    int timeout = 0;
    float heading;
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while((RPS.Y() < 0 && RPS.Y() > -1.75) || (RPS.Y() < y_coordinate - PULSE_TOLERANCE || RPS.Y() > y_coordinate + PULSE_TOLERANCE))
    {
        timeout++;
        if(timeout > 10){
            return;
        }
        if(RPS.X() > 0){
            heading = RPS.Heading();
            if( RPS.Y() > y_coordinate + PULSE_TOLERANCE)
            {
                // Pulse the motors for a short duration in the correct direction
                if(heading > 0 && heading < 180){
                    pulseBackward();
                } else {
                    pulseForward();
                }
            }
            else if((RPS.Y() < y_coordinate - PULSE_TOLERANCE))
            {
                if(heading > 0 && heading < 180){
                    pulseForward();
                } else {
                    pulseBackward();
                }
                // Pulse the motors for a short duration in the correct direction
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
            LCD.WriteAt("CheckY", 100, 100);
        }
    }
}


//Use RPS to move to the desired heading
void Drivetrain::checkHeading(float heading){
    int timeout = 0;
    LCD.Clear();
    LCD.WriteAt(HEADING_TOLERANCE, 5, 5);
   while ((RPS.Heading() < 0 && RPS.Heading() > -1.75) || (RPS.Heading() > heading + HEADING_TOLERANCE || RPS.Heading() < heading - HEADING_TOLERANCE)){

       timeout++;
       if(timeout > 10){
           return;
       }
       if(RPS.X() > 0){
            if(heading == 0){
                if(RPS.Heading() < 90){
                    if(RPS.Heading() > heading + HEADING_TOLERANCE){
                        pulseClockwise();
                    }
                }
                else if(RPS.Heading() > 270){
                    if(RPS.Heading() < 360 - HEADING_TOLERANCE){
                        pulseCounterclockwise();
                    }
                }
                if(RPS.Heading() < 1 || RPS.Heading() > 358){
                    return;
                }
            }
            else {
                if(((RPS.Heading() > heading + HEADING_TOLERANCE))){
                    pulseClockwise();
                }
                else if((RPS.Heading() < heading - HEADING_TOLERANCE)){
                    pulseCounterclockwise();
                }
            }
            Sleep(RPS_WAIT_TIME_IN_SEC);
       }
   }
}

double Drivetrain::getDistToX(double x){

    double diffX;
    
    diffX = abs(RPS.X() - x); 
    while(RPS.X() < 0){
        diffX = abs(RPS.X() - x);
    }

    return diffX;
}

double Drivetrain::getDistToY(double y){

    double diffY;
    diffY = abs(RPS.Y() - y);
    while(RPS.Y() < 0){
        diffY = abs(RPS.Y() - y);
    }

    return diffY;
}


double convertToRadians(double degree){
    return degree * PI / 180.0;
}
