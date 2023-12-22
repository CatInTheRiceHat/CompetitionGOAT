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