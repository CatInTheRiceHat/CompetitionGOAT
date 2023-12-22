#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

// ........................................................................
// Robot PID
// ........................................................................

//Settings
double DesiredValue;
double DesiredTurnValue;

// Lateral Settings
double kP = 0.07;
double kI = 0;
double kD = 0;

//Turn Settings
double turnkP = 0.07;
double turnkI = 0;
double turnkD = 0;

//Lateral Autonomous Settings
double error = DesiredValue;
double lasterror = error;
double integral = 0;

//Turn Autonomous Settings
double turnerror = DesiredTurnValue;
double turnlasterror = turnerror;
double turnintegral = 0;

// Enabled to use PID only for Auton
bool enabledrivePID = false;

int drivePID(double DesiredValue, double DesiredTurnValue) {
  while (enabledrivePID) {
        if (abs(error) < 30 && integral < 300) {integral += error;}
        if (abs(turnerror) < 30 && turnintegral < 300) {turnintegral += error;}

        // ........................................................................
        // Lateral Movement PID
        // ........................................................................

        double AverageDrive = (fl.position(degrees) + fr.position(degrees))/ 2;
        error = DesiredValue - AverageDrive;
        double derivative = error - lasterror;
        double driveDistance =  (error * kP + integral * kI + derivative * kD);

        // ........................................................................
        // Turning Movement PID
        // ........................................................................

        double AverageTurn = (fl.position(degrees) - fr.position(degrees))/2;
        turnerror = DesiredTurnValue - AverageTurn;
        double turnderivative = turnerror -  turnlasterror;
        double turnDistance =  (turnerror * turnkP + turnintegral * turnkI + turnderivative * turnkD);

        fl.spinFor(fwd, driveDistance + turnDistance, deg);
        ml.spinFor(fwd, driveDistance + turnDistance, deg);
        bl.spinFor(fwd, driveDistance + turnDistance, deg);

        fr.spinFor(fwd, driveDistance - turnDistance, deg);
        mr.spinFor(fwd, driveDistance - turnDistance, deg);
        br.spinFor(fwd, driveDistance - turnDistance, deg);

        if (error < 15 || turnerror < 15) {
            fl.stop();
            ml.stop();
            bl.stop();
            fr.stop();
            mr.stop();
            br.stop();
        }
        lasterror = error;
        turnlasterror = turnerror;
        wait(10, msec);
    }
}
