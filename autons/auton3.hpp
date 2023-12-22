#include "vex.h"

void auton3() {
  AutonDriveSpeed(80);

  RobotDriveFwd(1); //Drive behind the double white line
  wait(250,msec);

  RobotLeftTurn(1); //Turn 90 deg counterclockwise
  wait(250,msec);

  AutonDriveSpeed(100);

  intake.spin(reverse, 100, pct); //Score and push
  RobotDriveFwd(1);
  wait(100,msec);

  RobotDriveRev(1); //Drive back to any reasonable point
  intake.stop();

  AutonDriveSpeed(80);

  RobotRightTurn(1); //Turn 135 deg clockwise
  wait(250,msec);

  intake.spin(fwd, 100, pct); //Intake triball and DON'T CROSS THE DOUBLE WHITE LINE
  RobotDriveFwd(1);
  wait(250,msec);

  RobotDriveRev(1); //Go back same distance, stay on double line
  wait(250,msec);

  RobotLeftTurn(1); //Turn 135 deg counterclockwise
  wait(250,msec);

  AutonDriveSpeed(100);

  intake.spin(reverse, 100, pct); //Score triball
  RobotDriveFwd(1);
  wait(100,msec);

  RobotDriveRev(1); //Drive back and prepare for driver practice
}