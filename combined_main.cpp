#include "robot-config.h"

// Configuration sets up all the names for instances of each of the classes (motors or sensors)
vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor LeftMotor1 = vex::motor(vex::PORT13,true);
vex::motor LeftMotor2 = vex::motor(vex::PORT14,true);
vex::motor RightMotor1 = vex::motor(vex::PORT11,false);
vex::motor RightMotor2 = vex::motor(vex::PORT12,false);
vex::motor PuncherMotor = vex::motor(vex::PORT15, true);
vex::motor IntakeMotor = vex::motor(vex::PORT16,false);
vex::encoder LeftEncoder = vex::encoder(Brain.ThreeWirePort.G);
vex::encoder RightEncoder = vex::encoder(Brain.ThreeWirePort.A);
vex::gyro Gyro1 = vex::gyro(Brain.ThreeWirePort.D);
vex::gyro Gyro2 = vex::gyro(Brain.ThreeWirePort.C);
vex::limit PuncherLimit = vex::limit(Brain.ThreeWirePort.F);
vex::limit IntakeLimit = vex::limit(Brain.ThreeWirePort.E);


/*++| ROBOT CONFIGURATION *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*//*
[Smart Port]         [Name]          [Type]           [Description]       [Reversed]
Motor Port 1                         V5 Smart Motor   
Motor Port 2                         V5 Smart Motor   
Motor Port 3                         V5 Smart Motor   
Motor Port 4                         V5 Smart Motor   
Motor Port 5                         V5 Smart Motor   
Motor Port 6                         V5 Smart Motor   
Motor Port 7                         V5 Smart Motor   
Motor Port 8                         V5 Smart Motor   
Motor Port 9                         V5 Smart Motor   
Motor Port 10                        V5 Smart Motor   
Motor Port 11                        V5 Smart Motor   
Motor Port 12                        V5 Smart Motor   
Motor Port 13                        V5 Smart Motor   
Motor Port 14                        V5 Smart Motor   
Motor Port 15                        V5 Smart Motor   
Motor Port 16                        V5 Smart Motor   
Motor Port 17                        V5 Smart Motor   
Motor Port 18                        V5 Smart Motor   
Motor Port 19                        V5 Smart Motor   
Motor Port 20                        V5 Smart Motor   
-------------------------------------------------------------------------------------------------*/

/*++| DOCUMENTATION *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*//*

-------------------------------------------------------------------------------------------------*/
vex::competition    Competition;

