#include "main.h"

bool autonwl = false, autonwr = false;

bool calibration(int path){
    Task autonSensorsTask(sensorsTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensors Task");
    Task autonOdomTask(odomTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
    Task autonPIDTask(controlPID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");
    Task autonDebugTask(debugTerminal, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
    bool success = false;
    controlPIDEnable = true;
    debugMode = 0;
    printf("All init\n");
    
    switch (path){
        case 0:
            controlMove(24, 0.125, 1.7, 0);
            controlWait(10000);
            break;

        case 1:
            controlTurn(90, 1.5, 1.3, 0);
            controlWait(10000);
            break;

        case 2:
            controlTurnToPoint(false, 12, 12);
            controlWait(3000);
            controlMoveToPoint(false, 12, 12);
            controlWait(1000);
            controlTurnToPoint(false, 12, 24);
            controlWait(1000);
            controlMoveToPoint(false, 12, 24);
            controlWait(1000);
            break;
    }

    controlPIDEnable = false;
    autonDebugTask.remove();
    autonPIDTask.remove();
    autonOdomTask.remove();
    autonSensorsTask.remove();

    return success;
}

bool redMinus(){
    Task autonSensorsTask(sensorsTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensors Task");
    Task autonOdomTask(odomTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
    Task autonPIDTask(controlPID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");
    Task autonDebugTask(debugTerminal, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
    Motor intake(intakePort, intakeGearset, intakeEncoder);
    Motor chain(chainPort, chainGearset, chainEncoder);
    adi::Pneumatics clamp(clampPort, false, false);
    bool success = false;
    controlPIDEnable = true;
    debugMode = 0;

    clamp.retract();
    controlMove(-21);
    controlWait(1000);
    controlTurnTo(-30);
    controlWait(1000);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    delay(500);
    clamp.extend();
    delay(250);
    controlDrive(0, 0);
    controlPIDEnable = true;
    intake.move(127);
    chain.move(127);
    controlTareTarg();
    controlSpeedCap = 60;
    controlTurnToPoint(false, 35.5, -34, 1.55);
    controlWait(1500);
    controlSpeedCap = defaultSpeedCap;
    controlMoveToPoint(false, 35.5, -34);
    controlWait(1500);
    controlTurnToPoint(false, 37, -48);
    controlWait(1500);
    controlMove(11);
    controlWait(1000);
    controlMove(-4);
    controlWait(500);
    controlTurnTo(215);
    controlWait(1000);
    controlMove(7);
    controlWait(1000);
    controlTurnTo(-80);
    controlWait(1000);
    controlMove(12);
    controlWait(750);
    controlPIDEnable = false;
    controlDrive(40, 40);
    delay(200);
    intake.move(0);
    chain.move(0);
    
    controlPIDEnable = false;
    autonDebugTask.remove();
    autonPIDTask.remove();
    autonOdomTask.remove();
    autonSensorsTask.remove();
    return success;
}

bool redPlus(){
    Task autonSensorsTask(sensorsTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensors Task");
    Task autonOdomTask(odomTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
    Task autonPIDTask(controlPID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");
    Task autonDebugTask(debugTerminal, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
    Motor intake(intakePort, intakeGearset, intakeEncoder);
    Motor chain(chainPort, chainGearset, chainEncoder);
    adi::Pneumatics clamp(clampPort, false, false);
    bool success = false;
    controlPIDEnable = true;
    debugMode = 0;

    clamp.retract();
    controlMove(-21);
    controlWait(1000);
    controlTurnTo(30);
    controlWait(1000);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    delay(500);
    clamp.extend();
    delay(250);
    controlDrive(0, 0);
    controlPIDEnable = true;
    intake.move(127);
    chain.move(127);
    controlTareTarg();
    controlSpeedCap = 60;
    controlTurnToPoint(false, -33.5, -34, 1.55);
    controlWait(1500);
    controlSpeedCap = defaultSpeedCap;
    controlMoveToPoint(false, -33.5, -34);
    controlWait(1500);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    // controlTurnToPoint(true, 12, -52);
    // controlWait(1500);
    // controlSpeedCap = 100;
    // controlMoveToPoint(true, 12, -52);
    // controlWait(2000);
    // controlTurnTo(180);
    // controlWait(1000);

    autonDebugTask.remove();
    autonPIDTask.remove();
    autonOdomTask.remove();
    autonSensorsTask.remove();
    return success;
}

bool blueMinus(){
    Task autonSensorsTask(sensorsTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensors Task");
    Task autonOdomTask(odomTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
    Task autonPIDTask(controlPID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");
    Task autonDebugTask(debugTerminal, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
    Motor intake(intakePort, intakeGearset, intakeEncoder);
    Motor chain(chainPort, chainGearset, chainEncoder);
    adi::Pneumatics clamp(clampPort, false, false);
    bool success = false;
    controlPIDEnable = true;
    debugMode = 0;

    clamp.retract();
    controlMove(-21);
    controlWait(1000);
    controlTurnTo(30);
    controlWait(1000);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    delay(500);
    clamp.extend();
    delay(250);
    controlDrive(0, 0);
    controlPIDEnable = true;
    intake.move(127);
    chain.move(127);
    controlTareTarg();
    controlSpeedCap = 60;
    controlTurnToPoint(false, -35.5, -34, 1.55);
    controlWait(1500);
    controlSpeedCap = defaultSpeedCap;
    controlMoveToPoint(false, -35.5, -34);
    controlWait(1500);
    controlTurnToPoint(false, -37, -48);
    controlWait(1500);
    controlMove(11);
    controlWait(1000);
    controlMove(-4);
    controlWait(500);
    controlTurnTo(145);
    controlWait(1000);
    controlMove(7);
    controlWait(1000);
    controlTurnTo(80);
    controlWait(1000);
    controlMove(12);
    controlWait(750);
    controlPIDEnable = false;
    controlDrive(40, 40);
    delay(200);
    intake.move(0);
    chain.move(0);
    
    controlPIDEnable = false;
    autonDebugTask.remove();
    autonPIDTask.remove();
    autonOdomTask.remove();
    autonSensorsTask.remove();
    return success;
}

bool bluePlus(){
    Task autonSensorsTask(sensorsTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensors Task");
    Task autonOdomTask(odomTracker, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
    Task autonPIDTask(controlPID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");
    Task autonDebugTask(debugTerminal, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
    Motor intake(intakePort, intakeGearset, intakeEncoder);
    Motor chain(chainPort, chainGearset, chainEncoder);
    adi::Pneumatics clamp(clampPort, false, false);
    bool success = false;
    controlPIDEnable = true;
    debugMode = 0;

    clamp.retract();
    controlMove(-21);
    controlWait(1000);
    controlTurnTo(-30);
    controlWait(1000);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    delay(500);
    clamp.extend();
    delay(250);
    controlDrive(0, 0);
    controlPIDEnable = true;
    intake.move(127);
    chain.move(127);
    controlTareTarg();
    controlSpeedCap = 60;
    controlTurnToPoint(false, 33.5, -34, 1.55);
    controlWait(1500);
    controlSpeedCap = defaultSpeedCap;
    controlMoveToPoint(false, 33.5, -34);
    controlWait(1500);
    controlPIDEnable = false;
    controlDrive(-40, -40);
    // controlTurnToPoint(true, 12, -52);
    // controlWait(1500);
    // controlSpeedCap = 100;
    // controlMoveToPoint(true, 12, -52);
    // controlWait(2000);
    // controlTurnTo(180);
    // controlWait(1000);

    autonDebugTask.remove();
    autonPIDTask.remove();
    autonOdomTask.remove();
    autonSensorsTask.remove();
    return success;
}