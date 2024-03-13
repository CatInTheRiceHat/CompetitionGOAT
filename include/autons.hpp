#include "vex.h"

void auton1() { //Quals L AWP 1 Tri
  wait(100,msec);
  vertwings.set(1); //Take triball out of the matchload zone
  wait(100,msec);
  RobotLeftTurn(40); 
  wait(100,msec);
  vertwings.set(0);

  AutonDriveSpeed(40);

  wait(100,msec);//push alliance triball towards the goal
  RobotRightTurn(35);
  wait(100,msec);

  AutonDriveSpeed(20);

  RobotDriveRev(1650,2000);

  AutonDriveSpeed(40);
  wait(100,msec);
  RobotRightTurn(41);

  wait(100,msec);

  AutonDriveSpeed(100);

  RobotDriveRev(400);
  wait(100,msec);
  RobotDriveFwd(200);
  wait(100,msec);
  RobotRightTurn(5);
  wait(100,msec);
  RobotDriveRev(400);

  AutonDriveSpeed(40);
  //vertwings.set(0);

  wait(100,msec);
  RobotDriveFwd(70);
  wait(100,msec);
  RobotRightTurn(88);
  wait(100,msec);

  RobotDriveFwd(250);

  AutonDriveSpeed(30);

  RobotDriveRev(2600,3000);

  wait(100,msec);
  vertwings.set(1);
  wait(200,msec);

  RobotLeftTurn(8);
}

void auton2() { // Elims R 2.5 Tri -> if we're doing a long drive we should change the time variable
  AutonDriveSpeed(80);

  intake.spin(fwd, 100, pct); //get the triball under the elevation bar
  wait(100,msec);
  RobotDriveFwd(80);
  wait(500,msec);
  intake.stop();  


  AutonDriveSpeed(80);//drive near the matchload bar
  RobotDriveRev(1900,1500);
  wait(100,msec);
  RobotLeftTurn(41);
  wait(100,msec);

  //take ball outta matchload zone on the way
  RobotDriveRev(850);
  AutonDriveSpeed(20);
  RobotDriveRev(530);
  AutonDriveSpeed(70);
  wait(100,msec);

  RobotLeftTurn(40);//get perpendicular to the goal
  wait(100,msec);

  AutonDriveSpeed(100);

  RobotDriveRev(600);
  wait(100,msec);
  RobotDriveFwd(400);
  wait(100,msec);

  RobotRightTurn(175); //spit out the triball
  intake.spin(reverse, 100, pct);
  wait(400,msec);
  intake.stop();
  wait(100,msec);

  RobotLeftTurn(185);
  wait(100,msec);
  RobotRightTurn(6);
  wait(10,msec);

    
  AutonDriveSpeed(100);
  RobotDriveRev(600);
  wait(100,msec);
  AutonDriveSpeed(30);

  RobotDriveFwd(230);

  AutonDriveSpeed(100);
  wait(100,msec); // get the third triball thats the safest
  RobotRightTurn(85);
  wait(100,msec);
  RobotDriveRev(300);
  wait(100,msec);
  RobotDriveFwd(200);
  wait(100,msec);

  RobotRightTurn(15);

  intake.spin(fwd, 100, pct);
  RobotDriveFwd(2280,2000);
  wait(100,msec);
  intake.stop(hold);

  AutonDriveSpeed(100);
  RobotDriveRev(100);//score third triball
  wait(100,msec);
  RobotRightTurn(120);
  wait(100,msec);
  RobotDriveFwd(500);
  wait(100,msec);
  RobotRightTurn(85);
  wait(100,msec);

  RobotDriveRev(30,200);
  intake.spin(reverse, 100, pct);
  wait(500,msec);
  intake.stop();

  RobotDriveFwd(1200);
}

void auton3() { //Elims R 4 Tri
  AutonDriveSpeed(50);
  RobotDriveFwd(2500,1000); //Drive to the middle of the double white line
  wait(150,msec);
  RobotRightTurn(79); //Turn 90 deg clockwise
  wait(150,msec);

  AutonDriveSpeed(100);

  intake.spin(reverse, 100, pct); //Score and push [CHECKPOINT 1]
  wait(500,msec);
  intake.stop();

  RobotDriveRev(200);
  wait(100,msec);

  RobotRightTurn(180);
  wait(100,msec);

  AutonDriveSpeed(100);

  RobotDriveRev(525);
  wait(100,msec);

  RobotDriveFwd(100);
  wait(100,msec);

  AutonDriveSpeed(50);
  
  RobotLeftTurn(20);
  wait(150,msec);

  AutonDriveSpeed(40);

  intake.spin(fwd, 100, pct);
  RobotDriveFwd(1300,1300);
  wait(650,msec);
  intake.stop();
  wait(300,msec);

  AutonDriveSpeed(50);

  RobotDriveRev(900,1000);
  wait(150,msec);

  AutonDriveSpeed(80);

  RobotLeftTurn(165);//155
  wait(150,msec);

  AutonDriveSpeed(100);

  intake.spin(reverse, 100, pct);
  wait(450,msec);
  /*RobotDriveFwd(810);
  wait(100,msec);*/
  intake.stop();

  wait(100,msec);
  RobotDriveRev(400);

  //AutonDriveSpeed(100);

  wait(150,msec);
  RobotLeftTurn(118);

  intake.spin(fwd, 100, pct);
  wait(250,msec);
  AutonDriveSpeed(40);
  RobotDriveFwd(525,700);
  wait(100,msec);
  intake.stop();

  /*RobotDriveRev(100);
  wait(200,msec);*/

  AutonDriveSpeed(100);

  RobotLeftTurn(52);
  wait(100,msec);
  
  vertwings.set(1);
  wait(100,msec);
  RobotDriveRev(1500,1500);
  wait(100,msec);
  RobotDriveFwd(200);
  vertwings.set(0);

}

void auton4() { //Elims L 1 Tri + Goal Rush

}

void auton5() { //Auton Skills

}