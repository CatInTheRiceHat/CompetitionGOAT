#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"
#include "pre-auton.hpp"
#include "pid.hpp"
#include "autons.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial();
  AutonSelector();
}

/*
Set all gains to zero.

Increase kP until the response to a step input (like a sudden change in target distance) is steady oscillation. Steady oscillation means the robot moves back and forth around the target distance without settling down.

Set kP to about half of the value causing steady oscillation.

Increase kD until any overshoot is acceptable. Overshoot is when the robot moves past the target distance before coming back. Increasing kD will reduce the overshoot, but making kD too large can lead to a sluggish response.

Increase kI until the robot reaches the target distance in a reasonable time during steady state. Steady state is when the robot is not being subjected to any disturbances or changes in the target distance. Be careful with increasing kI, as too large a value can cause instability.
*/

//PID constants
double kP = 10; //kP is the constant for proportional control
double kI = 0; //kI is the constant for integral control
double kD = 0; //kD is the constant for derivative control

//PID variables
double integral = 0; //integral is the sum of all errors 
double derivative = 0; //derivative is the difference between the current error and the last error
double error = 0; //error is the difference between the target distance and the current distance
double lastError = 0; //lastError is the error from the last time the function was called
double integralLimit = 20; //integralLimit is the maximum value of the integral

//Orientation PID constants
double kP_orient = 0.0; //kP is the constant for proportional control
double kI_orient = 0.0; //kI is the constant for integral control
double kD_orient = 0.0; //kD is the constant for derivative control

//Orientation PID variables
double integral_orient = 0; //integral is the sum of all errors
double derivative_orient = 0; //derivative is the difference between the current error and the last error
double error_orient = 0; //error is the difference between the target orientation and the current orientation
double lastError_orient = 0; //lastError is the error from the last time the function was called

// drivetrain pid with odometry
void drivetrainPID(double targetDistance, double targetOrientation, double distanceSensorValue, double orientationSensorValue) {
    // Calculate distance error
    error = targetDistance - distanceSensorValue;

    // Calculate orientation error
    error_orient = targetOrientation - orientationSensorValue;

    // Calculate distance integral with windup prevention
    if (fabs(error) < integralLimit) {
        integral += error;
    } else {
        integral = 0;
    }

    // Calculate orientation integral with windup prevention
    if (fabs(error_orient) < integralLimit) {
        integral_orient += error_orient;
    } else {
        integral_orient = 0;
    }

    // Calculate distance derivative
    derivative = error - lastError; //change in distance
    lastError = error; //update previous value

    // Calculate orientation derivative
    derivative_orient = error_orient - lastError_orient; // change in orient
    lastError_orient = error_orient; // update previous value

    // Calculate distance PID output
    double output = kP * error + kI * integral + kD * derivative;

    // Calculate orientation PID output
    double output_orient = kP_orient * error_orient + kI_orient * integral_orient + kD_orient * derivative_orient;

    // Control motors
    double leftMotorSpeed = output + output_orient; // Calculate left speed
    double rightMotorSpeed = output - output_orient; // Calculate right speed

    // Set motor speeds...
    L.spin(fwd, leftMotorSpeed, pct);
    R.spin(fwd, rightMotorSpeed, pct);
}

void travel(double distance, double angle) {
    // Get current distance sensor value
    double currentDistance = (fl.position(deg) + fr.position(deg) / 2);
    // Get current orientation sensor value
    double currentOrientation = inert.rotation(deg);

    // Move forward
    while (fabs(distance - currentDistance) > 0.1) {
        drivetrainPID(distance, currentOrientation, currentDistance, currentOrientation);
        currentDistance = (fl.position(deg) + fr.position(deg) / 2);
    }

    // Turn
    while (fabs(angle - currentOrientation) > 0.1) {
        drivetrainPID(0, angle, currentDistance, currentOrientation);
        currentOrientation = inert.rotation(deg);
    }
}

void autonomous(void) {  
  L.setPosition(0,deg);
  R.setPosition(0,deg);

  travel(100,0);
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
bool IntakeTog = false;
bool OutakeTog = false;
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

    double arcadeleftPower = (0.7*(arcadeleftValue + arcaderightValue));
    double arcaderightPower = (0.7*(arcadeleftValue - arcaderightValue));

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
    if (asian.ButtonR1.pressing()){
      if (!IntakeTog) {
        intake.spin(fwd, 80, pct);
        wait(10, msec);
        IntakeTog = true;
      }
      else if (IntakeTog) {
        intake.stop(coast);
        wait(10, msec);
        IntakeTog = false;
      }
    }

    //Outake
    if (asian.ButtonR2.pressing()){
      if (!OutakeTog) {
        intake.spin(reverse, 80, pct);
        wait(10, msec);
        OutakeTog = true;
      }
      else if (OutakeTog) {
        intake.stop(coast);
        wait(10, msec);
        OutakeTog = false;
      }
    }

    //Wings
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

    //Blocker
    if (asian.ButtonX.pressing()) {
      blocker.set(1);
      wait(10, msec);
    }
    else {
      blocker.set(0);
      wait(10, msec);
    }

    //TemperatureCheck
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