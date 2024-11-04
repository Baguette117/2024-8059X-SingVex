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
    
    switch (path){
        case 0:
            controlMove(24);
            controlWait(1000);
            break;

        case 1:
            controlTurn(90);
            controlWait(1000);
            controlMove(12);
            break;

        case 2:
            controlTurnToPoint(false, 12, 12);
            controlWait(3000);
            controlMoveTo(false, 12, 12);
            controlWait(1000);
            controlSetCoords(0, 0, 0);
            controlTurnToPoint(false, 12, 12);
            controlWait(1000);
            controlMoveTo(false, 12, 12);
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