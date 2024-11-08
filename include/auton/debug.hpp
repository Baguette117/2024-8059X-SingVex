#ifndef _DEBUG_
#define _DEBUG_

// #define DEBUGCONTROL
#define DEBUGODOM
// #define DEBUGSENSORS

//debug task
void debugTerminal(void* ignore);

//print values
void printControl();
void printOdom();
void printSensors();

/*
*1st bit: Control
*2nd bit: Odom
*3rd bit: Sensors
*/
enum debugflags {
    debugControl = 1,
    debugOdom = 2,
    debugSensors = 4
};
extern int debugMode;
extern int interval;

#endif