#include "main.h"

//externs
double sensorsPosLeft, sensorsPosRight, sensorsVelocityLeft, sensorsVelocityRight, sensorsVelocity, sensorsBearing, sensorsAngle, sensorsBearingOffset = 0;
bool sensorsCalibrating = true, sensorsEnable = true;

void sensorsTracker(void *ignore){
    #ifdef DEBUGSENSORS
    printf("Sensors tracker started\n");
    #endif

    Motor leftFront(leftFrontPort, leftFrontGearset, leftFrontEncoder);
    Motor leftMid(leftMidPort, leftMidGearset, leftMidEncoder);
    Motor leftBack(leftBackPort, leftBackGearset, leftBackEncoder);
    Motor rightFront(rightFrontPort, rightFrontGearset, rightFrontEncoder);
    Motor rightMid(rightMidPort, rightMidGearset, rightMidEncoder);
    Motor rightBack(rightBackPort, rightBackGearset, rightBackEncoder);
    Imu inertial(inertialPort);

    leftFront.tare_position();
    leftMid.tare_position();
    leftBack.tare_position();
    rightFront.tare_position();
    rightMid.tare_position();
    rightBack.tare_position();

    while(true){
        if (!inertial.is_calibrating() && sensorsEnable){
            sensorsCalibrating = false;
            sensorsPosLeft = (leftFront.get_position() + leftMid.get_position() + leftBack.get_position())/3;
            sensorsPosRight = (rightFront.get_position() + rightMid.get_position() + rightBack.get_position())/3;

            sensorsVelocityLeft = (leftFront.get_actual_velocity() + leftMid.get_actual_velocity() + leftBack.get_actual_velocity())/3;
            sensorsVelocityRight = (rightFront.get_actual_velocity() + rightMid.get_actual_velocity() + rightBack.get_actual_velocity())/3;
            sensorsVelocity = (sensorsVelocityLeft + sensorsVelocityRight)/2;
            
            sensorsBearing = boundDeg(inertial.get_heading() + sensorsBearingOffset);
            sensorsAngle = boundRad(sensorsBearing*toRadian);
        }
        sensorsCalibrating = inertial.is_calibrating();

        delay(5);
    }
}

void sensorsSetHeading(double bearing){
    sensorsBearingOffset += boundDeg(bearing - sensorsBearing);
    #ifdef DEBUGSENSORS
    printf("sensorsSetHeading | offset: %f\n", sensorsBearingOffset);
    #endif
}

void sensorsTare(){
    #ifdef DEBUGSENSORS
    printf("sensorsTare\n");
    #endif

    Motor leftFront(leftFrontPort, leftFrontGearset, leftFrontEncoder);
    Motor leftMid(leftMidPort, leftMidGearset, leftMidEncoder);
    Motor leftBack(leftBackPort, leftBackGearset, leftBackEncoder);
    Motor rightFront(rightFrontPort, rightFrontGearset, rightFrontEncoder);
    Motor rightMid(rightMidPort, rightMidGearset, rightMidEncoder);
    Motor rightBack(rightBackPort, rightBackGearset, rightBackEncoder);
    
    leftFront.tare_position();
    leftMid.tare_position();
    leftBack.tare_position();
    rightFront.tare_position();
    rightMid.tare_position();
    rightBack.tare_position();
}