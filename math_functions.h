#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

const double MASTER_MOE;
const double         PI;

// returns the absolute value of the input. Input can be any integer or double but it returns the value as a double.
double shoesMath_abs(double input);

// returns the remainder of dividing the input by the divisor. It can take integer, double, negative, or positive input.
// divisor must be positive.
double shoesMath_mod(double input, double divisor);

// the input and maximum value both must be positive.
// if the input is greater than the max, it returns the max. otherwise it returns the input as is.
double shoesMath_max(double value, double max);

// the input and maximum value both can be positive or negative double.
// if the input is negative and less than the maximum, it returns the negative maximum.
// if the input is positive and greater than the maximum, it returns the positive maximum.
// otherwise it returns the input as is.
double shoesMath_abs_max(double value, double abs_max);

// converts degrees to radians. Input should be a double.
double shoesMath_rad(double deg);

// converts radians to degrees. Input should be a double.
double shoesMath_deg(double rad);

// input should be in radians. returns 0 if the input does not lie on one of the axis.
// 1 is the positive x axis, 2 is the positive y axis, 3 is the negative x axis, 4 is the negative y axis.
// the margin of error for floating point error is determined by the MASTER_MOE constant.
int axis_rad (double input);

// input should be in radians. returns 0 if the input does not lie in one of the quadrants.
// 1, 2, 3, and 4 are each of the quadrants respectively.
// the margin of error for floating point error is determined by the MASTER_MOE constant.
int quadrant_rad(double input);

// takes in an angle in radians and converts it to an equavilent positive angle less than 2 PI.
double simplify_rad(double input);

// input must be in radians.
// returns the angle as it would be reflected across the x-axis.
double reflect_x_rad(double input);

// input must be in radians.
// returns the angle as it would be reflected across the y-axis.
double reflect_y_rad(double input);

// input must in radians.
// returns sine of the input with 3 significant figures.
double shoesMath_sin_rad(double input);

// input must in radians.
// returns cosine of the input with 3 significant figures.
double shoesMath_cosine_rad(double input);

// input must in radians.
// returns tangent of the input with 3 significant figures.
double shoesMath_tangent_rad(double input);

#endif