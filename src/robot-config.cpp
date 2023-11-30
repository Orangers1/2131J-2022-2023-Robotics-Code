#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;


controller Controller1 = controller(primary);


motor DiscIntakeMotor = motor(PORT17, ratio18_1, false);
motor CatapultMotor = motor(PORT10, ratio36_1, true);

motor LeftFrontMotor = motor(PORT16, ratio6_1, true);
motor LeftMiddleMotor = motor(PORT14, ratio6_1, true);
motor LeftBackMotor = motor(PORT19, ratio6_1, true);

motor RightFrontMotor = motor(PORT15, ratio6_1, false);
motor RightMiddleMotor = motor(PORT13, ratio6_1, false);
motor RightBackMotor = motor(PORT18, ratio6_1, false);

motor_group leftDrive = motor_group(LeftFrontMotor,  LeftMiddleMotor, LeftBackMotor);
motor_group rightDrive = motor_group(RightFrontMotor,  RightMiddleMotor, RightBackMotor);

motor_group driving = motor_group(LeftFrontMotor,  LeftBackMotor, LeftMiddleMotor, RightFrontMotor, RightMiddleMotor, RightBackMotor);

pneumatics DeployPneumatic1 = pneumatics(Brain.ThreeWirePort.A);
pneumatics DeployPneumatic2 = pneumatics(Brain.ThreeWirePort.B);

optical RollerSensor = optical(PORT9);
distance CatapultSensor = distance(PORT20);
inertial Gyro = inertial(PORT2);

drivetrain drivetrainer = drivetrain(leftDrive, rightDrive);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  RightFrontMotor.setStopping(coast);
    RightMiddleMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    LeftMiddleMotor.setStopping(coast);
    LeftFrontMotor.setStopping(coast);

    DiscIntakeMotor.setStopping(coast);
    CatapultMotor.setStopping(hold);
  // Nothing to initialize
}