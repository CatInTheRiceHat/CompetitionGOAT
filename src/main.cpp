#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"
#include "autons.hpp"
#include "driver.hpp"
#include "pid.hpp"
#include "pre-auton.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  AutonSelector();
}

void autonomous(void) {
  //enabledrivePID = true;

  //drivePID(1000,0);
  
  if (display == 1) {auton1();}
  if (display == 2) {auton2();}
  if (display == 3) {auton3();}
  if (display == 4) {auton4();}
  if (display == 5) {auton5();}
  asian.Screen.print("Done");
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}