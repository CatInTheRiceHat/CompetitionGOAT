#include "vex.h"

void auton1() { //Quals L AWP 1 Tri
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
  pid(10.64); //Turn to the elv bar
  RobotLeftTurn(40);
  pid(31.91);
  RobotLeftTurn(20);
  pid(21.06);
}

void auton2() { // Elims R 5 Tri -> if we're doing a long drive we should change the time variable
  AutonDriveSpeed(70);

  intake.spin(fwd, 100, pct); //get the triball under the elevation bar
  wait(100, msec);
  RobotDriveFwd(80);
  wait(500,msec);
  intake.stop();

  AutonDriveSpeed(80);//drive near the matchload bar
  RobotDriveRev(1900);
  wait(100,msec);
  RobotLeftTurn(40);

  vertwings.set(1);//take ball outta matchload zone on the way
  RobotDriveRev(750);
  AutonDriveSpeed(40);
  RobotDriveRev(630);
  AutonDriveSpeed(70);
  vertwings.set(0);

  RobotLeftTurn(40);//get perpendicular to the goal
  wait(100,msec);

  /*RobotDriveRev(600);
  wait(100,msec);
  RobotDriveFwd(100);
  wait(500,msec);*/

  RobotRightTurn(175); //spit out the triball
  intake.spin(reverse, 100, pct);
  wait(100,msec);
  intake.stop();

  RobotLeftTurn(173);

  wait(500,msec);
  
  AutonDriveSpeed(100);
  RobotDriveRev(600);
  AutonDriveSpeed(30);

  RobotDriveFwd(400);

  AutonDriveSpeed(60);
  wait(100,msec); // get the third triball thats the safest
  RobotRightTurn(95);
  
  intake.spin(fwd, 100, pct);
  RobotDriveFwd(2280,1500);
  wait(100,msec);
  intake.stop(hold);

  AutonDriveSpeed(100);
  RobotDriveRev(100);//score third triball
  wait(100,msec);
  RobotRightTurn(104);
  wait(100,msec);
  RobotDriveFwd(600);
  wait(100,msec);
  RobotRightTurn(42);
  wait(100,msec);

  intake.spin(reverse, 100, pct);
  wait(500,msec);
  intake.stop();

  wait(100,msec);
  RobotRightTurn(172);
  wait(100,msec);
  RobotDriveRev(800);


  //pid(64.5);
  wait(500,msec);
  intake.stop();
}

void auton3() { //Elims
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