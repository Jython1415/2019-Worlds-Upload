#ifndef SENSORS_H
#define SENSORS_H
// CAJ Comp - Sensor Config and Updates - JShoes
// This is a file for me to consolidate all my sensor intializing and updates to keep my code a bit cleaner

double start_nameEncoder_rad = 0;
double current_nameEncoder_rad = 0;
double prev_nameEncoder_rad = 0;
double d_nameEncoder_rad = 0;
double reversed_nameEncoder = 0;

double start_leftEncoder_rad = 0;
double current_leftEncoder_rad = 0;
double prev_leftEncoder_rad = 0;
double d_leftEncoder_rad = 0;
double reversed_leftEncoder = 0;

double start_rightEncoder_rad = 0;
double current_rightEncoder_rad = 0;
double prev_rightEncoder_rad = 0;
double d_rightEncoder_rad = 0;
double reversed_rightEncoder = 0;

double start_gyro_rad = 0;
double current_gyro_rad = 0;
double prev_gyro_rad = 0;
double d_gyro_rad = 0;
double reversed_gyro = 0;

void gyro_update();
void nameEncoder_update();
void leftEncoder_update();
void rightEncoder_update();
void chassisEncoders_update();
void allEncoders_update();
void allSensors_update();

#endif