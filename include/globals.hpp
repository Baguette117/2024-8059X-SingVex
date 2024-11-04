#ifndef _GLOBALS_
#define _GLOBALS_

//LeftFront
#define leftFrontPort 3
#define leftFrontGearset pros::v5::MotorGears::blue
#define leftFrontEncoder pros::v5::MotorEncoderUnits::degrees
//LeftMid
#define leftMidPort -11
#define leftMidGearset pros::v5::MotorGears::blue
#define leftMidEncoder pros::v5::MotorEncoderUnits::degrees

//LeftBack
#define leftBackPort -9
#define leftBackGearset pros::v5::MotorGears::blue
#define leftBackEncoder pros::v5::MotorEncoderUnits::degrees

//RightFront
#define rightFrontPort -13
#define rightFrontGearset pros::v5::MotorGears::blue
#define rightFrontEncoder pros::v5::MotorEncoderUnits::degrees

//RightMid
#define rightMidPort 2
#define rightMidGearset pros::v5::MotorGears::blue
#define rightMidEncoder pros::v5::MotorEncoderUnits::degrees

//RightBack
#define rightBackPort 12
#define rightBackGearset pros::v5::MotorGears::blue
#define rightBackEncoder pros::v5::MotorEncoderUnits::degrees

//intake
#define intakePort 1
#define intakeGearset pros::v5::MotorGears::green
#define intakeEncoder pros::v5::MotorEncoderUnits::degrees

//chain
#define chainPort -10
#define chainGearset pros::v5::MotorGears::green
#define chainEncoder pros::v5::MotorEncoderUnits::degrees

//inertial
#define inertialPort NULL

//measurements
#define rightDist 6.102
#define leftDist 6.102

//pneumatics
#define clampPort 'A'
#endif