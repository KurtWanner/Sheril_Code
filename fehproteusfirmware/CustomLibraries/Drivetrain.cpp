#include "Drivetrain.h"
#include "FEHMotor.h"
#include "FEHIO.h"
#include "FEHUtility.h"
#include "Constants.h"
#include "math.h"

FEHMotor leftMotor(FEHMotor::Motor0,7.2);
FEHMotor rightMotor(FEHMotor::Motor1,7.2);
DigitalEncoder leftEncoder1(FEHIO::P0_5);
DigitalEncoder leftEncoder2(FEHIO::P0_7);
DigitalEncoder rightEncoder1(FEHIO::P2_2);
DigitalEncoder rightEncoder2(FEHIO::P2_4);

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

void Drivetrain::EncoderForward(double dist, double speed){
    ResetLeftCounts();
    ResetRightCounts();
    leftMotor.SetPercent(speed);
    rightMotor.SetPercent(speed);
    while((GetLeftEnc1() + GetRightEnc1())/2 < dist * CountsPerInch);
    leftMotor.Stop();
    rightMotor.Stop();
}
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

    while(abs(GetLeftEnc1() - GetRightEnc1()) < a90 * angle / 90);

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
