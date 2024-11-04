#include "main.h"

//externs
double controlSpeedCap = defaultSpeedCap, controlKP = defaultKP, controlKD = defaultKD, controlKI = defaultKI, controlTurnKP = defaultTurnKP, controlTurnKD = defaultTurnKD, controlTurnKI = defaultTurnKI, controlRampingMax = defaultRampingMax;
//wheels
double controlPowLeft, controlPowRight, controlTargPowLeft = 0, controlTargPowRight = 0, controlTargLeft = 0, controlTargRight = 0, controlErrorLeft, controlErrorRight, controlPrevErrorLeft = 0, controlPrevErrorRight = 0, controlDerivLeft, controlDerivRight;
//orientation
double controlTargBearing = 0, controlErrorBearing = 0, controlPrevErrorBearing = 0, controlDerivBearing = 0;
//other
bool controlPIDEnable = false, controlTurnMode = false, controlTurnClockwise;

void controlPID(void *ignore){
    Motor leftFront(leftFrontPort, leftFrontGearset, leftFrontEncoder);
    Motor leftMid(leftMidPort, leftMidGearset, leftMidEncoder);
    Motor leftBack(leftBackPort, leftBackGearset, leftBackEncoder);
    Motor rightFront(rightFrontPort, rightFrontGearset, rightFrontEncoder);
    Motor rightMid(rightMidPort, rightMidGearset, rightMidEncoder);
    Motor rightBack(rightBackPort, rightBackGearset, rightBackEncoder);
    Controller master (CONTROLLER_MASTER);
    master.clear();

    double deltaLeft, deltaRight;

    leftFront.tare_position();
    leftMid.tare_position();
    leftBack.tare_position();
    rightFront.tare_position();
    rightMid.tare_position();
    rightBack.tare_position();

    while(true){
        if (controlPIDEnable && !sensorsCalibrating){
            if (controlTurnMode){
                controlErrorBearing = boundDeg(controlTargBearing - sensorsBearing) - ((controlTurnClockwise)? 0 : 360);
                controlDerivBearing = controlErrorBearing - controlPrevErrorBearing;

                controlTargPowLeft = controlErrorBearing*controlTurnKP + controlDerivBearing*controlTurnKD;

                if (fabs(controlErrorBearing) < defaultBearingTolerance){
                    controlTargPowLeft = absadd(controlTargPowLeft, controlTurnKI);
                }

                controlTargRight = -controlTargPowLeft;

                controlPrevErrorBearing = controlErrorBearing;
            } else {
                controlErrorLeft = controlTargLeft - sensorsPosLeft;
                controlErrorRight = controlTargRight - sensorsPosRight;
                
                controlDerivLeft = controlErrorLeft - controlPrevErrorLeft;
                controlDerivRight = controlErrorRight - controlPrevErrorRight;
                
                controlPrevErrorLeft = controlErrorLeft;
                controlPrevErrorRight = controlErrorRight;

                controlTargPowLeft = controlErrorLeft*controlKP + controlDerivLeft*controlKD;
                controlTargPowRight = controlErrorRight*controlKP + controlDerivRight*controlKD;
            
                if (fabs(controlErrorLeft) < defaultDistanceTolerance && fabs(controlErrorRight) < defaultDistanceTolerance){
                    controlTargPowLeft = absadd(controlTargPowLeft, controlKI);
                    controlTargPowRight = absadd(controlTargPowRight, controlKI);
                }
            }

            deltaLeft = controlTargPowLeft - controlPowLeft;
            deltaRight = controlTargPowRight - controlPowRight;

            controlPowLeft += cap(deltaLeft, controlRampingMax);
            controlPowRight += cap(deltaRight, controlRampingMax);
            controlPowLeft = cap(controlPowLeft, controlSpeedCap);
            controlPowRight = cap(controlPowRight, controlSpeedCap);
            controlDrive(controlPowLeft, controlPowRight);
        }

        #ifdef DEBUGCONTROL
        printf(
        "PowLeft: %f, PowRight: %f | TargPowLeft: %f, TargPowRight: %f\n"
        "TargLeft: %F, TargRight: %f | ErrorLeft: %f, ErrorRight: %f | DerivLeft: %f, DerivRight: %f\n"
        "TargBearing: %f\n",
        controlPowLeft, controlPowRight, controlTargPowLeft, controlTargPowRight, controlTargLeft, controlTargRight, controlErrorLeft, controlErrorRight, controlDerivLeft, controlDerivRight, controlTargBearing);
        #endif

        delay(5);
    }
}


