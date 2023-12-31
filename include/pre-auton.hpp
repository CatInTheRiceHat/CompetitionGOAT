#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

// ........................................................................
// Auton Selector
// ........................................................................

void describe(int number) {
  asian.Screen.setCursor(4, 1);

  if (number == 1) {asian.Screen.print("OZ 100% 3 Triball");}
  else if (number == 2) {asian.Screen.print("OZ 70% 4 Triball");}
  else if (number == 3) {asian.Screen.print("DZ 100% 3 Triball");}
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
  wait(3,sec);
  asian.Screen.clearScreen();
}

// ........................................................................
// Inertial
// ........................................................................

void Inertial(){
    inert.calibrate();

    if (inert.isCalibrating()){
        asian.Screen.clearScreen();
        asian.Screen.setCursor(1, 1);
        asian.rumble(rumbleShort);
        wait(500,msec);
        asian.Screen.print("Inertial is Calibrating!");
        wait(3,sec);
        asian.rumble(rumbleLong);
        wait(500,msec);
        asian.Screen.print("Done!");
        wait(500,msec);
        asian.Screen.clearScreen();
    }
}   

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