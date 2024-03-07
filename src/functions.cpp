#include "vex.h"

using namespace vex;

// ........................................................................
// Auton Selector
// ........................................................................

void describe(int number) {
  asian.Screen.setCursor(4, 1);

  if (number == 1) {asian.Screen.print("Quals L AWP");}
  else if (number == 2) {asian.Screen.print("Elims R 6 Tri");}
  else if (number == 3) {asian.Screen.print("Elims R 5 Tri Goal Rush");}
  else if (number == 4) {asian.Screen.print("Elims L 6 Tri");}
  else if (number == 4) {asian.Screen.print("Auton Skills");}
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

void Inertial() {
  inert.calibrate();

  if (inert.isCalibrating()) {
    asian.Screen.clearScreen();
    asian.Screen.setCursor(1, 1);

    asian.Screen.print("Inertial is Calibrating!");
    wait(3,sec);
    
    asian.rumble(rumbleShort);
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
  L.spinFor(fwd, Drive, deg, false);
  R.spinFor(fwd, Drive, deg, true);
}

void RobotDriveRev(double Drive) {
  L.spinFor(reverse, Drive, deg, false);
  R.spinFor(reverse, Drive, deg, true);
}

void RobotLeftTurn(double Turn) {
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(reverse, 5 + 0.4*error, pct);
    R.spin(fwd, 5 + 0.4*error, pct);
    wait(20, msec);
  }

  L.stop(brake);
  R.stop(brake);
}

void RobotRightTurn(double Turn) {
  inert.setRotation(0,deg);

  while (fabs(inert.rotation(degrees)) < Turn) {
    double error = Turn - fabs(inert.rotation(degrees));
    L.spin(fwd, 5 + 0.4*error,pct);
    R.spin(reverse, 5 + 0.4*error,pct);
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

  L.setPosition(0,deg);
  R.setPosition(0,deg);

  while (PidOn) {
    double currentDist = (L.position(deg) + R.position(deg))/2;

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
    if (error > -50 && error < 50) { //30 originally
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