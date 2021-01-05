#include "robot-config.h"
/*++| ROBOT CONFIGURATION *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*//*
[Smart Port]         [Name]          [Type]           [Description]       [Reversed]
Motor Port 1                         V5 Smart Motor   
Motor Port 2                         V5 Smart Motor   
Motor Port 3                         V5 Smart Motor   
Motor Port 4                         V5 Smart Motor   
Motor Port 5                         V5 Smart Motor   
Motor Port 6                         V5 Smart Motor   
Motor Port 7                         V5 Smart Motor   
Motor Port 8                         V5 Smart Motor   
Motor Port 9                         V5 Smart Motor   
Motor Port 10                        V5 Smart Motor   
Motor Port 11                        V5 Smart Motor   
Motor Port 12                        V5 Smart Motor   
Motor Port 13                        V5 Smart Motor   
Motor Port 14                        V5 Smart Motor   
Motor Port 15                        V5 Smart Motor   
Motor Port 16                        V5 Smart Motor   
Motor Port 17                        V5 Smart Motor   
Motor Port 18                        V5 Smart Motor   
Motor Port 19                        V5 Smart Motor   
Motor Port 20                        V5 Smart Motor   
-------------------------------------------------------------------------------------------------*/

/*++| DOCUMENTATION *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*//*

-------------------------------------------------------------------------------------------------*/
vex::competition    Competition;

/*++| CONSTANTS *//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// default motor speeds used in user control and auton control
#define SUBSYSTEM_SPEED_PCT 100

#include "._math_functions.h"

void pre_auton( void )
{
	Brain.resetTimer();
	Brain.setTimer(0, vex::timeUnits::msec);
}

void autonomous( void )
{
	while (true)
    {
        auton_loop();
    }
}

void usercontrol( void )
{
	while (true)
    {
        user_loop();
    }
}

int main()
{
    pre_auton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );                        
    while (true)
    {
        vex::task::sleep(500);
    } 
}