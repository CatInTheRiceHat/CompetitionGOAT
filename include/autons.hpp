#include "vex.h"

void auton1() { //Quals L AWP
  vertwings.set(1); //Open Wings
  AutonDriveSpeed(80);
  wait(500,msec);
  RobotLeftTurn(67.5); //Turn to get triball out
  wait(500,msec);
  vertwings.set(0); //Close Wings
  wait(500,msec);
  RobotRightTurn(45); //Push Ali Tri
  RobotDriveRev(600);
  RobotRightTurn(35);
  RobotDriveRev(500);
  wait(100,msec);
  pid(500); //Turn to the elv bar
  RobotLeftTurn(40);
  pid(1500);
  RobotLeftTurn(20);
  pid(990);
}

void auton2() { // Elims R 6 Tri
  AutonDriveSpeed(70);
  intake.spin(fwd, 100, pct);
  wait(800,msec);
  intake.stop();
  RobotDriveRev(1900);
  wait(100,msec);
  RobotLeftTurn(45);
  vertwings.set(1);
  RobotDriveRev(900);
  vertwings.set(0);
  RobotLeftTurn(37.5);
  wait(100,msec);
  RobotDriveRev(600);
  wait(100,msec);
  RobotDriveFwd(150);
  intake.spin(fwd, 100, pct);
  RobotRightTurn(167.5);
  intake.spin(reverse, 100, pct);
  wait(500,msec);
  intake.stop();
  RobotDriveFwd(350);
  wait(100,msec);
  pid(-250);
}

void auton3() { //Quals DZ AWP
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

void auton4() { // Auton Skills 190+

}