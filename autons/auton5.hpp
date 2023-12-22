#include "vex.h"

void auton5() {
  AutonDriveSpeed(80);

  RobotDriveFwd(1); //Drive fwd
  wait(250,msec);

  RobotLeftTurn(1); //Rotate 45 deg counterclockwise
  wait(250,msec);

  RobotDriveRev(1); //Drive till touching matchload bar
  wait(250,msec);

  kicker.spin(reverse, 100, pct); //Matchloading
  wait(42,sec);
  kicker.stop();

  RobotDriveFwd(1); //Drive fwd
  wait(250,msec);

  RobotLeftTurn(1); //Rotate 45 deg counterclockwise
  wait(250,msec);

  AutonDriveSpeed(100);

  wings.set(1); //Pushing
  RobotDriveFwd(1); 
  wait(250,msec);

  RobotDriveRev(1); //Drive back
  wait(250,msec); 

  RobotRightTurn(1); //Rotate 90 deg clockwise
  wait(250,msec);

  RobotDriveFwd(1); //Drive fwd
  wait(250,msec);

  RobotLeftTurn(1); //Rotate 90 deg counterclockwise
  wait(250,msec);

  wings.set(1); //Pushing
  RobotDriveFwd(1); 
  wait(250,msec);

  RobotDriveRev(1); //Drive back
  wait(250,msec); 

  RobotRightTurn(1); //Rotate 90 deg clockwise
  wait(250,msec);

  RobotDriveFwd(1); //Drive fwd
  wait(250,msec);

  RobotLeftTurn(1); //Rotate 90 deg counterclockwise
  wait(250,msec);

  wings.set(1); //Pushing
  RobotDriveFwd(1); 
  wait(250,msec);

  RobotDriveRev(1); //Drive back
  wait(250,msec); 
}