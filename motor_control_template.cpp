// base slew rates
const int CHASSIS_STANDARD_SLEW_RATE 20
const int FAST_SLEW_RATE             50
const int STANDARD_SLEW_RATE         10

int NameMotor_power = 0;
int NameMotor_rate = CHASSIS_STANDARD_SLEW_RATE;
int NameMotor_actualPower = 0;
int NameMotor_brakeMode = 1;
int NameMotor_getPower()
{
	return NameMotor_power;
}
int NameMotor_getRate()
{
	return NameMotor_rate;
}
int NameMotor_getActualPower()
{
	return NameMotor_actualPower;
}
int NameMotor_getBrakeMode()
{
	return NameMotor_brakeMode;
}
void NameMotor_setPower(int input)
{
	NameMotor_power = input;
}
void NameMotor_setRate(int input)
{
	NameMotor_rate = input;
}
void NameMotor_setActualPower(int input)
{
	NameMotor_actualPower = input;
}
void NameMotor_setBrakeMode(int input)
{
	NameMotor_brakeMode = input;
}
void NameMotor_change(int input)
{
	NameMotor_setPower(NameMotor_getPower() + input);
	if (abs(NameMotor_getPower()) > 100)
	{
		if (NameMotor_getPower() > 0)
		{
			NameMotor_setPower(100);
		}
		else
		{
			NameMotor_setPower(-100);
		}
	}
}
void NameMotor_change_multiplier(double input)
{
	NameMotor_setPower(NameMotor_getPower()*input);
	if (abs(NameMotor_getPower()) > 100)
	{
		if (NameMotor_getPower() > 0)
		{
			NameMotor_setPower(100);
		}
		else
		{
			NameMotor_setPower(-100);
		}
	}
}
void NameMotor_update()
{
	if (abs(NameMotor_getPower()) > 100)
	{
		if (abs(NameMotor_getPower()) > 100)
		{
			if (NameMotor_getPower() > 0)
			{
				NameMotor_setPower(100);
			}
			else
			{
				NameMotor_setPower(-100);
			}
		}
	}
	
	if (NameMotor_getPower() != NameMotor_getActualPower())
	{
		int temp_rate = NameMotor_getRate();
		if (abs(NameMotor_getPower()) < abs(NameMotor_getActualPower()))
		{ 
			temp_rate *= 3;
		}
		if (abs(NameMotor_getPower() - NameMotor_getActualPower()) <= temp_rate)
		{
			NameMotor_setActualPower(NameMotor_getPower());
		}
		else if (NameMotor_getPower() > NameMotor_getActualPower())
		{
			NameMotor_setActualPower(NameMotor_getActualPower()+temp_rate);
		}
		else if (NameMotor_getPower() < NameMotor_getActualPower())
		{
			NameMotor_setActualPower(NameMotor_getActualPower()-temp_rate);
		}
	}

    if (NameMotor_getPower() != 0)
	{
		NameMotor1.spin(vex::directionType::fwd, NameMotor_getActualPower(), vex::velocityUnits::pct);
		NameMotor2.spin(vex::directionType::fwd, NameMotor_getActualPower(), vex::velocityUnits::pct);
	}
    else
	{
        if (NameMotor_getBrakeMode() == 0)
		{
			NameMotor1.stop(vex::brakeType::coast); 
			NameMotor2.stop(vex::brakeType::coast);
		}
        else if (NameMotor_getBrakeMode() == 1)
		{
			NameMotor1.stop(vex::brakeType::brake); 
			NameMotor2.stop(vex::brakeType::brake);
		}
        else if (NameMotor_getBrakeMode() == 3)
		{
			NameMotor1.stop(vex::brakeType::hold); 
			NameMotor2.stop(vex::brakeType::hold);
		}
		else
		{
			NameMotor1.spin(vex::directionType::fwd, NameMotor_getActualPower(), vex::velocityUnits::pct);
			NameMotor2.spin(vex::directionType::fwd, NameMotor_getActualPower(), vex::velocityUnits::pct);
		}
    }
}

void Motors_updateAll()
{
	NameMotor_update();
}