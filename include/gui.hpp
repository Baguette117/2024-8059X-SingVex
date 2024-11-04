#ifndef _GUI_
#define _GUI_

typedef enum {
    calibrationPath = 0,
    redFar = 1,
    redNear = 2,
    redAWP = 3,
    skillsPath = 4,
    blueFar = 5,
    blueNear = 6,
    blueAWP = 7
} autonPaths;
extern autonPaths selectedPath;
void initButtonMatrix();

#endif