/*++| CONSTANTS *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// default motor speeds used in user control and auton control
#define SUBSYSTEM_SPEED_PCT 100

const double MASTER_MOE =     0.0001;
const double PI         = 3.14159265;

// returns the absolute value of the input. Input can be any integer or double but it returns the value as a double.
double shoesMath_abs(double input)
{
	// multiplies the value by -1 only if it is negative so the sign is always positive.
	if (input < 0)
	{
		return -1*input;
	}
	else
	{
		return input;
	}
}

// returns the remainder of dividing the input by the divisor. It can take integer, double, negative, or positive input.
// divisor must be positive.
double shoesMath_mod(double input, double divisor)
{
	// multiplier keeps track of the sign of the original input.
	int multiplier = 1;
	if (input < 0)
	{
		multiplier = -1;
	}
	input = shoesMath_abs(input);
	// until the remainder is less than the divisor, the while loop continues to subtract the divisor from the remainder.
	while (input > divisor)
	{
		input -= divisor;
	}
	return input*multiplier;
}

// the input and maximum value both must be positive.
// if the input is greater than the max, it returns the max. otherwise it returns the input as is.
double shoesMath_max(double value, double max)
{
	if (value > max)
	{
		value = max;
	}
	return value;
}

// the input and maximum value both can be positive or negative double.
// if the input is negative and less than the maximum, it returns the negative maximum.
// if the input is positive and greater than the maximum, it returns the positive maximum.
// otherwise it returns the input as is.
double shoesMath_abs_max(double value, double abs_max)
{
	// checks to see if changing the value is even neccessary
	if (shoesMath_abs(value) > shoesMath_abs(abs_max))
	{
		// sets the value to the positive maximum.
		if (value > 0)
		{
			value = shoesMath_abs(abs_max);
		}
		// sets the value of the negative maximum.
		else
		{
			value = shoesMath_abs(abs_max)*-1;
		}
	}
	return value;
}

// converts degrees to radians. Input should be a double.
double shoesMath_rad(double deg)
{
	return deg*(PI/180);
}

// converts radians to degrees. Input should be a double.
double shoesMath_deg(double rad)
{
	return rad*(180/PI);
}

// input should be in radians. returns 0 if the input does not lie on one of the axis.
// 1 is the positive x axis, 2 is the positive y axis, 3 is the negative x axis, 4 is the negative y axis.
// the margin of error for floating point error is determined by the MASTER_MOE constant.
int axis_rad (double input)
{
	if (input > (2*PI) - MASTER_MOE || input < 0 + MASTER_MOE)
	{
		return 1;
	}
	else if (input > (PI/2) - MASTER_MOE && input < (PI/2) + MASTER_MOE)
	{
		return 2;
	}
	else if (input > PI - MASTER_MOE && input < PI + MASTER_MOE)
	{
		return 3;
	}
	else if (input > ((3*PI)/2) - MASTER_MOE && input < ((3*PI)/2) + MASTER_MOE)
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

// input should be in radians. returns 0 if the input does not lie in one of the quadrants.
// 1, 2, 3, and 4 are each of the quadrants respectively.
// the margin of error for floating point error is determined by the MASTER_MOE constant.
int quadrant_rad(double input)
{
	if (axis_rad(input) == 0) {
		if (input > 0 && input < PI/2)
		{
			return 1;
		}
		else if (input > PI/2 && input < PI)
		{
			return 2;
		}
		else if (input > PI && input < (3*PI)/2)
		{
			return 3;
		}
		else if (input > (3*PI)/2 && input < 2*PI)
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

// takes in an angle in radians and converts it to an equavilent positive angle less than 2 PI.
double simplify_rad(double input)
{
	input = shoesMath_mod(input, (2*PI));
	if (input < 0)
	{
		input += (2*PI);


	}
	return input;
}

// input must be in radians.
// returns the angle as it would be reflected across the x-axis.
double reflect_x_rad(double input)
{
	return (2*PI) - input;
}

// input must be in radians.
// returns the angle as it would be reflected across the y-axis.
double reflect_y_rad(double input)
{
	if (quadrant_rad(input) == 1 || quadrant_rad(input) == 2)
	{
		return PI - input;
	}
	else if (quadrant_rad(input) == 3 || quadrant_rad(input) == 4)
	{
		return (3*PI) - input;
	}
	else if (axis_rad(input) == 1)
	{
		return PI;
	}
	else if (axis_rad(input) == 3)
	{
		return 0;
	}
	else
	{
		return input;
	}
}

// input must in radians.
// returns sine of the input with 3 significant figures.
double shoesMath_sin_rad(double input)
{
	if (quadrant_rad(input) != 0)
	{
		int multiplier;
		if (quadrant_rad(input) == 1)
		{
			multiplier = 1;
		}
		else if (quadrant_rad(input) == 2)
		{
			multiplier = 1;
			input = reflect_y_rad(input);
		}
		else if (quadrant_rad(input) == 3)
		{
			multiplier = -1;
			input = reflect_y_rad(reflect_x_rad(input));
		}
		else if (quadrant_rad(input) == 4)
		{
			multiplier = -1;
			input = reflect_x_rad(input);
		}
		if (input < PI/4)
		{
			return (input-((input*input*input)/6)+(input*input*input*input*input/120))*multiplier;
		}
		else
		{
			input = (PI/2) - input;
			return (1-((input*input)/2)+((input*input*input*input)/24)-((input*input*input*input*input*input)/720))*multiplier;
		}
	}
	else if (axis_rad(input) == 1 || axis_rad(input) == 3)
	{
		return 0;
	}
	else if (axis_rad(input) == 2)
	{
		return 1;
	}
	else if (axis_rad(input) == 4)
	{
		return -1;
	}
	else
	{
		//when there is no valid return value.
		//This should never happen but it's a fail safe to make sure the function alawys returns something

		return 0;
	}
}

// input must in radians.
// returns cosine of the input with 3 significant figures.
double shoesMath_cosine_rad(double input)
{
	int multiplier = 0;
	if (quadrant_rad(input) != 0) {
		if (quadrant_rad(input) == 1)
		{
			input = (PI/2)-input;
			multiplier = 1;
		}
		else if (quadrant_rad(input) == 2)
		{
			input = ((3*PI)/2)-input;
			multiplier = -1;
		}
		else if (quadrant_rad(input) == 3)
		{
			input = ((5*PI)/2)-input;
			multiplier = 1;
		}
		else if (quadrant_rad(input) == 4)
		{
			input = ((7*PI)/2)-input;
			multiplier = -1;
		}

		return shoesMath_sin_rad(input) * multiplier;
	}
	else {
		if (axis_rad(input) == 1)
		{
			return 1;
		}
		else if (axis_rad(input) == 2 || axis_rad(input) == 4)
		{
			return 0;
		}
		else if (axis_rad(input) == 3)
		{
			return -1;
		}
		// when there is no valid return value.
		//This should never happen but it's a fail safe to make sure the function alawys returns something
		else
		{
			return 0;
		}
		
	}
}

// input must in radians.
// returns tangent of the input with 3 significant figures.
double shoesMath_tangent_rad(double input)
{
	return shoesMath_sin_rad(input)/shoesMath_cosine_rad(input);
}

// constants that describe the position and size of the tracking wheels - used for odometry
const double LEFT_TRACKING_WHEEL_CONVERSION  = 0.0000; // To convert radians into in
const double RIGHT_TRACKING_WHEEL_CONVERSION = 0.0000; // To convert radians into in
const double BACK_TRACKING_WHEEL_CONVERSION  = 0.0000; // To convert radians into in
const double ROBOT_WIDTH                     = 0.0000; // To convert radians into in
const double BACK_TRACKING_OFFSET            = 0.0000; // in

double shoesOdom_x = 0;
double shoesOdom_y = 0;
double shoesOdom_theta = 0;

double get_shoesOdom_x()
{
    return shoesOdom_x;
}
double get_shoesOdom_y()
{
    return shoesOdom_y;
}
double get_shoesOdom_theta()
{
    return shoesOdom_theta;
}
void set_shoesOdom_x(double input)
{
    shoesOdom_x = input;
}
void set_shoesOdom_y(double input)
{
    shoesOdom_y = input;
}
void set_shoesOdom_theta(double input)
{
    shoesOdom_theta = input;
}
double shoesOdom_d_x = 0;
double shoesOdom_d_y = 0;
double shoesOdom_prev_theta = 0;
double shoesOdom_offset_theta = 0;
double shoesOdom_d_theta = 0;
double shoesOdom_initial_left = 0;
double shoesOdom_initial_right = 0;
double shoesOdom_d_pos = 0;

void shoesOdom_reset_all()
{
    shoesOdom_x = 0;
    shoesOdom_y = 0;
    shoesOdom_theta = 0;
    shoesOdom_d_x = 0;
    shoesOdom_d_y = 0;
    shoesOdom_prev_theta = 0;
    shoesOdom_offset_theta = 0;
    shoesOdom_d_theta = 0;
    shoesOdom_initial_left = 0;
    shoesOdom_initial_right = 0;
    shoesOdom_d_pos = 0;
}
void shoesOdom_reset_pos(double new_left, double new_right, double new_x = 0, double new_y = 0, double new_theta = 0)
{
    shoesOdom_x = 0;
    shoesOdom_y = 0;
    shoesOdom_theta = 0;
    shoesOdom_offset_theta = 0;
    shoesOdom_initial_left = 0;
    shoesOdom_initial_right = 0;
}
void shoesOdom_update_theta(double d_left_RAD, double d_right_RAD)
{
    double d_left = d_left_RAD * LEFT_TRACKING_WHEEL_CONVERSION;
    double d_right = d_right_RAD * RIGHT_TRACKING_WHEEL_CONVERSION;
    
    shoesOdom_d_theta = ((d_right - d_left)/ROBOT_WIDTH);
    shoesOdom_theta = shoesMath_mod(shoesOdom_theta + shoesOdom_d_theta, 2*PI);
}
void shoesOdom_update_pos(double d_left_RAD, double d_right_RAD, double d_back_RAD = 0)
{
    shoesOdom_update_theta(d_left_RAD, d_right_RAD);
    
    double d_left = d_left_RAD * LEFT_TRACKING_WHEEL_CONVERSION;
    double d_right = d_right_RAD * RIGHT_TRACKING_WHEEL_CONVERSION;
    double d_back = d_back_RAD * BACK_TRACKING_WHEEL_CONVERSION;

    d_back *= BACK_TRACKING_WHEEL_CONVERSION;
    
    double d_arc = (d_left + d_right)/2;
    
    shoesOdom_d_theta = (d_left - d_right)/ROBOT_WIDTH;
    
    shoesOdom_theta += shoesOdom_d_theta;

    double dist = 0;
    if (shoesOdom_d_theta != 0)
    {
        dist = shoesMath_cosine_rad((PI - shoesOdom_d_theta) / 2) * (d_arc / shoesOdom_d_theta) * 2;
    }
    else
    {
        dist = d_left;
    }
    
    double dist2 = d_back;
    
    shoesOdom_d_x = shoesMath_cosine_rad(shoesOdom_theta - shoesOdom_d_theta) * dist + shoesMath_cosine_rad(shoesOdom_theta * dist2);
    shoesOdom_d_y = shoesMath_sin_rad(shoesOdom_theta - shoesOdom_d_theta) * dist + shoesMath_sin_rad(shoesOdom_theta * dist2);

    shoesOdom_x += shoesOdom_d_x;
    shoesOdom_y += shoesOdom_d_y;
}

// CAJ Comp - Sensor Config and Updates - JShoes
// This is a file for me to consolidate all my sensor intializing and updates to keep my code a bit cleaner

double start_NameEncoder_rad = 0;
double current_NameEncoder_rad = 0;
double prev_NameEncoder_rad = 0;
double d_NameEncoder_rad = 0;
double reversed_NameEncoder = 0;

double start_LeftEncoder_rad = 0;
double current_LeftEncoder_rad = 0;
double prev_LeftEncoder_rad = 0;
double d_LeftEncoder_rad = 0;
double reversed_LeftEncoder = 0;

double start_RightEncoder_rad = 0;
double current_RightEncoder_rad = 0;
double prev_RightEncoder_rad = 0;
double d_RightEncoder_rad = 0;
double reversed_RightEncoder = 0;

double start_Gyro1_rad = 0;
double current_Gyro1_rad = 0;
double prev_Gyro1_rad = 0;
double d_Gyro1_rad = 0;

double start_Gyro2_rad = 0;
double current_Gyro2_rad = 0;
double prev_Gyro2_rad = 0;
double d_Gyro2_rad = 0;

double current_PuncherLimit_value = 0;
double prev_PuncherLimit_value = 0;

double current_IntakeLimit_value = 0;
double prev_IntakeLimit_value = 0;


void PuncherLimit_update()
{
	prev_PuncherLimit_value = current_PuncherLimit_value;
	current_PuncherLimit_value = PuncherLimit.pressing();
}
void IntakeLimit_update()
{
	prev_IntakeLimit_value = current_IntakeLimit_value;
	current_IntakeLimit_value = IntakeLimit.pressing();
}
void Gyro1_update()
{
	prev_Gyro1_rad = current_Gyro1_rad;
	current_Gyro1_rad = Gyro1.value(vex::rotationUnits::deg);
	d_Gyro1_rad = current_Gyro1_rad - prev_Gyro1_rad;
}
void Gyro2_update()
{
	prev_Gyro2_rad = current_Gyro2_rad;
	current_Gyro2_rad = Gyro2.value(vex::rotationUnits::deg);
	d_Gyro2_rad = current_Gyro2_rad - prev_Gyro2_rad;
}
void NameEncoder_update()
{
	prev_NameEncoder_rad = current_NameEncoder_rad;
	// current_NameEncoder_rad = shoesMath_rad(NameEncoder.rotation(vex::rotationUnits::deg)) * ((reversed_nameEncoder*2)-1);
	d_NameEncoder_rad = current_NameEncoder_rad - prev_NameEncoder_rad;
}
void LeftEncoder_update()
{
	prev_LeftEncoder_rad = current_LeftEncoder_rad;
	current_LeftEncoder_rad = shoesMath_rad(LeftEncoder.rotation(vex::rotationUnits::deg)) * ((reversed_LeftEncoder*2)-1);
	d_LeftEncoder_rad = current_LeftEncoder_rad - prev_LeftEncoder_rad;
}
void RightEncoder_update()
{
	prev_RightEncoder_rad = current_RightEncoder_rad;
	current_RightEncoder_rad = shoesMath_rad(RightEncoder.rotation(vex::rotationUnits::deg)) * ((reversed_RightEncoder*2)-1);
	d_RightEncoder_rad = current_RightEncoder_rad - prev_RightEncoder_rad;
}
void chassisEncoders_update()
{
	LeftEncoder_update();
	RightEncoder_update();
}
void allEncoders_update()
{
	chassisEncoders_update();
}
void gyros_update()
{
	Gyro1_update();
	Gyro2_update();
}
void limits_update()
{
	PuncherLimit_update();
	IntakeLimit_update();
}
void allSensors_update()
{
	limits_update();
	gyros_update();
	allEncoders_update();
}

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
void Controller1_Axis1_update()
{
    prev_Axis1_value = current_Axis1_value;
    current_Axis1_value = Controller1.Axis1.value();
}

float prev_Axis2_value = 0;
float current_Axis2_value = 0;
void Controller1_Axis2_update()
{
    prev_Axis2_value = current_Axis2_value;
    current_Axis2_value = Controller1.Axis2.value();
}

float prev_Axis3_value = 0;
float current_Axis3_value = 0;
void Controller1_Axis3_update()
{
    prev_Axis3_value = current_Axis3_value;
    current_Axis3_value = Controller1.Axis3.value();
}

float prev_Axis4_value = 0;
float current_Axis4_value = 0;
void Controller1_Axis4_update()
{
    prev_Axis4_value = current_Axis4_value;
    current_Axis4_value = Controller1.Axis4.value();
}

int prev_ButtonUp_pressing = 0;
int current_ButtonUp_pressing = 0;
void Controller1_ButtonUp_update()
{
    prev_ButtonUp_pressing = current_ButtonUp_pressing;
    current_ButtonUp_pressing = Controller1.ButtonUp.pressing() == 1 ? 1 : 0;
}

int prev_ButtonDown_pressing = 0;
int current_ButtonDown_pressing = 0;
void Controller1_ButtonDown_update()
{
    prev_ButtonDown_pressing = current_ButtonDown_pressing;
    current_ButtonDown_pressing = Controller1.ButtonDown.pressing() == 1 ? 1 : 0;
}

int prev_ButtonLeft_pressing = 0;
int current_ButtonLeft_pressing = 0;
void Controller1_ButtonLeft_update()
{
    prev_ButtonLeft_pressing = current_ButtonLeft_pressing;
    current_ButtonLeft_pressing = Controller1.ButtonLeft.pressing() == 1 ? 1 : 0;
}

int prev_ButtonRight_pressing = 0;
int current_ButtonRight_pressing = 0;
void Controller1_ButtonRight_update()
{
    prev_ButtonRight_pressing = current_ButtonRight_pressing;
    current_ButtonRight_pressing = Controller1.ButtonRight.pressing() == 1 ? 1 : 0;
}

int prev_ButtonA_pressing = 0;
int current_ButtonA_pressing = 0;
void Controller1_ButtonA_update()
{
    prev_ButtonA_pressing = current_ButtonA_pressing;
    current_ButtonA_pressing = Controller1.ButtonA.pressing() == 1 ? 1 : 0;
}

int prev_ButtonB_pressing = 0;
int current_ButtonB_pressing = 0;
void Controller1_ButtonB_update()
{
    prev_ButtonB_pressing = current_ButtonB_pressing;
    current_ButtonB_pressing = Controller1.ButtonB.pressing() == 1 ? 1 : 0;
}

int prev_ButtonX_pressing = 0;
int current_ButtonX_pressing = 0;
void Controller1_ButtonX_update()
{
    prev_ButtonX_pressing = current_ButtonX_pressing;
    current_ButtonX_pressing = Controller1.ButtonX.pressing() == 1 ? 1 : 0;
}

int prev_ButtonY_pressing = 0;
int current_ButtonY_pressing = 0;
void Controller1_ButtonY_update()
{
    prev_ButtonY_pressing = current_ButtonY_pressing;
    current_ButtonY_pressing = Controller1.ButtonY.pressing() == 1 ? 1 : 0;
}

int prev_ButtonL1_pressing = 0;
int current_ButtonL1_pressing = 0;
void Controller1_ButtonL1_update()
{
    prev_ButtonL1_pressing = current_ButtonL1_pressing;
    current_ButtonL1_pressing = Controller1.ButtonL1.pressing() == 1 ? 1 : 0;
}

int prev_ButtonL2_pressing = 0;
int current_ButtonL2_pressing = 0;
void Controller1_ButtonL2_update()
{
    prev_ButtonL2_pressing = current_ButtonL2_pressing;
    current_ButtonL2_pressing = Controller1.ButtonL2.pressing() == 1 ? 1 : 0;
}

int prev_ButtonR1_pressing = 0;
int current_ButtonR1_pressing = 0;
void Controller1_ButtonR1_update()
{
    prev_ButtonR1_pressing = current_ButtonR1_pressing;
    current_ButtonR1_pressing = Controller1.ButtonR1.pressing() == 1 ? 1 : 0;
}

int prev_ButtonR2_pressing = 0;
int current_ButtonR2_pressing = 0;
void Controller1_ButtonR2_update()
{
    prev_ButtonR2_pressing = current_ButtonR2_pressing;
    current_ButtonR2_pressing = Controller1.ButtonR2.pressing() == 1 ? 1 : 0;
}

// a grouping function to make calling all the joystick _update functions simpler
void Controller1_Joysticks_update()
{
    Controller1_Axis1_update();
    Controller1_Axis2_update();
    Controller1_Axis3_update();
    Controller1_Axis4_update();
}

// more grouping functions
void Controller1_DirectionButtons_update()
{
    Controller1_ButtonUp_update();
    Controller1_ButtonDown_update();
    Controller1_ButtonLeft_update();
    Controller1_ButtonRight_update();
}

void Controller1_LetterButtons_update()
{
    Controller1_ButtonA_update();
    Controller1_ButtonB_update();
    Controller1_ButtonX_update();
    Controller1_ButtonY_update();
}

void Controller1_LTButtons_update()
{
    Controller1_ButtonL1_update();
    Controller1_ButtonL2_update();
}

void Controller1_RTButtons_update()
{
    Controller1_ButtonR1_update();
    Controller1_ButtonR2_update();
}

void Controller1_TriggerButtons_update()
{
    Controller1_LTButtons_update();
    Controller1_RTButtons_update();
}

void Controller1_Buttons_update()
{
    Controller1_TriggerButtons_update();
    Controller1_LetterButtons_update();
    Controller1_DirectionButtons_update();
}

void Controller1_update()
{
    Controller1_Buttons_update();
    Controller1_Joysticks_update();
}

// base slew rates
const int CHASSIS_STANDARD_SLEW_RATE = 20;
const int FAST_SLEW_RATE             = 50;
const int STANDARD_SLEW_RATE         = 10;

// variable is used to set the desired speed of the motor
int LeftMotors_power = 0;

// this variable is the rate at which the speed of the motor is desired to increase at. Controls acceleration
int LeftMotors_rate = CHASSIS_STANDARD_SLEW_RATE;

// this variable is the actual speed sent to the motor controllers, based on the desired power and rate.
int LeftMotors_actualPower = 0;

// this tells the motors what to do when the power is 0: coast, brake, or hold.
int LeftMotors_brakeMode = 1;
int LeftMotors_getPower()
{
	return LeftMotors_power;
}
int LeftMotors_getRate()
{
	return LeftMotors_rate;
}
int LeftMotors_getActualPower()
{
	return LeftMotors_actualPower;
}
int LeftMotors_getBrakeMode()
{
	return LeftMotors_brakeMode;
}

// this function is what is used to set power to the left side of the chassis in the main execution block (for the most part).
void LeftMotors_setPower(int input)
{
	LeftMotors_power = input;
}
void LeftMotors_setRate(int input)
{
	LeftMotors_rate = input;
}
void LeftMotors_setActualPower(int input)
{
	LeftMotors_actualPower = input;
}
void LeftMotors_setBrakeMode(int input)
{
	LeftMotors_brakeMode = input;
}
void LeftMotors_change(int input)
{
	LeftMotors_setPower(LeftMotors_getPower() + input);
	if (abs(LeftMotors_getPower()) > 100)
	{
		if (LeftMotors_getPower() > 0)
		{
			LeftMotors_setPower(100);
		}
		else
		{
			LeftMotors_setPower(-100);
		}
	}
}
void LeftMotors_change_multiplier(double input)
{
	LeftMotors_setPower(LeftMotors_getPower()*input);
	if (abs(LeftMotors_getPower()) > 100)
	{
		if (LeftMotors_getPower() > 0)
		{
			LeftMotors_setPower(100);
		}
		else
		{
			LeftMotors_setPower(-100);
		}
	}
}
void LeftMotors_update()
{
	if (abs(LeftMotors_getPower()) > 100)
	{
		if (abs(LeftMotors_getPower()) > 100)
		{
			if (LeftMotors_getPower() > 0)
			{
				LeftMotors_setPower(100);
			}
			else
			{
				LeftMotors_setPower(-100);
			}
		}
	}
	
	if (LeftMotors_getPower() != LeftMotors_getActualPower())
	{
		int temp_rate = LeftMotors_getRate();
		if (abs(LeftMotors_getPower()) < abs(LeftMotors_getActualPower()))
		{ 
			temp_rate *= 3;
		}
		if (abs(LeftMotors_getPower() - LeftMotors_getActualPower()) <= temp_rate)
		{
			LeftMotors_setActualPower(LeftMotors_getPower());
		}
		else if (LeftMotors_getPower() > LeftMotors_getActualPower())
		{
			LeftMotors_setActualPower(LeftMotors_getActualPower()+temp_rate);
		}
		else if (LeftMotors_getPower() < LeftMotors_getActualPower())
		{
			LeftMotors_setActualPower(LeftMotors_getActualPower()-temp_rate);
		}
	}

    if (LeftMotors_getPower() != 0)
	{
		LeftMotor1.spin(vex::directionType::fwd, LeftMotors_getActualPower(), vex::velocityUnits::pct);
		LeftMotor2.spin(vex::directionType::fwd, LeftMotors_getActualPower(), vex::velocityUnits::pct);
	}
    else
	{
        if (LeftMotors_getBrakeMode() == 0)
		{
			LeftMotor1.stop(vex::brakeType::coast); 
			LeftMotor2.stop(vex::brakeType::coast);
		}
        else if (LeftMotors_getBrakeMode() == 1)
		{
			LeftMotor1.stop(vex::brakeType::brake); 
			LeftMotor2.stop(vex::brakeType::brake);
		}
        else if (LeftMotors_getBrakeMode() == 3)
		{
			LeftMotor1.stop(vex::brakeType::hold); 
			LeftMotor2.stop(vex::brakeType::hold);
		}
		else
		{
			LeftMotor1.spin(vex::directionType::fwd, LeftMotors_getActualPower(), vex::velocityUnits::pct);
			LeftMotor2.spin(vex::directionType::fwd, LeftMotors_getActualPower(), vex::velocityUnits::pct);
		}
    }
}

int RightMotors_power = 0;
int RightMotors_rate = CHASSIS_STANDARD_SLEW_RATE;
int RightMotors_actualPower = 0;
int RightMotors_brakeMode = 1;
int RightMotors_getPower()
{
	return RightMotors_power;
}
int RightMotors_getRate()
{
	return RightMotors_rate;
}
int RightMotors_getActualPower()
{
	return RightMotors_actualPower;
}
int RightMotors_getBrakeMode()
{
	return RightMotors_brakeMode;
}
void RightMotors_setPower(int input)
{
	RightMotors_power = input;
}
void RightMotors_setRate(int input)
{
	RightMotors_rate = input;
}
void RightMotors_setActualPower(int input)
{
	RightMotors_actualPower = input;
}
void RightMotors_setBrakeMode(int input)
{
	RightMotors_brakeMode = input;
}
void RightMotors_change(int input)
{
	RightMotors_setPower(RightMotors_getPower() + input);
	if (abs(RightMotors_getPower()) > 100)
	{
		if (RightMotors_getPower() > 0)
		{
			RightMotors_setPower(100);
		}
		else
		{
			RightMotors_setPower(-100);
		}
	}
}
void RightMotors_change_multiplier(double input)
{
	RightMotors_setPower(RightMotors_getPower()*input);
	if (abs(RightMotors_getPower()) > 100)
	{
		if (RightMotors_getPower() > 0)
		{
			RightMotors_setPower(100);
		}
		else
		{
			RightMotors_setPower(-100);
		}
	}
}
void RightMotors_update()
{
	if (abs(RightMotors_getPower()) > 100)
	{
		if (abs(RightMotors_getPower()) > 100)
		{
			if (RightMotors_getPower() > 0)
			{
				RightMotors_setPower(100);
			}
			else
			{
				RightMotors_setPower(-100);
			}
		}
	}
	
	if (RightMotors_getPower() != RightMotors_getActualPower())
	{
		int temp_rate = RightMotors_getRate();
		if (abs(RightMotors_getPower()) < abs(RightMotors_getActualPower()))
		{ 
			temp_rate *= 3;
		}
		if (abs(RightMotors_getPower() - RightMotors_getActualPower()) <= temp_rate)
		{
			RightMotors_setActualPower(RightMotors_getPower());
		}
		else if (RightMotors_getPower() > RightMotors_getActualPower())
		{
			RightMotors_setActualPower(RightMotors_getActualPower()+temp_rate);
		}
		else if (RightMotors_getPower() < RightMotors_getActualPower())
		{
			RightMotors_setActualPower(RightMotors_getActualPower()-temp_rate);
		}
	}

    if (RightMotors_getPower() != 0)
	{
		RightMotor1.spin(vex::directionType::fwd, RightMotors_getActualPower(), vex::velocityUnits::pct);
		RightMotor2.spin(vex::directionType::fwd, RightMotors_getActualPower(), vex::velocityUnits::pct);
	}
    else
	{
        if (RightMotors_getBrakeMode() == 0)
		{
			RightMotor1.stop(vex::brakeType::coast); 
			RightMotor2.stop(vex::brakeType::coast);
		}
        else if (RightMotors_getBrakeMode() == 1)
		{
			RightMotor1.stop(vex::brakeType::brake); 
			RightMotor2.stop(vex::brakeType::brake);
		}
        else if (RightMotors_getBrakeMode() == 3)
		{
			RightMotor1.stop(vex::brakeType::hold); 
			RightMotor2.stop(vex::brakeType::hold);
		}
		else
		{
			RightMotor1.spin(vex::directionType::fwd, RightMotors_getActualPower(), vex::velocityUnits::pct);
			RightMotor2.spin(vex::directionType::fwd, RightMotors_getActualPower(), vex::velocityUnits::pct);
		}
    }
}

int IntakeMotor_power = 0;
int IntakeMotor_rate = CHASSIS_STANDARD_SLEW_RATE;
int IntakeMotor_actualPower = 0;
int IntakeMotor_brakeMode = 1;
int IntakeMotor_getPower()
{
	return IntakeMotor_power;
}
int IntakeMotor_getRate()
{
	return IntakeMotor_rate;
}
int IntakeMotor_getActualPower()
{
	return IntakeMotor_actualPower;
}
int IntakeMotor_getBrakeMode()
{
	return IntakeMotor_brakeMode;
}
void IntakeMotor_setPower(int input)
{
	IntakeMotor_power = input;
}
void IntakeMotor_setRate(int input)
{
	IntakeMotor_rate = input;
}
void IntakeMotor_setActualPower(int input)
{
	IntakeMotor_actualPower = input;
}
void IntakeMotor_setBrakeMode(int input)
{
	IntakeMotor_brakeMode = input;
}
void IntakeMotor_change(int input)
{
	IntakeMotor_setPower(IntakeMotor_getPower() + input);
	if (abs(IntakeMotor_getPower()) > 100)
	{
		if (IntakeMotor_getPower() > 0)
		{
			IntakeMotor_setPower(100);
		}
		else
		{
			IntakeMotor_setPower(-100);
		}
	}
}
void IntakeMotor_change_multiplier(double input)
{
	IntakeMotor_setPower(IntakeMotor_getPower()*input);
	if (abs(IntakeMotor_getPower()) > 100)
	{
		if (IntakeMotor_getPower() > 0)
		{
			IntakeMotor_setPower(100);
		}
		else
		{
			IntakeMotor_setPower(-100);
		}
	}
}
void IntakeMotor_update()
{
	if (abs(IntakeMotor_getPower()) > 100)
	{
		if (abs(IntakeMotor_getPower()) > 100)
		{
			if (IntakeMotor_getPower() > 0)
			{
				IntakeMotor_setPower(100);
			}
			else
			{
				IntakeMotor_setPower(-100);
			}
		}
	}
	
	if (IntakeMotor_getPower() != IntakeMotor_getActualPower())
	{
		int temp_rate = IntakeMotor_getRate();
		if (abs(IntakeMotor_getPower()) < abs(IntakeMotor_getActualPower()))
		{ 
			temp_rate *= 3;
		}
		if (abs(IntakeMotor_getPower() - IntakeMotor_getActualPower()) <= temp_rate)
		{
			IntakeMotor_setActualPower(IntakeMotor_getPower());
		}
		else if (IntakeMotor_getPower() > IntakeMotor_getActualPower())
		{
			IntakeMotor_setActualPower(IntakeMotor_getActualPower()+temp_rate);
		}
		else if (IntakeMotor_getPower() < IntakeMotor_getActualPower())
		{
			IntakeMotor_setActualPower(IntakeMotor_getActualPower()-temp_rate);
		}
	}

    if (IntakeMotor_getPower() != 0)
	{
		IntakeMotor.spin(vex::directionType::fwd, IntakeMotor_getActualPower(), vex::velocityUnits::pct);
	}
    else
	{
        if (IntakeMotor_getBrakeMode() == 0)
		{
			IntakeMotor.stop(vex::brakeType::coast); 
		}
        else if (IntakeMotor_getBrakeMode() == 1)
		{
			IntakeMotor.stop(vex::brakeType::brake); 
		}
        else if (IntakeMotor_getBrakeMode() == 3)
		{
			IntakeMotor.stop(vex::brakeType::hold); 
		}
		else
		{
			IntakeMotor.spin(vex::directionType::fwd, IntakeMotor_getActualPower(), vex::velocityUnits::pct);
		}
    }
}

int PuncherMotor_power = 0;
int PuncherMotor_rate = CHASSIS_STANDARD_SLEW_RATE;
int PuncherMotor_actualPower = 0;
int PuncherMotor_brakeMode = 1;
int PuncherMotor_getPower()
{
	return PuncherMotor_power;
}
int PuncherMotor_getRate()
{
	return PuncherMotor_rate;
}
int PuncherMotor_getActualPower()
{
	return PuncherMotor_actualPower;
}
int PuncherMotor_getBrakeMode()
{
	return PuncherMotor_brakeMode;
}
void PuncherMotor_setPower(int input)
{
	PuncherMotor_power = input;
}
void PuncherMotor_setRate(int input)
{
	PuncherMotor_rate = input;
}
void PuncherMotor_setActualPower(int input)
{
	PuncherMotor_actualPower = input;
}
void PuncherMotor_setBrakeMode(int input)
{
	PuncherMotor_brakeMode = input;
}
void PuncherMotor_change(int input)
{
	PuncherMotor_setPower(PuncherMotor_getPower() + input);
	if (abs(PuncherMotor_getPower()) > 100)
	{
		if (PuncherMotor_getPower() > 0)
		{
			PuncherMotor_setPower(100);
		}
		else
		{
			PuncherMotor_setPower(-100);
		}
	}
}
void PuncherMotor_change_multiplier(double input)
{
	PuncherMotor_setPower(PuncherMotor_getPower()*input);
	if (abs(PuncherMotor_getPower()) > 100)
	{
		if (PuncherMotor_getPower() > 0)
		{
			PuncherMotor_setPower(100);
		}
		else
		{
			PuncherMotor_setPower(-100);
		}
	}
}
void PuncherMotor_update()
{
	if (abs(PuncherMotor_getPower()) > 100)
	{
		if (abs(PuncherMotor_getPower()) > 100)
		{
			if (PuncherMotor_getPower() > 0)
			{
				PuncherMotor_setPower(100);
			}
			else
			{
				PuncherMotor_setPower(-100);
			}
		}
	}
	
	if (PuncherMotor_getPower() != PuncherMotor_getActualPower())
	{
		int temp_rate = PuncherMotor_getRate();
		if (abs(PuncherMotor_getPower()) < abs(PuncherMotor_getActualPower()))
		{ 
			temp_rate *= 3;
		}
		if (abs(PuncherMotor_getPower() - PuncherMotor_getActualPower()) <= temp_rate)
		{
			PuncherMotor_setActualPower(PuncherMotor_getPower());
		}
		else if (PuncherMotor_getPower() > PuncherMotor_getActualPower())
		{
			PuncherMotor_setActualPower(PuncherMotor_getActualPower()+temp_rate);
		}
		else if (PuncherMotor_getPower() < PuncherMotor_getActualPower())
		{
			PuncherMotor_setActualPower(PuncherMotor_getActualPower()-temp_rate);
		}
	}

    if (PuncherMotor_getPower() != 0)
	{
		PuncherMotor.spin(vex::directionType::fwd, PuncherMotor_getActualPower(), vex::velocityUnits::pct);
	}
    else
	{
        if (PuncherMotor_getBrakeMode() == 0)
		{
			PuncherMotor.stop(vex::brakeType::coast); 
		}
        else if (PuncherMotor_getBrakeMode() == 1)
		{
			PuncherMotor.stop(vex::brakeType::brake); 
		}
        else if (PuncherMotor_getBrakeMode() == 3)
		{
			PuncherMotor.stop(vex::brakeType::hold); 
		}
		else
		{
			PuncherMotor.spin(vex::directionType::fwd, PuncherMotor_getActualPower(), vex::velocityUnits::pct);
		}
    }
}

void Motors_updateAll()
{
	LeftMotors_update();
	RightMotors_update();
	IntakeMotor_update();
	PuncherMotor_update();

	LeftMotors_setPower(0);
	RightMotors_setPower(0);
	IntakeMotor_setPower(0);
	PuncherMotor_setPower(0);
}

// Used to select the autonomoun route that should be run
int auton_route = 0;

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

void usercontrol_chassisControl()
{
    LeftMotors_setPower(current_Axis3_value);
    RightMotors_setPower(current_Axis2_value);
}

int usercontrol_intakeMode = 0;
void usercontrol_intakeControl()
{
    if (current_ButtonL1_pressing && !prev_ButtonL1_pressing)
    {
        usercontrol_intakeMode = (usercontrol_intakeMode == 1) ? 0 : 1;
    }
    else if (current_ButtonL2_pressing && !prev_ButtonL2_pressing)
    {
        usercontrol_intakeMode = (usercontrol_intakeMode == -1) ? 0 : -1;
    }

    if (usercontrol_intakeMode == 1)
    {
        IntakeMotor_setPower(60);
        if (current_PuncherLimit_value == 1 && current_IntakeLimit_value == 1)
        {
            usercontrol_intakeMode = 0;
        }
    }
    else if (usercontrol_intakeMode == -1)
    {
        IntakeMotor_setPower(-100);
    }
    else
    {
        IntakeMotor_setPower(0);
    }
}

void usercontrol_puncherControl()
{
    if (current_ButtonR1_pressing)
    {
        PuncherMotor_setPower(50);
    }
    else
    {
        PuncherMotor_setPower(0);
    }
}

void user_loop()
{
    Controller1_update();
    allSensors_update();

    usercontrol_chassisControl();
    usercontrol_intakeControl();
    usercontrol_puncherControl();

    Motors_updateAll();
}

void pre_auton( void )
{
	Brain.resetTimer();
	Brain.setTimer(0, vex::timeUnits::msec);
}

void autonomous( void )
{
	while (true)
    {
		auton_loop();
    }
}

void usercontrol( void )
{
	while (true)
    {
        user_loop();
    }
}

int main()
{
    pre_auton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );                        
    while (true)
    {
        vex::task::sleep(500);
    } 
}