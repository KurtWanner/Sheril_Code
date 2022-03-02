
enum Colors {
    Red,
    Blue,
    None
};

enum StartMenu {
    Testing,
    Run
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



#define RobotWidth 8.3

#define RedMax .31
#define RedMin .29

#define BlueMax .6
#define BlueMin .4

#define StartLightMax .31
#define StartLightMin .29

#define Radius 1.75
#define CountsPerRev 180
#define PI 3.14159265358

#define BurgerRotMax 2445
#define BurgerRotMin 730

#define CountsPerInch 16.6