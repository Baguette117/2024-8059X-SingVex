#ifndef _GUI_
#define _GUI_

typedef enum {
    calibrationPath = 0,
    redMinusPath,
    redPlusPath,
    redAWPPath,
    skillsPath,
    blueMinusPath,
    bluePlusPath,
    blueAWPPath
} autonPaths;
extern autonPaths selectedPath;
void initButtonMatrix();

#endif