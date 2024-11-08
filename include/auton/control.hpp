#ifndef _CONTROL_
#define _CONTROL_

#define defaultKP .155
#define defaultKD 2
#define defaultKI 0
#define defaultTurnKP 1.5
#define defaultTurnKD 1.3
#define defaultTurnKI 0
#define defaultRampingMax 2
#define defaultDistanceTolerance 25
#define defaultBearingTolerance 3
#define defaultVelocityTolerance 2.4
#define defaultSpeedCap 120

//control task
void controlPID(void* ignore);

//basic movement
void controlDrive(double left, double right);
bool controlWait(double timeout);

//relative movements
void controlMove(double inches, double kp = defaultKP, double kd = defaultKD, double ki = defaultKI);
void controlTurn(double degrees, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);

//absolute movements
void controlMoveToPoint(bool backwards, double x, double y, double kp = defaultKP, double kd = defaultKD, double ki = defaultKI);
void controlTurnTo(double bearing, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);
void controlTurnToPoint(bool backwards, double x, double y, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);
void controlTurnClockwiseTo(double bearing, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);
void controlTurnClockwiseToPoint(bool backwards, double x, double y, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);
void controlTurnAnticlockwiseTo(double bearing, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);
void controlTurnAnticlockwiseToPoint(bool backwards, double x, double y, double kp = defaultTurnKP, double kd = defaultTurnKD, double ki = defaultTurnKI);

//other
void controlSetCoords(double x, double y, double bearing);
void controlTareTarg();

extern double controlSpeedCap, controlKP, controlKD, controlKI, controlTurnKP, controlTurnKD, controlTurnKI, controlRampingMax, controlPowLeft, controlPowRight, controlTargPowLeft, controlTargPowRight, controlTargLeft, controlTargRight, controlErrorLeft, controlErrorRight, controlPrevErrorLeft, controlPrevErrorRight, controlDerivLeft, controlDerivRight, controlTargBearing, controlErrorBearing, controlPrevErrorBearing, controlDerivBearing;
extern bool controlPIDEnable, controlTurnMode, controlTurnClockwise;

#endif