#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
// base slew rates
const int CHASSIS_STANDARD_SLEW_RATE 20
const int FAST_SLEW_RATE             50
const int STANDARD_SLEW_RATE         10

// variable is used to set the desired speed of the motor
int LeftMotors_power = 0;

// this variable is the rate at which the speed of the motor is desired to increase at. Controls acceleration
int LeftMotors_rate = CHASSIS_STANDARD_SLEW_RATE;

// this variable is the actual speed sent to the motor controllers, based on the desired power and rate.
int LeftMotors_actualPower = 0;

// this tells the motors what to do when the power is 0: coast, brake, or hold.
int LeftMotors_brakeMode = 1;

int LeftMotors_getPower();
int LeftMotors_getRate();
int LeftMotors_getActualPower();
int LeftMotors_getBrakeMode();

// this function is what is used to set power to the left side of the chassis in the main execution block (for the most part).
void LeftMotors_setPower(int input);
void LeftMotors_setRate(int input);
void LeftMotors_setActualPower(int input);
void LeftMotors_setBrakeMode(int input);
void LeftMotors_change(int input);
void LeftMotors_change_multiplier(double input);
void LeftMotors_update();

int RightMotors_power = 0;
int RightMotors_rate = CHASSIS_STANDARD_SLEW_RATE;
int RightMotors_actualPower = 0;
int RightMotors_brakeMode = 1;

void RightMotors_setPower(int input);
void RightMotors_setRate(int input);
void RightMotors_setActualPower(int input);
void RightMotors_setBrakeMode(int input);
void RightMotors_change(int input);
void RightMotors_change_multiplier(double input);
void RightMotors_update();

int IntakeMotor_power = 0;
int IntakeMotor_rate = CHASSIS_STANDARD_SLEW_RATE;
int IntakeMotor_actualPower = 0;
int IntakeMotor_brakeMode = 1;

void IntakeMotor_setPower(int input);
void IntakeMotor_setRate(int input);
void IntakeMotor_setActualPower(int input);
void IntakeMotor_setBrakeMode(int input);
void IntakeMotor_change(int input);
void IntakeMotor_change_multiplier(double input);
void IntakeMotor_update();

int PuncherMotor_power = 0;
int PuncherMotor_rate = CHASSIS_STANDARD_SLEW_RATE;
int PuncherMotor_actualPower = 0;
int PuncherMotor_brakeMode = 1;

void PuncherMotor_setPower(int input);
void PuncherMotor_setRate(int input);
void PuncherMotor_setActualPower(int input);
void PuncherMotor_setBrakeMode(int input);
void PuncherMotor_change(int input);
void PuncherMotor_change_multiplier(double input);
void PuncherMotor_update();

void Motors_updateAll();

#endif