#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Colors {
    Red,
    Blue,
    None
};

enum StartMenu {
    TestingCode,
    RunCode
};

enum TestingCodes {
    Encoder,
    Forward,
    Backward,
    Left,
    Right,
    GetCdS,
    Stop

};

typedef struct  { //TODO
    double MiddleTop = 20;
} FieldXPositions;


typedef struct  { //TODO
    double Middle = 20;
    double AlignSink = 20;
} FieldYPositions;


typedef struct {
    double a90 = 206.7;

} AngleCounters;

#define a90 206.7



#define RobotWidth 8.0

#define RedMax .31
#define RedMin .29

#define BlueMax .6
#define BlueMin .400

#define StartLightMax 1.0
#define StartLightMin .05

#define Radius 1.75
#define CountsPerRev 180
#define PI 3.14159265358

#define BurgerRotMax 2445
#define BurgerRotMin 730

// TODO Add values
#define IceTrayRotMin 715
#define IceTrayRotMax 1750

#define restAngle 45
#define StartAngle 60
#define DumpAngle 140

#define burgerUp 90 
#define burgerDown 6

#define leverUp 60
#define leverDown 130

// TODO Add values
#define OrderSlideRotMin 1
#define OrderSlideRotMax 1

#define CountsPerInch 16.3

#define SlowSpeed 20

#define LCDBottom 239
#define LCDRight 319

#define TestMenuY 80
#define TestMenuX 100
#define TestMenuYOffset 35
#define TestMenuXOffset 5

#define RPS_WAIT_TIME_IN_SEC 0.35 

#define X_BASELINE 28.9
#define Y_BASELINE 62.6


// Shaft encoding counts for CrayolaBots 

#define COUNTS_PER_INCH 17.63 

#define COUNTS_PER_DEGREE 2.20

// Defines for pulsing the robot 

#define PULSE_TIME 0.08 

#define PULSE_POWER_LEFT 18 
#define PULSE_POWER_RIGHT 18

#define PULSE_TOLERANCE 0.15
#define HEADING_TOLERANCE 1.0

#define radius 1.625 

#define countsPerRotation 180 

#endif