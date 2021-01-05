// Controller Variables and Functions - JShoes
// Its a bit of a self contained piece of code I import into my VCS programming projects.
// It takes care of all the controller intricacies I've ever needed with a few simple functions.
// Keeps code looking fresh and neat.

// the prev_ value of a joystick and be used to determine the velocity of the joystick
// this may be useful in some advanced control optimization or applications
float prev_Axis1_value = 0;

// current_ is a simple read of the sensor value
float current_Axis1_value = 0;

// _update assigns new values to the prev_ and current_ variables
// it should be run before the values are neccessary, at the beginning of each loop
void Controller1_Axis1_update()
{
    prev_Axis1_value = current_Axis1_value;
    current_Axis1_value = Controller1.Axis1.value();
}

float prev_Axis2_value = 0;
float current_Axis2_value = 0;
void Controller1_Axis2_update()
{
    prev_Axis2_value = current_Axis2_value;
    current_Axis2_value = Controller1.Axis2.value();
}

float prev_Axis3_value = 0;
float current_Axis3_value = 0;
void Controller1_Axis3_update()
{
    prev_Axis3_value = current_Axis3_value;
    current_Axis3_value = Controller1.Axis3.value();
}

float prev_Axis4_value = 0;
float current_Axis4_value = 0;
void Controller1_Axis4_update()
{
    prev_Axis4_value = current_Axis4_value;
    current_Axis4_value = Controller1.Axis4.value();
}

int prev_ButtonUp_pressing = 0;
int current_ButtonUp_pressing = 0;
void Controller1_ButtonUp_update()
{
    prev_ButtonUp_pressing = current_ButtonUp_pressing;
    current_ButtonUp_pressing = Controller1.ButtonUp.pressing() == 1 ? 1 : 0;
}

int prev_ButtonDown_pressing = 0;
int current_ButtonDown_pressing = 0;
void Controller1_ButtonDown_update()
{
    prev_ButtonDown_pressing = current_ButtonDown_pressing;
    current_ButtonDown_pressing = Controller1.ButtonDown.pressing() == 1 ? 1 : 0;
}

int prev_ButtonLeft_pressing = 0;
int current_ButtonLeft_pressing = 0;
void Controller1_ButtonLeft_update()
{
    prev_ButtonLeft_pressing = current_ButtonLeft_pressing;
    current_ButtonLeft_pressing = Controller1.ButtonLeft.pressing() == 1 ? 1 : 0;
}

int prev_ButtonRight_pressing = 0;
int current_ButtonRight_pressing = 0;
void Controller1_ButtonRight_update()
{
    prev_ButtonRight_pressing = current_ButtonRight_pressing;
    current_ButtonRight_pressing = Controller1.ButtonRight.pressing() == 1 ? 1 : 0;
}

int prev_ButtonA_pressing = 0;
int current_ButtonA_pressing = 0;
void Controller1_ButtonA_update()
{
    prev_ButtonA_pressing = current_ButtonA_pressing;
    current_ButtonA_pressing = Controller1.ButtonA.pressing() == 1 ? 1 : 0;
}

int prev_ButtonB_pressing = 0;
int current_ButtonB_pressing = 0;
void Controller1_ButtonB_update()
{
    prev_ButtonB_pressing = current_ButtonB_pressing;
    current_ButtonB_pressing = Controller1.ButtonB.pressing() == 1 ? 1 : 0;
}

int prev_ButtonX_pressing = 0;
int current_ButtonX_pressing = 0;
void Controller1_ButtonX_update()
{
    prev_ButtonX_pressing = current_ButtonX_pressing;
    current_ButtonX_pressing = Controller1.ButtonX.pressing() == 1 ? 1 : 0;
}

int prev_ButtonY_pressing = 0;
int current_ButtonY_pressing = 0;
void Controller1_ButtonY_update()
{
    prev_ButtonY_pressing = current_ButtonY_pressing;
    current_ButtonY_pressing = Controller1.ButtonY.pressing() == 1 ? 1 : 0;
}

int prev_ButtonL1_pressing = 0;
int current_ButtonL1_pressing = 0;
void Controller1_ButtonL1_update()
{
    prev_ButtonL1_pressing = current_ButtonL1_pressing;
    current_ButtonL1_pressing = Controller1.ButtonL1.pressing() == 1 ? 1 : 0;
}

int prev_ButtonL2_pressing = 0;
int current_ButtonL2_pressing = 0;
void Controller1_ButtonL2_update()
{
    prev_ButtonL2_pressing = current_ButtonL2_pressing;
    current_ButtonL2_pressing = Controller1.ButtonL2.pressing() == 1 ? 1 : 0;
}

int prev_ButtonR1_pressing = 0;
int current_ButtonR1_pressing = 0;
void Controller1_ButtonR1_update()
{
    prev_ButtonR1_pressing = current_ButtonR1_pressing;
    current_ButtonR1_pressing = Controller1.ButtonR1.pressing() == 1 ? 1 : 0;
}

int prev_ButtonR2_pressing = 0;
int current_ButtonR2_pressing = 0;
void Controller1_ButtonR2_update()
{
    prev_ButtonR2_pressing = current_ButtonR2_pressing;
    current_ButtonR2_pressing = Controller1.ButtonR2.pressing() == 1 ? 1 : 0;
}

// a grouping function to make calling all the joystick _update functions simpler
void Controller1_Joysticks_update()
{
    Controller1_Axis1_update();
    Controller1_Axis2_update();
    Controller1_Axis3_update();
    Controller1_Axis4_update();
}

// more grouping functions
void Controller1_DirectionButtons_update()
{
    Controller1_ButtonUp_update();
    Controller1_ButtonDown_update();
    Controller1_ButtonLeft_update();
    Controller1_ButtonRight_update();
}

void Controller1_LetterButtons_update()
{
    Controller1_ButtonA_update();
    Controller1_ButtonB_update();
    Controller1_ButtonX_update();
    Controller1_ButtonY_update();
}

void Controller1_LTButtons_update()
{
    Controller1_ButtonL1_update();
    Controller1_ButtonL2_update();
}

void Controller1_RTButtons_update()
{
    Controller1_ButtonR1_update();
    Controller1_ButtonR2_update();
}

void Controller1_TriggerButtons_update()
{
    Controller1_LTButtons_update();
    Controller1_RTButtons_update();
}

void Controller1_Buttons_update()
{
    Controller1_TriggerButtons_update();
    Controller1_LetterButtons_update();
    Controller1_DirectionButtons_update();
}

void Controller1_update()
{
    Controller1_Buttons_update();
    Controller1_Joysticks_update();
}