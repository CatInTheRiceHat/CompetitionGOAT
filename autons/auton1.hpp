#include "vex.h"

void auton1() {
  AutonDriveSpeed(80);

  RobotDriveFwd(2500); //Drive to the middle of the double white line
  wait(250,msec);

  RobotRightTurn(575); //Turn 90 deg clockwis
  wait(250,msec);

  AutonDriveSpeed(100); //Make Fasta

  intake.spin(reverse, 100, pct); //Outake
  wait(100,msec);

  RobotDriveRev(650); //Drive back to middle of the two tiles, ok to knock off the other triball
  intake.stop();

  AutonDriveSpeed(40);

  RobotRightTurn(900); //Turn 135 deg clockwise
  wait(250,msec);

  intake.spin(fwd, 100, pct); //Intake triball and don't touch the bar
  RobotDriveFwd(780);
  wait(250,msec);

  RobotDriveRev(650); //Go back same distance, stay on double line
  wait(250,msec);
  intake.stop();

  AutonDriveSpeed(25); //slow down the speed of turning back

  RobotLeftTurn(860); //Turn 135 deg counterclockwise
  wait(250,msec);

  AutonDriveSpeed(100);

  intake.spin(reverse, 100, pct); //Score triball
  wait(250,msec);

  RobotDriveFwd(1300); //PUSH
  wait(100,msec);

  RobotDriveRev(500); //Drive back and prepare for driver practice
  intake.stop();

  RobotDriveFwd(1000); //Push it in twice just to make sure it gets in
  wait(250,msec);

  RobotDriveRev(700); //Prepare for driver control
}