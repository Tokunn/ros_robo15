#include "ros/ros.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

void send_udp(const ros_robo15::Spi_cmd::ConstPtr& txbuf_msg) {
    ROS_DEBUG("nw send 0x%x", txbuf_msg->spi_cmd);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "nw_spi_connecter");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("send_data", 1000, send_udp);

    ros::spin();

    return EXIT_SUCCESS;
}
