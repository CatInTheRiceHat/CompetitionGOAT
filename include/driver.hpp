#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

// ........................................................................
// Driver Phase Code
// ........................................................................

bool IntakeTog = false;
bool OutakeTog = false;
bool WingsTog = false;

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
    asian.rumble("-");
  }
}

void usercontrol(void) {

  //Set all motors back to 100 pct.
  fl.setVelocity(100,pct);
  ml.setVelocity(100,pct);
  bl.setVelocity(100,pct);

  fr.setVelocity(100,pct);
  mr.setVelocity(100,pct);
  br.setVelocity(100,pct);

  asian.Screen.clearScreen();

  while (1) {
    
    //Drivetrain
    double arcadeleftValue = asian.Axis3.position();
    double arcaderightValue = asian.Axis1.position();

    double arcadeleftPower = (0.7*(arcadeleftValue + arcaderightValue));
    double arcaderightPower = (0.7*(arcadeleftValue - arcaderightValue));

    fl.spin(fwd, arcadeleftPower, percent);
    ml.spin(fwd, arcadeleftPower, percent);
    bl.spin(fwd, arcadeleftPower, percent);
  
    fr.spin(fwd, arcaderightPower, percent);
    mr.spin(fwd, arcaderightPower, percent);
    br.spin(fwd, arcaderightPower, percent);

    //Kicker
    if (asian.ButtonL1.pressing()) {
      kicker.spin(reverse, 100, pct);
      wait(100,msec);
    }
    else {
      kicker.stop(hold);
      wait(100,msec);
    }

    //Intake
    if (asian.ButtonR1.pressing()){
      if (!IntakeTog) {
        intake.spin(fwd, 80, pct);
        wait(100,msec);
        IntakeTog = true;
      }
      else if (IntakeTog) {
        intake.stop(coast);
        wait(100,msec);
        IntakeTog = false;
      }
    }

    //Outake
    if (asian.ButtonR2.pressing()){
      if (!OutakeTog) {
        intake.spin(reverse, 80, pct);
        wait(100,msec);
        OutakeTog = true;
      }
      else if (OutakeTog) {
        intake.stop(coast);
        wait(100,msec);
        OutakeTog = false;
      }
    }

    //Wings
    if (asian.ButtonB.pressing()){
      if (!WingsTog) {
        wings.set(1);
        wait(100,msec);
        WingsTog = true;
      }
      else if (WingsTog) {
        wings.set(0);
        wait(100,msec);
        WingsTog = false;
      }
    }

    //Blocker
    if (asian.ButtonX.pressing()) {
      blocker.set(1);
      wait(100,msec);
    }
    else {
      blocker.set(0);
      wait(100,msec);
    }

    //TemperatureCheck
    TemperatureCheck();
    wait(20, msec);      
  } 
}
