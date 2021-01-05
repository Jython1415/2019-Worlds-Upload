#include "math_functions.h"

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