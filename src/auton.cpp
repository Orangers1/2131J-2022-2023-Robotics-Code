#include "vex.h"
#include <iostream>
#include "PID.h"
int autonToRun = -1;


typedef struct _button
{
  int xpos;
  int ypos;
  int width;
  int height;
  bool state;
  vex::color offColor;
  vex::color onColor;
  const char *label;
} button;

bool colorChoice = false;
// buttons
button buttons[] = {
  // x  y   width  height, starts false, color when false, color when true, 
  // for more buttons add a comma after the }
  // 0x3238db is a blue color - use a hex code picker have 0x before it
  { 30, 30, 60, 60, false, 0xE00000, 0x0000E0, "Color" },
  { 120, 30, 60, 60, false, 0x951b3e, 0x1b9572, "Left" },
  { 210, 30, 60, 60, false, 0x951b3e, 0x1b9572, "Skill" },
  { 300, 30, 60, 60, false, 0x951b3e, 0x1b9572, "Troll" },
  { 390, 30, 60, 60, false, 0x951b3e, 0x1b9572, "None"},
  { 210, 150, 60, 60, false, 0x951b3e, 0x1b9572, "Home"}
};


void displayButtonControls(int index, bool pressed );

int findButton( int16_t xpos, int16_t ypos )
{
    int nButtons = sizeof(buttons) / sizeof(button);
    for ( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
       continue;
 
      return(index);
    }
    return (-1); 
}

void initButtons()
{
  int nButtons = sizeof(buttons) / sizeof(button);

  for( int index=0;index < nButtons;index++) {
    buttons[index].state = false;
  }
}

void userTouchCallbackPressed() {
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();

  if( (index = findButton( xpos, ypos )) >= 0 ) {
    displayButtonControls( index, true );
  }
}

void userTouchCallbackReleased() {
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();

  if( (index = findButton( xpos, ypos )) >= 0 ) {

    if( buttons[index].state == true) {
      buttons[index].state = false;
    }
    else 
    {
      buttons[index].state = true;
    }
    
    autonToRun = index;

    displayButtonControls( index, false );
  }
}

void displayButtonControls( int index, bool pressed ) {
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  
  for(int i=0; i<sizeof(buttons)/sizeof(button);i++) {

    if( buttons[i].state )
      c = buttons[i].onColor;
    else
      c = buttons[i].offColor;

    Brain.Screen.setFillColor( c );

    if( i == index && pressed == true) {
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
    }
    else
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );
  
    Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

    if( buttons[i].label != NULL )
      Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
  }
}
// mini functions to run in the actual ones.



double rightDriveAvg() {

double rightDriveAverage = 0;
int rightFPos = 0;
int rightMPos = 0;
int rightBPos = 0;
if(RightFrontMotor.position(degrees) < 0) {
  rightFPos = -RightFrontMotor.position(degrees);
}
else {
    rightFPos = RightFrontMotor.position(degrees);
}

if(RightBackMotor.position(degrees) < 0) {
  rightBPos = -RightBackMotor.position(degrees);
}else {
    rightBPos = RightBackMotor.position(degrees);

}
rightDriveAverage = (rightFPos + rightBPos + rightMPos)/3;
  return rightDriveAverage;
}

double leftDriveAvg() {

double leftDriveAverage = 0;
int leftFPos = 0;
int leftMPos = 0;
int leftBPos = 0;
if(LeftFrontMotor.position(degrees) < 0) {
  leftFPos = -LeftFrontMotor.position(degrees);
}
else {
    leftFPos = LeftFrontMotor.position(degrees);
}

if(LeftBackMotor.position(degrees) < 0) {
 leftBPos = -LeftBackMotor.position(degrees);
}else {
    leftBPos = LeftBackMotor.position(degrees);

}
leftDriveAverage = (leftFPos + leftBPos + leftMPos)/3;
  return leftDriveAverage;
}


// actual autonomous functions
void trolls ()
{
  Controller1.Screen.print("Read the Brain");
  Brain.Screen.printAt( 0, 200, "     Gotem      ");
}


void skills() {
 
}
void rightAuton(bool colorc){
  // if colorc = true then on blue team. otherwise red.
  // shoot preloads
  // turn around and strafe to do the roller

}
void leftAuton(bool colorc){
  // if colorc = true then on blue team. otherwise red.
  // shoot preloads
  // turn around and do the roller
  driving.spinFor(fwd, 100, deg);
  DiscIntakeMotor.setVelocity(15, pct);
  DiscIntakeMotor.spinFor(fwd, 125, deg);


}
void HomeWinPoint (bool colorc){
  // start up the shooter
  // do the roller that you start on.
  // back up a little, turn, shoot.
  // after shot pre-loads turn right and go to the other roller, intake 3 along the way.
  // then shoot the 3 more after 2nd roller if time permits.
}
void sevenStepRamp(double target, double maxSpeed) {
  double currentSpeed;
  double error;


  double currentPosition;
double leftavg = leftDriveAvg();
double rightavg = rightDriveAvg();

if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
currentSpeed = driving.velocity(pct);

int i = 0;
// step 1
while (currentSpeed < maxSpeed/4) { // e^x essentially
  // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
driving.setVelocity(exp((.2) * i),  pct);
i++;
}
std::cout << "Finished step 1, " << currentSpeed << " , " << error <<  std::endl;
double e;
e = driving.velocity(pct);
// step 2
while (currentSpeed < maxSpeed - (maxSpeed/4)) { // linear
  // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
driving.setVelocity(e,  pct);
e = e + 1;
}
std::cout << "Finished step 2, " << currentSpeed << " , " << error <<  std::endl;

// step 3
while (currentSpeed < maxSpeed) { // -e^-x
    // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
driving.setVelocity(-exp((.2) * -i),  pct);
i++;
}
std::cout << "Finished step 3, " << currentSpeed << " , " << error <<  std::endl;
e = driving.velocity(pct);
// step 4
while (error < target) { // flat at max speed until error.
    // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
}
std::cout << "Finished step 4, " << error <<  std::endl;

// step 5
while (currentSpeed > maxSpeed - (maxSpeed/4)) { // -e^x
    // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
driving.setVelocity(-exp((.2) * i),  pct);
i--;
}
std::cout << "Finished step 5, " << currentSpeed <<  std::endl;

// step 6
while (currentSpeed > maxSpeed/4) { // negative linear.
    // updating variables
driving.setVelocity(e,  pct);
e = e - 1;
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.

}
std::cout << "Finished step 6, " << currentSpeed <<  std::endl;

// step 7
while (currentSpeed > 0) { // e ^ -x
    // updating variables
currentSpeed = driving.velocity(pct);
leftavg = leftDriveAvg();
rightavg = rightDriveAvg();
if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
currentPosition = (leftavg + rightavg) / 2;
error = target - currentPosition;
// end of updating variables.
driving.setVelocity(exp((.2) * -i),  pct);
i--;
}
std::cout << "Finished step 7, " << currentSpeed <<  std::endl;

driving.stop();
}



