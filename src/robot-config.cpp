#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller asian = controller(primary);
motor fr = motor(PORT10, ratio6_1, false);
motor mr = motor(PORT14, ratio6_1, false);
motor br = motor(PORT18, ratio6_1, false);
motor fl = motor(PORT3, ratio6_1, true);
motor ml = motor(PORT17, ratio6_1, true);
motor bl = motor(PORT7, ratio6_1, true);
motor_group L = motor_group(ml, bl, fl);
motor_group R = motor_group(mr, br, fr);
motor intake = motor(PORT13, ratio6_1, false);
motor catapult = motor(PORT4, ratio36_1, false);
pneumatics wedgewings = pneumatics(Brain.ThreeWirePort.A);
pneumatics vertwings = pneumatics(Brain.ThreeWirePort.A);
pneumatics hang = pneumatics(Brain.ThreeWirePort.C);
inertial inert = inertial(PORT15);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}