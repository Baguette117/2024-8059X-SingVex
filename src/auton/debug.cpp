#include "main.h"

int debugMode = 0b00000000;
int interval = 20;

void debugTerminal(void* ignore){
    Imu inertial(inertialPort);
    Controller master(CONTROLLER_MASTER);

    printf("Debug task started\n");
    while(true){
        if (sensorsCalibrating){
            printf("Inertial is calibrating\n");
            master.print(2, 0, "Inertial is calibrating");
        }else{
            if (debugMode & debugControl) printControl();
            if (debugMode & debugOdom) printOdom();
            if (debugMode & debugSensors) printSensors();
            master.print(0, 0, "%f %f", odomGlobalX, odomGlobalY);
        }
        
        delay(interval);
    }
}

void printControl(){
    printf(
        "PowLeft: %f, PowRight: %f | TargPowLeft: %f, TargPowRight: %f\n"
        "TargLeft: %F, TargRight: %f | ErrorLeft: %f, ErrorRight: %f | DerivLeft: %f, DerivRight: %f\n"
        "TargBearing: %f\n",
        controlPowLeft, controlPowRight, controlTargPowLeft, controlTargPowRight, controlTargLeft, controlTargRight, controlErrorLeft, controlErrorRight, controlDerivLeft, controlDerivRight, controlTargBearing);
}

void printOdom(){
    printf(
        "GlobalX: %f, GlobalY: %f\n"
        "LocalX: %f, LocalY: %f\n"
        "GlobalDeltaX: %.15f, GlobalDeltaY: %.15f\n"
        "PrevPosLeft: %f, PrevPosRight: %f\n"
        "DeltaPosLeft: %.15f, DeltaPosRight: %.15f\n"
        "PrevBearing: %f, DeltaAngle: %.15f\n"
        "radius: %f\n",
        odomGlobalX, odomGlobalY, odomPrevPosLeft, odomPrevPosRight, odomDeltaPosLeft, odomDeltaPosRight, odomPrevAngle, odomDeltaAngle, localX, localY, globalDeltaX, globalDeltaY, odomRadius);
}

void printSensors(){
    printf(
        "LeftPos: %f, RightPos: %f\n"
        "LeftVelocity: %f, RightVelocity: %f, Velocity: %f\n"
        "Bearing: %f, Angle: %f\n",
        sensorsPosLeft, sensorsPosRight, sensorsVelocityLeft, sensorsVelocityRight, sensorsVelocity, sensorsBearing, sensorsAngle);
}