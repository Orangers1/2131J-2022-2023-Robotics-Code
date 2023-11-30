    /*
    author: Josh Eggett
    */

#include "vex.h"
#include "robot-config.h"
#include <iostream>
#include "auton.h"


void driverControl()
{
    RightFrontMotor.setStopping(coast);
    RightMiddleMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    LeftMiddleMotor.setStopping(coast);
    LeftFrontMotor.setStopping(coast);

    DiscIntakeMotor.setStopping(coast);
    CatapultMotor.setStopping(hold);
    

      bool intakeSpinning = false;
      int jammed = 0;
      int outtake = 0;
      int buttonRecent = 0;
      double discIntakeVelocity = 100;
      
      bool rollerSpinning = false;
      bool rollerReversed = false;
      RollerSensor.setLight(ledState::on);
      RollerSensor.setLightPower(80, pct);
      bool launching = false;
    double rollerSpeed = 15;
    double cataDistance = CatapultSensor.objectDistance(mm);
double outputRecent = 0;
  while(1)
  {
    if (CatapultSensor.isObjectDetected()) {
cataDistance = CatapultSensor.objectDistance(mm);
    } else {
      cataDistance = 10000;
    }

// ====================================Output things =========================

   if (outputRecent <= 0) {
     if (rollerSpinning) {
    std::cout << "roller mode enabled"  << std::endl;
     
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.clearLine(0);
    Controller1.Screen.print("roller mode enabled");
    DiscIntakeMotor.setVelocity(rollerSpeed, pct);
    Controller1.rumble("-");
     } else {
       std::cout << "intake mode enabled"  << std::endl;
     
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.clearLine(0);
    Controller1.Screen.print("intake mode enabled");
     }
   // 
    outputRecent = 800;
    }
    outputRecent--;
      //  std::cout << CatapultSensor.position(deg)  << std::endl;

// ===========================================================================


// ================================CatapultControl==================================
if (!launching && cataDistance > 100) { // if its not launching and the distance is greater than 100 keep moving down. (100 mm)
  CatapultMotor.setVelocity(100, pct);
  CatapultMotor.spin(fwd);
} else if (cataDistance < 100 && !launching) { // less than 100 and not launching, stop
  CatapultMotor.stop();
} else if (launching) { // if its launching go.
  CatapultMotor.spin(fwd);
}

 if(Controller1.ButtonR1.pressing()) {
      if (!launching) {
          launching = true;
       }
    }

    if (launching) {
      if (cataDistance > 180) {
        launching = false;
      }
    }

 

//===============================================================================

  // ==============================MECHANUM===========================================
    // int RightStraight = Controller1.Axis2.position(percent);
    // int LeftStraight = Controller1.Axis3.position(percent);

    // int LeftStrafe = Controller1.Axis4.position(percent);
    // int RightStrafe = -Controller1.Axis1.position(percent);
     
    //  int RightBackMotorSpeed = RightStraight  - RightStrafe;
    //  int RightFrontMotorSpeed = RightStraight  +RightStrafe ;
    //  int LeftFrontMotorSpeed = LeftStraight + LeftStrafe ;
    //  int LeftBackMotorSpeed = LeftStraight - LeftStrafe ;

    // RightFrontMotor.spin(forward, RightFrontMotorSpeed, percent);
    // RightBackMotor.spin(forward, RightBackMotorSpeed, percent);
    // LeftFrontMotor.spin(forward, LeftFrontMotorSpeed, percent);
    // LeftBackMotor.spin(forward, LeftBackMotorSpeed, percent);
    //===================================================================================
    //-----------------------------OMNI----------------------------------
    RightFrontMotor.spin(forward, Controller1.Axis2.position(), percent);
    RightMiddleMotor.spin(forward, Controller1.Axis2.position(), percent);
    RightBackMotor.spin(forward, Controller1.Axis2.position(), percent);

    LeftFrontMotor.spin(forward, Controller1.Axis3.position(), percent);
    LeftMiddleMotor.spin(forward, Controller1.Axis3.position(), percent);
    LeftBackMotor.spin(forward, Controller1.Axis3.position(), percent);
//-----------------------------------------------------------------------

  // controls


// =========================================Roller/IntakeDirectionControlStart===================================
   if(Controller1.ButtonRight.pressing()) {
     if (rollerReversed) {
     rollerReversed = false;
     } else if (!rollerSpinning) {
      rollerSpinning = true;
      rollerReversed = false;
      } else if (rollerSpinning) {
        rollerSpinning = false;
              rollerReversed = false;
      }
      wait(300, msec);
   }
   if(Controller1.ButtonLeft.pressing()) {
      if (!rollerReversed) {
      rollerReversed = true;
            rollerSpinning = true;

      } else if (rollerReversed) {
        rollerReversed = false;
              rollerSpinning = false;

      }
      wait(300, msec);
   }
   // ===========================================roller/intake direction control end=============================
       if(Controller1.ButtonL1.pressing()) {
          if (!intakeSpinning) {
            intakeSpinning = true;
      } else if (intakeSpinning) {
            intakeSpinning = false;
      }
      wait(300, msec);
    }
      if(Controller1.ButtonL2.pressing()) {
      intakeSpinning = false;
      outtake = 200;
    }
    if (Controller1.ButtonR2.pressing()) {
      rollerSpinning = true;
    } else {
          rollerSpinning = false;
    }

    if (intakeSpinning) {
      if (rollerSpinning) {
      DiscIntakeMotor.setVelocity(rollerSpeed, pct);
      DiscIntakeMotor.spin(fwd);
      } else {
        if (outtake <= 0) {
      DiscIntakeMotor.setVelocity(discIntakeVelocity, pct);
      DiscIntakeMotor.spin(fwd);
        } else {
      DiscIntakeMotor.setVelocity(discIntakeVelocity, pct);
      DiscIntakeMotor.spin(reverse);
        }
        } 
    } else {
      if (outtake >= 0) {
      DiscIntakeMotor.setVelocity(discIntakeVelocity, pct);
      DiscIntakeMotor.spin(reverse);
        } else {
      DiscIntakeMotor.stop();
        }
    }


// Disc intake stuff below  ===============AUTO UNJAMMING STUFF=======================







  outtake--;
  jammed -= 2;
buttonRecent = buttonRecent - 1;
 // end of disc intake. ====================================== END OF AUTO UNJAM INTAKE
       std::cout << cataDistance  << std::endl;
  wait(3, msec);

}
}