//basic movement
void controlDrive(double left, double right){
    Motor leftFront(leftFrontPort);
    Motor leftMid(leftMidPort);
    Motor leftBack(leftBackPort);
    Motor rightFront(rightFrontPort);
    Motor rightMid(rightMidPort);
    Motor rightBack(rightBackPort);
    
    leftFront.move(left);
    leftMid.move(left);
    leftBack.move(left);
    rightFront.move(right);
    rightMid.move(right);
    rightBack.move(right);
}

bool controlWait(double timeout){
    double start = millis();
    if (controlTurnMode){
        do {
            delay(50);
            if (millis() - start > timeout){
                #ifdef DEBUGCONTROL
                printf("Timeout\n");
                #endif

                return false;
            }
            #ifdef DEBUGCONTROL
            printf("Turning\n");
            #endif

            } while (fabs(controlErrorLeft) > defaultBearingTolerance || fabs(controlErrorRight) > defaultBearingTolerance || fabs(sensorsVelocityLeft) > defaultVelocityTolerance || fabs(sensorsVelocityRight) > defaultVelocityTolerance);
    } else {
        do {
            delay(50);
            if (millis() - start > timeout){
                #ifdef DEBUGCONTROL
                printf("Timeout\n");
                #endif

                return false;
            }
            #ifdef DEBUGCONTROL
            printf("Moving\n");
            #endif

        } while (fabs(controlErrorLeft) > defaultDistanceTolerance || fabs(controlErrorRight) > defaultDistanceTolerance || fabs(sensorsVelocity) > defaultVelocityTolerance);
    }
    return true;
}


//relative movements
void controlMove(double inches, double kp, double kd, double ki){
    double start = millis();
    controlTurnMode = false;
    #ifdef DEBUGCONTROL
    printf("controlMove | inches: %f\n", inches);
    #endif


    controlKP = kp;
    controlKD = kd;
    controlKI = ki;
    controlTargLeft = sensorsPosLeft + inches*degPerInch;
    controlTargRight += sensorsPosRight + inches*degPerInch;
}

void controlTurn(double degrees, double kp, double kd, double ki){
    double start = millis();
    controlTurnMode = true;
    #ifdef DEBUGCONTROL
    printf("controlTurn | degrees: %f\n", degrees);
    #endif


    controlTurnKP = kp;
    controlTurnKD = kd;
    controlTurnKI = ki;
    controlTurnClockwise = degrees > 0;
    controlTargBearing = boundDeg(controlTargBearing + degrees);
}


//absolute movements
void controlMoveTo(bool backwards, double x, double y, double kp, double kd, double ki){
    #ifdef DEBUGCONTROL
    printf("controlMove2 | x: %f\ty: %f\n", x, y);
    #endif

    double diffX = x - odomGlobalX, diffY = y - odomGlobalY;
    double distance = sqrt(diffX*diffX + diffY*diffY);

    if (backwards){
        controlMove(-distance, kp, kd, ki);
    } else {
        controlMove(distance, kp, kd, ki);
    }
}

void controlTurnTo(double bearing, double kp, double kd, double ki){
    controlTurnMode = true;
    #ifdef DEBUGCONTROL
    printf("controlTurnTo | bearing: %f\n", bearing);
    #endif


    double errorBearing = boundDeg(bearing - sensorsBearing);
    if (errorBearing > 180) controlTurnClockwise = false;
    else controlTurnClockwise = true;

    controlTurnKP = kp;
    controlTurnKD = kd;
    controlTurnKI = ki;
    controlTargBearing = bearing;
}

