#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

using namespace vex;

// ........................................................................
// Auton Selector
// ........................................................................

void describe(int number) {
  asian.Screen.setCursor(4, 1);

  if (number == 1) {asian.Screen.print("Quals L AWP 1 Tri");}
  else if (number == 2) {asian.Screen.print("N/A");}
  else if (number == 3) {asian.Screen.print("Elims R 4 Tri");}
  else if (number == 4) {asian.Screen.print("Elims L 1 Tri + Goal Rush");}
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
      asian.rumble(rumbleShort);
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

void Inertial() {
  inert.calibrate();

  if (inert.isCalibrating()) {
    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);

    asian.Screen.print("Inertial is Calibrating!");
    wait(3,sec);
    
    wait(500,msec);
    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);
    asian.Screen.print("Done!");
    asian.rumble(rumbleShort);
    wait(500,msec);


    asian.Screen.clearScreen();
  }
}   

// ........................................................................
// Robot Autonomous Programs
// ........................................................................

void RobotDriveFwd(double Drive, double timeLimit = 500) {
  L.setPosition(0,deg);
  R.setPosition(0,deg);
  Brain.Timer.clear();
  L.spinFor(fwd, Drive, deg, false);
  R.spinFor(fwd, Drive, deg, false);
  while(fabs(Drive - (L.position(deg) + R.position(deg))/2) > 30 && Brain.Timer.time(msec) < timeLimit){
    wait(20, msec);
  }
  L.stop(coast);
  R.stop(coast);
}

void RobotDriveRev(double Drive, double timeLimit = 500) {
  L.setPosition(0,deg);
  R.setPosition(0,deg);
  Brain.Timer.clear();
  L.spinFor(reverse, Drive, deg, false);
  R.spinFor(reverse, Drive, deg, false);
  while(fabs(Drive - (L.position(deg) + R.position(deg))/2) > 30 && Brain.Timer.time(msec) < timeLimit){
    wait(20, msec);
  }
  L.stop(coast);
  R.stop(coast);
}

void RobotLeftTurn(double Turn) {
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(reverse, 1.5 + 0.4*error, pct);
    R.spin(fwd, 1.5 + 0.4*error, pct);
    wait(20, msec);
  }

  L.stop(brake);
  R.stop(brake);
}

void RobotRightTurn(double Turn) {
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(fwd, 1.5 + 0.4*error,pct);
    R.spin(reverse, 1.5 + 0.4*error,pct);
    wait(20, msec);
  }

  L.stop(brake);
  R.stop(brake);
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
// PID
// ........................................................................

bool PidOn = false;

int pid(double target) {
  double kP = 0.00085;//0.015 //0.002525
  double kI = 0.0;//0.05 //0.027
  double kD = 0.0;//0.01 //0.0174
  double error = 0;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;

  double power = 0;
  double prevPower = 0;

  L.setPosition(0,turns);
  R.setPosition(0,turns);

  while (PidOn) {
    double currentDist = (L.position(turns) + R.position(turns))/2 * 0.75 * 3.25 * M_PI;

    error = target - currentDist;
    if(fabs(integral) > 200) {
      integral += error;
    }

    derivative = error - prevError;

    power = (kP*error) + (kI*integral) + (kD*derivative);

    if (power > 1) power = 1;
    if (power < -1) power = -1;

    double slew = 0.1;

    if (power > prevPower + slew) power = prevPower + slew;
    if (power < prevPower - slew) power = prevPower - slew;

    L.spin(fwd,11*power,volt);
    R.spin(fwd,11*power,volt);

    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);
    asian.Screen.print(error);
    wait(20,msec);
    if (error > -1 && error < 1) { //30 originally
      break;
    }

    prevPower = power;
    prevError = error;

    wait(20,msec);
  }
  L.stop();
  R.stop();
  return 0;
}

// ........................................................................
// Temperature Check
// ........................................................................

void TemperatureCheck() {

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