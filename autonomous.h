#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

// Used to select the autonomoun route that should be run
int auton_route = 0;

// Used to keep track of where in the run the program is at
int auton_stage = 0;

const double auton_chassis_straight_P     = 0.01;
const double auton_chassis_straight_I     = 0.01;
const double auton_chassis_straight_I_max = 0000;
const double auton_chassis_straight_D     = 0.01;
const double auton_chassis_straight_P2    = 0.01;

const double auton_chassis_turn_P     = 0.01;
const double auton_chassis_turn_I     = 0.01;
const double auton_chassis_turn_I_max = 0000;
const double auton_chassis_turn_D     = 0.01;

double auton_chassis_straight_T   = 0;
double auton_chassis_straight_E   = 0;
double auton_chassis_straight_EP  = 0;
double auton_chassis_straight_EI  = 0;
double auton_chassis_straight_ED  = 0;
double auton_chassis_straight_EP2 = 0;

double auton_chassis_turn_T  = 0;
double auton_chassis_turn_E  = 0;
double auton_chassis_turn_EP = 0;
double auton_chassis_turn_EI = 0;
double auton_chassis_turn_ED = 0;

void auton_chassis_straight(int target);

void auton_chassis_turn(int target_degrees);

void auton_loop();

#endif