#ifndef CONTROLLER_H
#define CONTROLLER_H
// Controller Variables and Functions - JShoes
// Its a bit of a self contained piece of code I import into my VCS programming projects.
// It takes care of all the controller intricacies I've ever needed with a few simple functions.
// Keeps code looking fresh and neat.

// the prev_ value of a joystick and be used to determine the velocity of the joystick
// this may be useful in some advanced control optimization or applications
float prev_Axis1_value = 0;

// current_ is a simple read of the sensor value
float current_Axis1_value = 0;

// _update assigns new values to the prev_ and current_ variables
// it should be run before the values are neccessary, at the beginning of each loop
void Controller1_Axis1_update();

float prev_Axis2_value = 0;
float current_Axis2_value = 0;
void Controller1_Axis2_update();

float prev_Axis3_value = 0;
float current_Axis3_value = 0;
void Controller1_Axis3_update();
float prev_Axis4_value = 0;
float current_Axis4_value = 0;
void Controller1_Axis4_update();

int prev_ButtonUp_pressing = 0;
int current_ButtonUp_pressing = 0;
void Controller1_ButtonUp_update();

int prev_ButtonDown_pressing = 0;
int current_ButtonDown_pressing = 0;
void Controller1_ButtonDown_update();

int prev_ButtonLeft_pressing = 0;
int current_ButtonLeft_pressing = 0;
void Controller1_ButtonLeft_update();

int prev_ButtonRight_pressing = 0;
int current_ButtonRight_pressing = 0;
void Controller1_ButtonRight_update();

int prev_ButtonA_pressing = 0;
int current_ButtonA_pressing = 0;
void Controller1_ButtonA_update();

int prev_ButtonB_pressing = 0;
int current_ButtonB_pressing = 0;
void Controller1_ButtonB_update();

int prev_ButtonX_pressing = 0;
int current_ButtonX_pressing = 0;
void Controller1_ButtonX_update();

int prev_ButtonY_pressing = 0;
int current_ButtonY_pressing = 0;
void Controller1_ButtonY_update();

int prev_ButtonL1_pressing = 0;
int current_ButtonL1_pressing = 0;
void Controller1_ButtonL1_update();

int prev_ButtonL2_pressing = 0;
int current_ButtonL2_pressing = 0;
void Controller1_ButtonL2_update();

int prev_ButtonR1_pressing = 0;
int current_ButtonR1_pressing = 0;
void Controller1_ButtonR1_update();

int prev_ButtonR2_pressing = 0;
int current_ButtonR2_pressing = 0;
void Controller1_ButtonR2_update();

// a grouping function to make calling all the joystick _update functions simpler
void Controller1_Joysticks_update();

// more grouping functions
void Controller1_DirectionButtons_update();

void Controller1_LetterButtons_update();

void Controller1_LTButtons_update();

void Controller1_RTButtons_update();

void Controller1_TriggerButtons_update();

void Controller1_Buttons_update();

void Controller1_update();

#endif