#include "Drivetrain.h"
#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHUtility.h"
#include "Constants.h"
#include "math.h"
#include "FEHLCD.h"
#include "math.h"

FEHMotor leftMotor(FEHMotor::Motor0,7.2);
FEHMotor rightMotor(FEHMotor::Motor1,7.2);
DigitalEncoder leftEncoder1(FEHIO::P0_1);
DigitalEncoder leftEncoder2(FEHIO::P0_7);
DigitalEncoder rightEncoder1(FEHIO::P2_7);
DigitalEncoder rightEncoder2(FEHIO::P3_4);

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

    return (30 / (1 + pow(e, -(x/5)))) - 15;
}

void Drivetrain::EncoderForward(double dist, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    leftMotor.SetPercent(-speed * 0.88);
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
            leftMotor.SetPercent(0.88 * (-speed - sigmoid(diff)));
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
        Sleep(.02);

    }
    leftMotor.Stop();
    rightMotor.Stop();
}

void Drivetrain::EncoderBackward(double dist, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    leftMotor.SetPercent(speed * 0.88);
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
            leftMotor.SetPercent(0.88 * (speed + sigmoid(diff)));
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
        leftMotor.SetPercent(-speed);
    }

    while(abs(GetLeftEnc1() - GetRightEnc1()) < a90 * abs(angle) / 90){
        LCD.Clear();
        LCD.WriteAt("Left 1 Enc:", 5, 5);
        LCD.WriteAt("Left 2 Enc:", 5, 30);
        LCD.WriteAt("Right 1 Enc:", 5, 55);
        LCD.WriteAt("Right 2 Enc:", 5, 80);
        LCD.WriteAt(GetLeftEnc1(), 100, 5);
        LCD.WriteAt(GetLeftEnc2(), 100, 30);
        LCD.WriteAt(GetRightEnc1(), 100, 55);
        LCD.WriteAt(GetRightEnc2(), 100, 80);    

        LCD.WriteAt("Difference:", 5, 105);
        LCD.WriteAt(GetLeftEnc1() - GetRightEnc1(), 100, 105);

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
