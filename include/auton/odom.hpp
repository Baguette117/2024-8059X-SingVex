#ifndef _ODOM_
#define _ODOM_

#define degPerInch 27.779771885
#define degPerDeg 2.848484

//odom task
void odomTracker(void* ignore);

void odomSetCoords(double x, double y, double bearing);

extern double odomGlobalX, odomGlobalY, globalDeltaY, globalDeltaX, localX, localY, odomRadius, odomPrevPosLeft, odomPrevPosRight, odomDeltaPosLeft, odomDeltaPosRight, odomPrevAngle, odomDeltaAngle;
extern bool odomEnable;
#endif