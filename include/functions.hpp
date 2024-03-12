#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

extern int autons;
extern int display;
extern bool PidOn;

void describe(int number);
void AutonSelector();
void Inertial();
void RobotDriveFwd(double Drive, double timeLimit = 500);
void RobotDriveRev(double Drive, double timeLimit = 500);
void RobotLeftTurn(double Turn);
void RobotRightTurn(double Turn);
void AutonDriveSpeed(double Speed);
int pid(double target);
void TemperatureCheck();

#endif // FUNCTIONS_HPP