void controlTurnToPoint(bool backwards, double x, double y, double kp, double kd, double ki){
    #ifdef DEBUGCONTROL
    printf("controlTurnToPoint | x: %f\ty: %f\n", x, y);
    #endif

    double diffX = x - odomGlobalX, diffY = y - odomGlobalY;
    double angle = atan2(diffY, diffX);
    double bearing = boundDeg((90 - angle*toDegree) + 180*backwards);
    double errorBearing = boundDeg(bearing - sensorsBearing);
    controlTurnTo(bearing, kp, kd, ki);
}

void controlTurnClockwiseTo(bool backwards, double bearing, double timeout, double kp, double kd, double ki){
    controlTurnMode = true;
    #ifdef DEBUGCONTROL
    printf("controlTurnClockwiseTo | bearing: %f\ttimeout: %f\n", bearing, timeout);
    #endif


    controlTurnClockwise = true;

    controlTurnKP = kp;
    controlTurnKD = kd;
    controlTurnKI = ki;

    controlTargBearing = bearing;
}

void controlTurnClockwiseToPoint(bool backwards, double x, double y, double kp, double kd, double ki){
    #ifdef DEBUGCONTROL
    printf("controlTurnToRightPoint | x: %f\ty: %f\n", x, y);
    #endif

    double diffX = x - odomGlobalX, diffY = y - odomGlobalY;
    double angle = atan2(diffY, diffX);
    double bearing = boundDeg((90 - angle*toDegree) + 180*backwards);
    controlTurnClockwiseTo(bearing, kp, kd, ki);
}

void controlTurnAnticlockwiseTo(double bearing, double kp, double kd, double ki){
    controlTurnMode = true;
    #ifdef DEBUGCONTROL
    printf("controlTurnAnticlockwiseTo | bearing: %f\n", bearing);
    #endif


    controlTurnClockwise = false;

    controlTurnKP = kp;
    controlTurnKD = kd;
    controlTurnKI = ki;

    controlTargBearing = bearing;
}

void controlTurnAnticlockwiseToPoint(bool backwards, double x, double y, bool ideal, double kp, double kd, double ki){
    #ifdef DEBUGCONTROL
    printf("controlTurnToRightPoint | x: %f\ty: %f\n", x, y);
    #endif

    double diffX = x - odomGlobalX, diffY = y - odomGlobalY;
    double angle = atan2(diffY, diffX);
    double bearing = boundDeg((90 - angle*toDegree) + ((backwards)? 180 : 0));
    controlTurnAnticlockwiseTo(bearing, kp, kd, ki);
}

//other
void controlSetCoords(double x, double y, double bearing){
    #ifdef DEBUGCONTROL
    printf("controlSetCoords | x: %f\ty: %f\tbearing: %f\n", x, y, bearing);
    #endif


    Motor leftFront(leftFrontPort, leftFrontGearset, leftFrontEncoder);
    Motor leftMid(leftMidPort, leftMidGearset, leftMidEncoder);
    Motor leftBack(leftBackPort, leftBackGearset, leftBackEncoder);
    Motor rightFront(rightFrontPort, rightFrontGearset, rightFrontEncoder);
    Motor rightMid(rightMidPort, rightMidGearset, rightMidEncoder);
    Motor rightBack(rightBackPort, rightBackGearset, rightBackEncoder);

    sensorsEnable = false;
    odomEnable = false;
    controlPIDEnable = false;

    delay(15);

    sensorsTare();
    odomSetCoords(x, y, bearing);
    controlTargLeft = 0;
    controlTargRight = 0;
    controlTargBearing = boundDeg(bearing);
    odomPrevPosLeft = 0;
    odomPrevPosRight = 0;
    
    sensorsEnable = true;
    odomEnable = true;
    controlPIDEnable = true;

    delay(15);
}

void controlTareTarg(){
    controlPIDEnable = false;

    delay(15);
    controlTargLeft = sensorsPosLeft;
    controlTargRight = sensorsPosRight;
    controlTargBearing = sensorsBearing;
    controlPIDEnable = true;

    delay(15);
}