using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller asian;
extern motor fr;
extern motor mr;
extern motor br;
extern motor fl;
extern motor ml;
extern motor bl;
extern motor_group L;
extern motor_group R;
extern motor intake;
extern motor catapult;
extern pneumatics wedgewings;
extern pneumatics vertwings;
extern pneumatics hang;
extern inertial inert;

/*
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit(void);