#include "ros/ros.h"
#include "ros_robo15/Gamepad_cmd.h"

//#define float64	double
//#define int8	int

#define SHOOT_ONES	1
#define SHOOT_TWER	2
#define SHOOT_ENMY	3

#define AXIS_VAL_MAX	32767
#define AXIS_VAL_BIAS	32767

#define AXIS_X_BITS	4
#define AXIS_Y_BITS	3
#define AXIS_T_BITS	4

/*typedef struct Gamepad_cmd{
    float64 left_axis_x;
    float64 left_axis_y;
    float64 right_axis_x;
    float64 right_axis_y;

    bool button_x;
    bool button_a;
    bool button_b;
    bool button_y;

    int8 hat_x;
    int8 hat_y;

    bool left_bumper;
    bool right_bumper;

    bool left_trigger;
    bool right_trigger;

    bool button_back;
    bool button_start;

    bool left_axis_push;
    bool right_axis_push;
}Gpads_cmd;*/

//unsigned char makeFirCmd(Gpads_cmd p_cmd);
unsigned char makeFirCmd(ros_robo15::Gamepad_cmd p_cmd);
//unsigned char makeMovCmd(Gpads_cmd p_cmd);
unsigned char makeMovCmd(ros_robo15::Gamepad_cmd p_cmd);
