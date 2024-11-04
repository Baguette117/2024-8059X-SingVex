#include "main.h"

//externs
double odomGlobalX = 0, odomGlobalY = 0, globalDeltaY, globalDeltaX, localX, localY, odomRadius, odomPrevPosLeft = 0, odomPrevPosRight = 0, odomDeltaPosLeft, odomDeltaPosRight, odomDeltaInchesLeft, odomDeltaInchesRight, odomPrevAngle, odomDeltaAngle;
bool odomEnable = true;

void odomTracker(void *ignore){
    #ifdef DEBUGODOM
    printf("Odom tracker started\n");
    #endif
    
    Controller master(CONTROLLER_MASTER);
    master.clear();

    //Rotating vector
    double odomRotationAngle;

    //Holding variables
    double odomPosLeft, odomPosRight, odomAngle;
    int counter = 0;

    while(true){
        if (sensorsCalibrating){
            odomSetCoords(0, 0, 0);
        } else if (odomEnable){
            odomPosLeft = sensorsPosLeft;
            odomPosRight = sensorsPosRight;
            odomAngle = sensorsAngle;
            odomDeltaPosLeft = odomPosLeft - odomPrevPosLeft;
            odomDeltaPosRight = odomPosRight - odomPrevPosRight;
            odomDeltaInchesLeft = odomDeltaPosLeft/degPerInch;
            odomDeltaInchesRight = odomDeltaPosRight/degPerInch;
            odomDeltaAngle = odomAngle - odomPrevAngle;
            odomRotationAngle = -odomPrevAngle;

            if (odomDeltaAngle > pi){
                odomDeltaAngle = odomDeltaAngle - tau;
            } else if (odomDeltaAngle < -pi){
                odomDeltaAngle = odomDeltaAngle + tau;
            }

            if (odomDeltaAngle != 0){
                odomRadius = odomDeltaInchesRight/odomDeltaAngle + rightDist;

                localX = odomRadius - odomRadius*cos(odomDeltaAngle);
                localY = sin(odomDeltaAngle)*odomRadius;

                globalDeltaX = localX*cos(odomRotationAngle) - localY*sin(odomRotationAngle);
                globalDeltaY = localX*sin(odomRotationAngle) + localY*cos(odomRotationAngle);
            } else {
                localX = 0;
                localY = (odomDeltaPosLeft + odomDeltaPosRight)/2;
                
                globalDeltaX = localX*cos(odomRotationAngle) - localY*sin(odomRotationAngle);
                globalDeltaY = localX*sin(odomRotationAngle) + localY*cos(odomRotationAngle);
            }

            odomGlobalX += globalDeltaX;
            odomGlobalY += globalDeltaY;

            odomPrevPosLeft = odomPosLeft;
            odomPrevPosRight = odomPosRight;
            odomPrevAngle = odomAngle;
            if (!((++counter)%1)){
                master.print(0, 0, "%f %f", odomGlobalX, odomGlobalY);
                master.print(1, 0, "%f", sensorsBearing);
            }

            #ifdef DEBUGODOM
            printf("Δx: %f, Δy: %f\ngΔx: %f, gΔy: %f\nx: %f, y: %f\n", localX, localY, globalDeltaY, globalDeltaX, odomGlobalX, odomGlobalY);
            #endif
            

        }
    }

    delay(5);
}


void odomSetCoords(double x, double y, double bearing){
    #ifdef DEBUGODOM
    printf("odomSetCoords | x: %f, y: %f, bearing: %f\n", x, y, bearing);
    #endif
    
    odomPrevPosLeft = 0;
    odomPrevPosRight = 0;
    odomPrevAngle = boundRad(bearing*toRadian);
    odomGlobalX = x;
    odomGlobalY = y;
    sensorsSetHeading(boundDeg(bearing));
}