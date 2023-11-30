#pragma once
using namespace vex;

extern brain Brain;

extern controller Controller1;

extern motor LeftFrontMotor;
extern motor LeftMiddleMotor;
extern motor LeftBackMotor;
extern motor RightFrontMotor;
extern motor RightMiddleMotor;
extern motor RightBackMotor;

extern motor DiscIntakeMotor;
extern motor CatapultMotor;

extern pneumatics DeployPneumatic1;
extern pneumatics DeployPneumatic2;
extern inertial Gyro;
extern distance CatapultSensor;

extern optical RollerSensor;

extern motor_group rightDrive;
extern motor_group leftDrive;
extern motor_group driving;

extern drivetrain drivetrainer;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
