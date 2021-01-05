#include "math_functions.h"
#include "motor_control.h"
#include "controller.h"
#include "sensors.h"

void usercontrol_chassisControl()
{
    LeftMotors_setPower(current_Axis3_value);
    RightMotors_setPower(current_Axis2_value);
}

int usercontrol_intakeMode = 0;
void usercontrol_intakeControl()
{
    if (current_ButtonL1_pressing && !prev_ButtonL1_pressing)
    {
        usercontrol_intakeMode = (usercontrol_intakeMode == 1) ? 0 : 1;
    }
    else if (current_ButtonL2_pressing && !prev_ButtonL2_pressing)
    {
        usercontrol_intakeMode = (usercontrol_intakeMode == -1) ? 0 : -1;
    }

    if (usercontrol_intakeMode == 1)
    {
        IntakeMotor_setPower(60);
        if (current_PuncherLimit_value == 1 && current_IntakeLimit_value == 1)
        {
            usercontrol_intakeMode = 0;
        }
    }
    else if (usercontrol_intakeMode == -1)
    {
        IntakeMotor_setPower(-100);
    }
    else
    {
        IntakeMotor_setPower(0);
    }
}

void usercontrol_puncherControl()
{
    if (current_ButtonR1_pressing)
    {
        PuncherMotor_setPower(50);
    }
    else
    {
        PuncherMotor_setPower(0);
    }
}

void user_loop()
{
    Controller1_update();
    allSensors_update();

    usercontrol_chassisControl();
    usercontrol_intakeControl();
    usercontrol_puncherControl();

    Motors_updateAll();
}