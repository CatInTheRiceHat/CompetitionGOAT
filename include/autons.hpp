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

void auton2() {
  AutonDriveSpeed(50);
  RobotDriveFwd(2500); //Drive to the middle of the double white line
  wait(250,msec);
  RobotRightTurn(525); //Turn 90 deg clockwis
  wait(250,msec);
  AutonDriveSpeed(100);
  intake.spin(reverse, 100, pct); //Score and push [CHECKPOINT 1]
  wait(100,msec);
  RobotDriveFwd(200);
  wait(100,msec);
  RobotDriveRev(850); //Drive back to middle of the two tiles, ok to knock off the other triball
  intake.stop();
  AutonDriveSpeed(40);
  RobotRightTurn(865); //Turn 135 deg clockwise
  wait(250,msec);
  AutonDriveSpeed(30);
  intake.spin(fwd, 100, pct); //Intake triball and don't touch the bar
  RobotDriveFwd(695);
  wait(350,msec);
  AutonDriveSpeed(25); //slow down to make it more accurate
  RobotDriveRev(350); //Go back same distance, stay on double line
  wait(250,msec);
  intake.stop();
  AutonDriveSpeed(25); //slow down the speed of turning back
  RobotLeftTurn(850); //Turn 135 deg counterclockwise
  wait(250,msec);
  AutonDriveSpeed(100);
  intake.spin(reverse, 100, pct); //Score triball
  wait(250,msec);
  RobotDriveFwd(1300);
  wait(100,msec);
  AutonDriveSpeed(25);
  RobotRightTurn(10);
  RobotDriveRev(750); //Drive back
  intake.stop();
  //from here on is collecting the third triball
  RobotLeftTurn(525);
  wait(100,msec);
  intake.spin(fwd, 100, pct); //intake triball on the double white lines
  wait(250,msec);
  RobotDriveFwd(450);
  wait(100,msec);
  intake.stop();
  RobotDriveRev(300);
  wait(200,msec);
  RobotRightTurn(573);
  AutonDriveSpeed(20);
  RobotDriveFwd(100);
  wait(150,msec);
  intake.spin(reverse, 100, pct); //SCORE IT PLS
  wait(200,msec);
  AutonDriveSpeed(100);
  RobotDriveFwd(1000);
  wait(100,msec);
  intake.stop();
  RobotDriveRev(500);
}

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

void auton5() {
  AutonDriveSpeed(80);
  RobotDriveFwd(1); //Drive fwd
  wait(250,msec);
  RobotLeftTurn(1); //Rotate 45 deg counterclockwise
  wait(250,msec);
  RobotDriveRev(1); //Drive till touching matchload bar
  wait(250,msec);
  catapult.spin(reverse, 100, pct); //Matchloading
  wait(42,sec);
  catapult.stop();
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