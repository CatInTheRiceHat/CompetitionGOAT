#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"
#include "functions.hpp"
#include "autons.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial();
  AutonSelector();
  L.setStopping(coast);
  R.setStopping(coast);
}

void autonomous(void) {  
  L.setStopping(brake);
  R.setStopping(brake);
  PidOn = true;
  if (display == 1) {auton1();}
  if (display == 2) {auton2();}
  if (display == 3) {auton3();}
  if (display == 4) {auton4();}

  asian.Screen.setCursor(1, 1);
  asian.Screen.print("Done");
}

// ........................................................................
// Driver Control
// ........................................................................

bool CatapultDown = false;
bool WedgeWingsTog = false;
bool VertWingsTog = false;
bool Hang = false;

void usercontrol(void) {
  asian.Screen.clearScreen();
  L.setStopping(coast);
  R.setStopping(coast);

  while (1) {
    
    // Drivetrain
    double arcadeleftValue = asian.Axis3.position();
    double arcaderightValue = asian.Axis1.position();

    double arcadeleftPower = ((arcadeleftValue + arcaderightValue));
    double arcaderightPower = ((arcadeleftValue - arcaderightValue));

    L.spin(fwd, (0.85*arcadeleftPower), percent);
    R.spin(fwd, (0.85*arcaderightPower), percent);

    if (arcadeleftPower > arcaderightPower || arcadeleftPower < arcaderightPower) {
      arcadeleftPower = 1.17*arcadeleftPower;
      arcaderightPower = 1.17*arcaderightPower;
    }

    // Catapult
    if (asian.ButtonL1.pressing()) {
      catapult.spin(reverse, 100, pct);
      wait(10, msec);
    }
    else {
      catapult.stop(hold);
      wait(10, msec);
    }

    // Catapult Down
    if (asian.ButtonL2.pressing()) {
      catapult.spinToPosition(340, deg);
      wait(10, msec);
    }
    else {
      catapult.stop(hold);
      wait(10, msec);
    }

    // Intake
    if (asian.ButtonR1.pressing()) {
      intake.spin(fwd, 100, pct);
    }
    else if (asian.ButtonR2.pressing()) {
      intake.spin(reverse, 100, pct);
    }
    else {
    intake.stop(coast);
    }

    // Wings
    if (asian.ButtonB.pressing()) {
      if (!WedgeWingsTog) {
        wedgewings.set(1);
        wait(100, msec);
        WedgeWingsTog = true;
      }
      else if (WedgeWingsTog) {
        wedgewings.set(0);
        wait(100, msec);
        WedgeWingsTog = false;
      }
    }

    if (asian.ButtonX.pressing()) {
      if (!VertWingsTog) {
        vertwings.set(1);
        wait(100, msec);
        VertWingsTog = true;
      }
      else if (VertWingsTog) {
        vertwings.set(0);
        wait(100, msec);
        VertWingsTog = false;
      }
    }

    // Hang
    if (asian.ButtonUp.pressing()) {
      if (!Hang) {
        hang.set(1);
        wait(10, msec);
        Hang = true;
      }
    }

    if (asian.ButtonDown.pressing()) {
      if (Hang) {
        hang.set(0);
        wait(10, msec);
        Hang = false;
      }
    }

    // TemperatureCheck
    TemperatureCheck();
    wait(10, msec);    
  } 
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(10, msec);
  }
}