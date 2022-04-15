#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Colors {
    Red,
    Blue,
    None
};

// CdS Cutoffs
#define RedMax .31
#define RedMin .29

#define BlueMax .6
#define BlueMin .400

#define StartLightMax 1.0
#define StartLightMin .05

#define PI 3.14159265358

// Servo max and mins
#define BurgerRotMax 2445
#define BurgerRotMin 730

#define IceTrayRotMin 715
#define IceTrayRotMax 1750

// Standard servo angles
#define restAngle 45
#define StartAngle 60
#define DumpAngle 140

#define burgerUp 90 
#define burgerDown 6

#define leverUp 60
#define leverDown 130

// LCD Constants
#define LCDBottom 239
#define LCDRight 319

// Wait time in between RPS checks
#define RPS_WAIT_TIME_IN_SEC 0.35 

// Standard RPS values used for correction
#define X_BASELINE 28.9
#define Y_BASELINE 62.6

// Shaft encoding counts 
#define COUNTS_PER_INCH 16.3
#define COUNTS_PER_DEGREE 2.20

// Defines for RPS Checks
#define PULSE_TIME 0.08 

#define PULSE_POWER_LEFT 18 
#define PULSE_POWER_RIGHT 18

#define PULSE_TOLERANCE 0.15
#define HEADING_TOLERANCE 1.0

#endif