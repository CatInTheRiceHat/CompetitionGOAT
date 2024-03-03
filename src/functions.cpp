#include "vex.h"

using namespace vex;

// ........................................................................
// Auton Selector
// ........................................................................

void describe(int number) {
  asian.Screen.setCursor(4, 1);

  if (number == 1) {asian.Screen.print("Elims OZ 6 Tri Goal Rush");}
  else if (number == 2) {asian.Screen.print("Elims DZ 4 Tri");}
  else if (number == 3) {asian.Screen.print("Quals DZ AWP + 3 Tri");}
  else if (number == 4) {asian.Screen.print("Auton Skills 190+");}
}

int autons = 3;
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

void Inertial() {
  inert.calibrate();

  if (inert.isCalibrating()) {
    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);
    asian.rumble(rumbleShort);
    wait(500,msec);

    asian.Screen.print("Inertial is Calibrating!");
    wait(3,sec);
    
    asian.rumble(rumbleLong);
    wait(500,msec);

    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);
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
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(reverse, 5 + error, pct);
    R.spin(fwd, 5 + error, pct);
    wait(20, msec);
  }

  L.stop(brake);
  R.stop(brake);
}

void RobotRightTurn(double Turn) {
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(fwd, 5 + error,pct);
    R.spin(reverse, 5 + error,pct);
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

int pid(double target) {
  double kP = 0.0015;
  double kI = 0.005;
  double kD = 0.01;
  double error = target;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;

  double power = 0;
  double prevPower = 0;

  L.setPosition(0,deg);
  R.setPosition(0,deg);

  while (1) {
    double currentDist = (L.position(deg) + R.position(deg))/2;

    error = target - currentDist;
    if(fabs(integral) < 200) {
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

    if (error > -5 && error < 5 && error - prevError > -3 && error - prevError < 3) break;

    prevPower = power;
    prevError = error;

    wait(20,msec);
  }
  fl.stop();
  fr.stop();
  ml.stop();
  mr.stop();
  bl.stop();
  br.stop();
  return 0;
}