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