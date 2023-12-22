#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

// ........................................................................
// Robot Autonomous Programs
// ........................................................................

void RobotDriveFwd(double Drive) {
  fl.spinFor(fwd, Drive, deg, false);
  ml.spinFor(fwd, Drive, deg, false);
  bl.spinFor(fwd, Drive, deg, false);
  
  fr.spinFor(fwd, Drive, deg, false);
  mr.spinFor(fwd, Drive, deg, false);
  br.spinFor(fwd, Drive, deg, true);
}

void RobotDriveRev(double Drive) {
  fl.spinFor(reverse, Drive, deg, false);
  ml.spinFor(reverse, Drive, deg, false);
  bl.spinFor(reverse, Drive, deg, false);
  
  fr.spinFor(reverse, Drive, deg, false);
  mr.spinFor(reverse, Drive, deg, false);
  br.spinFor(reverse, Drive, deg, true);
}

void RobotLeftTurn(double Turn) {
  fl.spinFor(reverse, Turn, deg, false);
  ml.spinFor(reverse, Turn, deg, false);
  bl.spinFor(reverse, Turn, deg, false);
  
  fr.spinFor(fwd, Turn, deg, false);
  mr.spinFor(fwd, Turn, deg, false);
  br.spinFor(fwd, Turn, deg, true);
}

void RobotRightTurn(double Turn) {
  fl.spinFor(fwd, Turn, deg, false);
  ml.spinFor(fwd, Turn, deg, false);
  bl.spinFor(fwd, Turn, deg, false);
  
  fr.spinFor(reverse, Turn, deg, false);
  mr.spinFor(reverse, Turn, deg, false);
  br.spinFor(reverse, Turn, deg, true);
}

void AutonDriveSpeed(double Speed){
  fl.setVelocity(Speed, pct);
  ml.setVelocity(Speed, pct);
  bl.setVelocity(Speed, pct);
  
  fr.setVelocity(Speed, pct);
  mr.setVelocity(Speed, pct);
  br.setVelocity(Speed, pct);
}

// ........................................................................
// Auton Selector
// ........................................................................

void describe(int number) {
  asian.Screen.setCursor(4, 1);

  if (number == 1) {asian.Screen.print("OZ 100% 2 Triball");}
  else if (number == 2) {asian.Screen.print("OZ 70% 3 Triball");}
  else if (number == 3) {asian.Screen.print("DZ 100% 2 Triball (WIP)");}
  else if (number == 4) {asian.Screen.print("AWP");}
  else if (number == 5) {asian.Screen.print("Auton Skills");}
}

int autons = 5;
int display = 0;

void AutonSelector() {
  asian.Screen.clearScreen();
  wait(100,msec);

  while(1){
    if (asian.ButtonRight.pressing()) {
      display++;
      wait(100, msec);
    }
    if (asian.ButtonLeft.pressing()) {
      display--;
      wait(100, msec);
    }
    if (asian.ButtonA.pressing()) {
      wait(1000, msec);
      if (asian.ButtonA.pressing()) {
      asian.rumble(rumbleLong);
      asian.Screen.clearScreen();
      break;
      }
    } 

    if (display > autons) {display = 0;}
    if (display < 0) {display = autons;}

    if (display == 0) {
      asian.Screen.clearScreen();
      asian.Screen.setCursor(1, 1);
      asian.Screen.print("Choose Your Program");
    }        
    if (display != 0) {
      asian.Screen.clearScreen();
      asian.Screen.setCursor(1, 1);
      asian.Screen.print("Selected:");
      asian.Screen.setCursor(4, 1);
      describe(display);
    }
  }
  asian.Screen.clearScreen();
  asian.Screen.setCursor(1, 1);
  asian.Screen.print("Good Luck! :)");
  wait(2000,msec);
  asian.Screen.clearScreen();
}

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

    double arcadeleftPower = (0.8*(arcadeleftValue + arcaderightValue));
    double arcaderightPower = (0.8*(arcadeleftValue - arcaderightValue));

    L.spin(fwd, arcadeleftPower, percent);
    R.spin(fwd, arcadeleftPower, percent);

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
