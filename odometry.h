#ifndef ODOMETRY_H
#define ODOMETRY_H

// constants that describe the position and size of the tracking wheels - used for odometry
const double LEFT_TRACKING_WHEEL_CONVERSION  = 0.0000; // To convert radians into in
const double RIGHT_TRACKING_WHEEL_CONVERSION = 0.0000; // To convert radians into in
const double BACK_TRACKING_WHEEL_CONVERSION  = 0.0000; // To convert radians into in
const double ROBOT_WIDTH                     = 0.0000; // To convert radians into in
const double BACK_TRACKING_OFFSET            = 0.0000; // in

double shoesOdom_x = 0;
double shoesOdom_y = 0;
double shoesOdom_theta = 0;

double get_shoesOdom_x();
double get_shoesOdom_y();
double get_shoesOdom_theta();
void set_shoesOdom_x(double input);
void set_shoesOdom_y(double input);
void set_shoesOdom_theta(double input);

double shoesOdom_d_x = 0;
double shoesOdom_d_y = 0;
double shoesOdom_prev_theta = 0;
double shoesOdom_offset_theta = 0;
double shoesOdom_d_theta = 0;
double shoesOdom_initial_left = 0;
double shoesOdom_initial_right = 0;
double shoesOdom_d_pos = 0;

void shoesOdom_reset_all();
void shoesOdom_reset_pos(double new_left, double new_right, double new_x = 0, double new_y = 0, double new_theta = 0);
void shoesOdom_update_theta(double d_left_RAD, double d_right_RAD);
void shoesOdom_update_pos(double d_left_RAD, double d_right_RAD, double d_back_RAD = 0);

#endif ODOMETRY_H