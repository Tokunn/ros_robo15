#include "ros/ros.h"
#include "ros_robo15/Gamepad_cmd.h"

#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "joystick.h"

#define BUTTON_DATA_MAX 12
#define STICK_DATA_MAX 6
#define MAX_STICK 1 
#define BUTTON_X 0
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_Y 3
#define BUTTON_LB 4
#define BUTTON_RB 5
#define BUTTON_LT 6
#define BUTTON_RT 7
#define BUTTON_BACK 8
#define BUTTON_START 9
#define BUTTON_STICKLEFT 10
#define BUTTON_STICKRIGHT 11
#define LEFT_STICK_X 0
#define LEFT_STICK_Y 1
#define RIGHT_STICK_X 2
#define RIGHT_STICK_Y 3
#define CROSS_STICK_X 4
#define CROSS_STICK_Y 5


/*----- main() -----*/
int main(int argc, char **argv) {
    ros::init(argc, argv, "gamepad_cpp");

    int fd = open("/dev/input/js0", O_RDONLY);
    unsigned char button_data[BUTTON_DATA_MAX];
    float stick_data[STICK_DATA_MAX];

    ros::NodeHandle n;

    ros::Publisher gamepad_cpp_pub = n.advertise<ros_robo15::Gamepad_cmd>("gamepad_cmd", 1000);

    ros::Rate loop_rate(50);
    
    while (ros::ok()) {

        struct js_event event;
        if (read( fd, &event, sizeof(struct js_event) ) >= sizeof(struct js_event) ) {
            switch (event.type & 0x7f) {
                case JS_EVENT_BUTTON:
                    if (event.number < BUTTON_DATA_MAX) {
                        button_data[event.number] = event.value;
                    }
                    break;
                case JS_EVENT_AXIS:
                    if (event.number < STICK_DATA_MAX) {
                        stick_data[event.number] = event.value;
                    }
                    break;
            }
        }
        
        ros_robo15::Gamepad_cmd gamepad_cmd;

        gamepad_cmd.left_axis_x = 2;//stick_data[LEFT_STICK_X];
        gamepad_cmd.left_axis_y = 2;//stick_data[LEFT_STICK_Y];
        gamepad_cmd.right_axis_x = 2;//stick_data[RIGHT_STICK_X];
        gamepad_cmd.right_axis_y = 2;//stick_data[RIGHT_STICK_Y];

        gamepad_cpp_pub.publish(gamepad_cmd);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return EXIT_SUCCESS;
}
