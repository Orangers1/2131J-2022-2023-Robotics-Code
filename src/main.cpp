/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       Josh EGgett                                               */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <iostream>
#include "driver-control.h"
#include "auton.h"

using namespace vex;

// A global instance of competition
competition Competition;



void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
    
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}




//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
    // std::cout << RightFrontMotor.temperature(fahrenheit) << " , " <<  RightMiddleMotor.temperature(fahrenheit) << ", " << RightBackMotor.temperature(fahrenheit) << std::endl;
  Competition.autonomous(autono);
  Competition.drivercontrol(driverControl);

  

  Brain.Screen.pressed( userTouchCallbackPressed );
  Brain.Screen.released( userTouchCallbackReleased );

  Brain.Screen.setFillColor( vex::color(0x404040) );
  Brain.Screen.setPenColor( vex::color(0x404040) );
  Brain.Screen.drawRectangle( 0, 0, 480, 120 );
  Brain.Screen.setFillColor( vex::color(0x808080) );
  Brain.Screen.setPenColor( vex::color(0x808080) );
  Brain.Screen.drawRectangle( 0, 120, 480, 120 );

  displayButtonControls( 0, false );

  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (1) {
       // allow other stuff to run
    // 


    Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.setFillColor( vex::color(0x303030) );

    Brain.Screen.setPenColor( vex::color(0xc11f27) );
    
    Brain.Screen.printAt( 0, 132,  "          2131J          ");
    wait(30, msec);
  }
}
