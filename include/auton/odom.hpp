#ifndef _ODOM_
#define _ODOM_

//measurements
#define degPerInch 66.8450761
#define degPerDeg 7
#define rightDist 6.5
#define leftDist 6.5

//odom task
void odomTracker(void* ignore);

void odomSetCoords(double x, double y, double bearing);

extern double odomGlobalX, odomGlobalY, globalDeltaY, globalDeltaX, localX, localY, odomRadius, odomPrevPosLeft, odomPrevPosRight, odomDeltaPosLeft, odomDeltaPosRight, odomPrevAngle, odomDeltaAngle;
extern bool odomEnable;
#endif