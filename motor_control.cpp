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