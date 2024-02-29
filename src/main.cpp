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
  L.setPosition(0,deg);
  R.setPosition(0,deg);

  pid(1000);

  if (display == 1) {auton1();}
  if (display == 2) {auton2();}
  if (display == 3) {auton3();}
  if (display == 4) {auton4();}

  asian.Screen.setCursor(1, 1);
  asian.Screen.print("Done");
}

// ........................................................................
// Driver Phase Code
// ........................................................................

bool CatapultDown = false;
bool WingsTog = false;

// ........................................................................
// Temperature Check
// ........................................................................

void TemperatureCheck(){

  bool flhot = false;
  bool mlhot = false;
  bool blhot = false;
  bool frhot = false;
  bool mrhot = false;
  bool brhot = false;

  if (fl.temperature(fahrenheit) >= 120) {flhot = true;}
  if (ml.temperature(fahrenheit) >= 120) {mlhot = true;}
  if (bl.temperature(fahrenheit) >= 120) {blhot = true;}

  if (fr.temperature(fahrenheit) >= 120) {frhot = true;}
  if (mr.temperature(fahrenheit) >= 120) {mrhot = true;}
  if (br.temperature(fahrenheit) >= 120) {brhot = true;}

  if (flhot || mlhot || blhot || frhot || mrhot || brhot) {
    asian.Screen.setCursor(4,4);
    std::string HotSequence = "Motor ";

    if (flhot){HotSequence += "Fl is HOT!";}
    if (mlhot){HotSequence += "Ml is HOT!";}
    if (blhot){HotSequence += "Bl is HOT!";}

    if (frhot){HotSequence += "Fr is HOT!";}
    if (mrhot){HotSequence += "Mr is HOT!";}
    if (brhot){HotSequence += "Br is HOT!";}

    asian.Screen.print(HotSequence.c_str());
    asian.rumble(rumbleLong);
  }
}

void usercontrol(void) {

  // Set all motors back to 100 pct.
    fl.setVelocity(100, percent);
    ml.setVelocity(100, percent);
    bl.setVelocity(100, percent);

    fr.setVelocity(100, percent);
    mr.setVelocity(100, percent);
    br.setVelocity(100, percent);

  asian.Screen.clearScreen();

  while (1) {
    
    // Drivetrain
    double arcadeleftValue = asian.Axis3.position();
    double arcaderightValue = asian.Axis1.position();

    double arcadeleftPower = (0.6*(arcadeleftValue + arcaderightValue));
    double arcaderightPower = (0.6*(arcadeleftValue - arcaderightValue));

    fl.spin(fwd, arcadeleftPower, percent);
    ml.spin(fwd, arcadeleftPower, percent);
    bl.spin(fwd, arcadeleftPower, percent);

    fr.spin(fwd, arcaderightPower, percent);
    mr.spin(fwd, arcaderightPower, percent);
    br.spin(fwd, arcaderightPower, percent);

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
    if (asian.ButtonR2.pressing()){
      catapult.spinToPosition(340, deg);
      wait(10, msec);
    }
    else {
      catapult.stop(hold);
      wait(10, msec);
    }

    // Intake
    if (asian.ButtonR1.pressing()==true){
      intake.spin(fwd, 100, pct);
    }
    else if (asian.ButtonR2.pressing()==true){
      intake.spin(reverse, 100, pct);
    }
    else {
    intake.stop(coast);
    }

    // Wings
    if (asian.ButtonB.pressing()){
      if (!WingsTog) {
        wings.set(1);
        wait(10, msec);
        WingsTog = true;
      }
      else if (WingsTog) {
        wings.set(0);
        wait(10, msec);
        WingsTog = false;
      }
    }

    // Blocker
    if (asian.ButtonX.pressing()) {
      blocker.set(1);
      wait(10, msec);
    }
    else {
      blocker.set(0);
      wait(10, msec);
    }

    // TemperatureCheck
    TemperatureCheck();
    wait(20, msec);      
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