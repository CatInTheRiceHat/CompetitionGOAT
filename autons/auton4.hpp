#include <iostream>
#include "stdarg.h"
#include <cstring>
#include <string.h>
#include "vex.h"

void auton4() { //Works 70% of the time
  AutonDriveSpeed(50);

  RobotDriveFwd(1200); //Drive behind the double white line
  wait(250,msec);

  AutonDriveSpeed(80);

  RobotRightTurn(250); //Turn to be perpendicular to the side of the goal
  wait(250,msec);

  AutonDriveSpeed(35);

  intake.spin(fwd, 100, pct); //Score and push
  wait(300,msec);
  RobotDriveFwd(800);
  wait(100,msec);
  intake.stop();

  AutonDriveSpeed(25);

  RobotDriveRev(970); //Drive back to center of goal tile
  wait(300,msec);

  RobotLeftTurn(180); //Turn 90 deg counterclockwise
  wait(250,msec);
  wings.set(1);
  wait(250,msec);

  AutonDriveSpeed(100);

  RobotDriveRev(920); //drive back to pull the triball out of the matchload zone
  wait(250,msec);

  RobotLeftTurn(190); //turn and try to pull the triball out of the matchload zone again just in case
  wait(250,msec);
  RobotDriveRev(300);
  wait(500,msec);

  RobotDriveFwd(500); //minor adjustments so we can back up properly to the elevation bar
  wait(100,msec);
  wings.set(0);

  RobotLeftTurn(170); //Touch the elevation bar
  wait(500,msec);
  RobotDriveRev(3200);
}