#include "math_functions.h"
#include "motor_control.h"
#include "sensors.h"
#include "odometry.h"

// Used to select the autonomoun route that should be run
int auton_route = 1;

// Used to keep track of where in the run the program is at
int auton_stage = 0;

const double auton_chassis_straight_P         =  8.00;
const double auton_chassis_straight_I         =  0.00;
const double auton_chassis_straight_I_boundry =     6;
const double auton_chassis_straight_D         =  0.00;
const double auton_chassis_straight_P2        =  0.00;

const double auton_chassis_turn_P         =  0.00;
const double auton_chassis_turn_I         =  0.00;
const double auton_chassis_turn_I_boundry =     6;
const double auton_chassis_turn_D         =  0.00;

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

void auton_chassis_straight(int target)
{
    // this part of the code has to be after a sensor update because it requires those values
    int average_distance = (current_LeftEncoder_rad*LEFT_TRACKING_WHEEL_CONVERSION +
                            current_RightEncoder_rad*RIGHT_TRACKING_WHEEL_CONVERSION) / 2;
    
    auton_chassis_straight_EP = auton_chassis_straight_E;
    auton_chassis_straight_E = auton_chassis_straight_T - average_distance;
    auton_chassis_straight_ED = auton_chassis_straight_E - auton_chassis_straight_EP;

    if (shoesMath_abs(auton_chassis_straight_E) > auton_chassis_straight_I_boundry)
    {
        auton_chassis_straight_EI = 0;
    }
    else
    {
        auton_chassis_straight_EI += auton_chassis_straight_E;
    }

    int base_power = auton_chassis_straight_E * auton_chassis_straight_P +
                     auton_chassis_straight_EI * auton_chassis_straight_I -
                     auton_chassis_straight_ED * auton_chassis_straight_D;

    auton_chassis_straight_EP2 = current_RightEncoder_rad * RIGHT_TRACKING_WHEEL_CONVERSION -
                                 current_LeftEncoder_rad * LEFT_TRACKING_WHEEL_CONVERSION;

    LeftMotors_setPower(int(shoesMath_abs_max(base_power + auton_chassis_straight_EP2 * auton_chassis_straight_P2, 100.0)));
    RightMotors_setPower(int(shoesMath_abs_max(base_power - auton_chassis_straight_EP2 * auton_chassis_straight_P2, 100.0)));
}
int auton_chassis_straight_done(int MOE)
{
    if (shoesMath_abs(auton_chassis_straight_E) < MOE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void auton_chassis_turn(int target_degrees)
{
    auton_chassis_turn_EP = auton_chassis_turn_E;
    auton_chassis_turn_E = auton_chassis_turn_T - shoesMath_deg(current_Gyro1_rad);
    auton_chassis_turn_ED = auton_chassis_turn_E - auton_chassis_turn_EP;

    if (shoesMath_abs(auton_chassis_turn_E) > auton_chassis_turn_I_boundry)
    {
        auton_chassis_turn_EI = 0;
    }
    else
    {
        auton_chassis_turn_EI += auton_chassis_turn_E;
    }

    int base_power = auton_chassis_turn_E*auton_chassis_straight_P +
                     auton_chassis_turn_EI*auton_chassis_straight_I -
                     auton_chassis_turn_ED*auton_chassis_straight_D;

    LeftMotors_setPower(base_power);
    RightMotors_setPower(base_power*-1);
}

void auton_loop()
{
    allSensors_update();

    switch (auton_route)
    {
        case 0 :
            switch (auton_stage)
            {
                case 0 :
                    auton_chassis_straight(24);

					if (auton_chassis_straight_done(1) == 1)
					{
						auton_stage++;
					}
                case 1 :
					if (true)
					{
						auton_stage++;
					}
                case 2 :
					if (true)
					{
						auton_stage++;
					}
                case 3 :
					if (true)
					{
						auton_stage++;
					}
                case 4 :
					if (true)
					{
						auton_stage++;
					}
            }
        case 1 :
            switch (auton_stage)
            {
                case 0 :
                    Brain.Screen.clearScreen();
                    Brain.Screen.setCursor(1,1);
                    Brain.Screen.print("%f", current_LeftEncoder_rad);
                    if (false)
					{
						auton_stage++;
					}
                case 1 :
                    if (true)
					{
						auton_stage++;
					}
                case 2 :
                    if (true)
					{
						auton_stage++;
					}
                case 3 :
                    if (true)
					{
						auton_stage++;
					}
                case 4 :
                    if (true)
					{
						auton_stage++;
					}
            }
        case 2 :
            switch (auton_stage)
            {
                case 0 :
                    if (true)
					{
						auton_stage++;
					}
                case 1 :
                    if (true)
					{
						auton_stage++;
					}
                case 2 :
                    if (true)
					{
						auton_stage++;
					}
                case 3 :
                    if (true)
					{
						auton_stage++;
					}
                case 4 :
                    if (true)
					{
						auton_stage++;
					}
            }
    }

    Motors_updateAll();
}