// these methods create a new instance of a pid that will run until the task is done.
void pidDriveFwd (double target) {
double error = 0;

double totalError = 0;
double prevError = 0;

double kP = 0.05;
double kI = 0.05;
double kD = 0.42;

double value;
double leftavg = leftDriveAvg();
double rightavg = rightDriveAvg();

while (error > 0) {

if (leftavg < 0) {
  leftavg *=-1;
}
if (rightavg < 0) {
  rightavg *=-1;
}
value = (leftavg + rightavg) / 2;

error = value - target;
totalError += error;
int derivative = error - prevError;

int motorPower = (error * kP + totalError * kI + derivative * kD); //Add values up
driving.setVelocity(motorPower, pct); //Apply values to motor
  } // end of loop
}
void pidDriveReverse () {

}
void pidTurnLeft () {

}
void pidTurnRight () {

}



float gyroError(float targetAngle) {
float error;
float currentAngle;

currentAngle = Gyro.heading();

// now we are in 180 to -180
if (targetAngle > 180) {
  targetAngle = 360 - targetAngle;
}
if (currentAngle > 180) {
  currentAngle = 360 - currentAngle;
}


if (targetAngle < 0 && currentAngle < 0) {
  error = fabs(targetAngle - currentAngle);
}
else if (targetAngle > 0 && currentAngle > 0) {
  error = fabs(targetAngle - currentAngle);
}
else {
  // on opposite sides of 180
  if (fabs(targetAngle) + fabs(currentAngle) > 180) {
    error = (180 - fabs(targetAngle)) + (180 - fabs(currentAngle));
  }else {
    error = fabs(targetAngle) + fabs(currentAngle);
  }
}

return error;
}

void swerveTurn(float targetAngle, float speed, vex::turnType direction, bool backwards, float tolerance) {
    // pid       error, kp, ki, kd, starti
    PID swerveTurnpid(1, 1, .1, 2, 5);

  // turn towards right
  if(direction == right) {
    if(backwards) {
    while(Gyro.heading() < targetAngle - tolerance || Gyro.heading() > targetAngle + tolerance) {
        rightDrive.spin(reverse, swerveTurnpid.compute(gyroError(targetAngle)), pct);
      }
    } else {
      while(Gyro.heading() < targetAngle - tolerance || Gyro.heading() > targetAngle + tolerance) {
        leftDrive.spin(fwd, swerveTurnpid.compute(gyroError(targetAngle)), pct);
      }
    }
    // turn towards left
  } else {
    if (backwards) {
    while(Gyro.heading() < targetAngle - tolerance || Gyro.heading() > targetAngle + tolerance) {
        leftDrive.spin(reverse, swerveTurnpid.compute(gyroError(targetAngle)), pct);
      }
    } else {
      while(Gyro.heading() < targetAngle - tolerance || Gyro.heading() > targetAngle + tolerance) {
        rightDrive.spin(fwd, swerveTurnpid.compute(gyroError(targetAngle)), pct);
      }
    }
    rightDrive.setVelocity(0, pct);
    leftDrive.setVelocity(0, pct);
  }
}
void bradLeftAuton() {
  /*
  intake on
  drive forwards
  drive reverse
  swerve turn right
  roller
  bring intake up
  drive forwards
  shoot
  wait for cata to go down
  intake on, bring intake down
  wait for all discs in
  shoot
  back up a little
  turn right
  intake up, intake on
  drive forwards
  intake down
  turn left
  shoot
  done
  */
}

void autono( void ) {

// establish variables
    bool Blue = buttons[0].state;
    bool left = buttons[1].state;
    bool skill = buttons[2].state;
    bool rickroll = buttons[3].state;
    bool None = buttons[4].state;
    bool Home = buttons[5].state;

if (rickroll) {
trolls();
}

if (!None) {

if (Blue) {
 colorChoice = false;
} else {
 colorChoice = true;

}



  if (!skill) { // skills opening

    if (!Home) {


    if (left) {
      leftAuton(Blue);
    } else {
      rightAuton(Blue);
    }



  } else { // home else
    HomeWinPoint(Blue);
  }


  }else if (skill) { // skills closing
    skills();
  } // else if skills closing



  
 } else { // end of none button
   if (Blue) {
 colorChoice = false;
  } else {
 colorChoice = true;
  } 
 }

}// end of method