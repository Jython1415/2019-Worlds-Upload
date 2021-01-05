# define PI 3.14159265

double corrected_atan(double rise, double run)
{
	if (run == 0)
	{
		return 0;
	}
	else
	{
		double ratio = rise/run;
		double raw = atan(ratio);
		double output = raw;
		if (rise < 0) 
		{
			output += PI;
		}
		return output;
	}
}

double rad(double deg)
{
	return deg*(PI/180);
}