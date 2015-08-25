#include "ros/ros.h"
#include "ros_robo15/Gamepad_cmd.h"

#include <sstream>
#include <stdlib.h>


/*----- main() -----*/
int main(int argc, char **argv) {
    ros::init(argc, argv, "gamepad_cpp");

    ros::NodeHandle n;

    ros::Publisher gamepad_cpp_pub = n.advertise<ros_robo15::Gamepad_cmd>("gamepad_cmd", 1000);

    ros::Rate loop_rate(50);

    while (ros::ok()) {

        ros_robo15::Gamepad_cmd gamepad_cmd;

        gamepad_cpp_pub.publish(gamepad_cmd);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return EXIT_SUCCESS;
}
