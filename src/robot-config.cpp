#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller asian = controller(primary);
motor fr = motor(PORT2, ratio6_1, false);
motor mr = motor(PORT12, ratio6_1, false);
motor br = motor(PORT18, ratio6_1, false);
motor fl = motor(PORT3, ratio6_1, true);
motor ml = motor(PORT13, ratio6_1, true);
motor bl = motor(PORT6, ratio6_1, true);
motor_group L = motor_group(ml, bl, fl);
motor_group R = motor_group(mr, br, fr);
motor intake = motor(PORT19, ratio6_1, false);
motor catapult = motor(PORT8, ratio36_1, false);
pneumatics wings = pneumatics(Brain.ThreeWirePort.A);
pneumatics blocker = pneumatics(Brain.ThreeWirePort.B);
inertial inert = inertial(PORT20);

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