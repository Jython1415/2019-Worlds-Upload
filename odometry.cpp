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