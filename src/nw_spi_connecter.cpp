#include "ros/ros.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void send_udp(const ros_robo15::Spi_cmd::ConstPtr& txbuf_msg) {
    ROS_DEBUG("nw send 0x%x", txbuf_msg->spi_cmd);
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4000);
    addr.sin_addr.s_addr = inet_addr("localhost");


    sendto(sock, &txbuf_msg->spi_cmd, 1, 0, (struct sockaddr *)&addr, sizeof(addr));

    close(sock);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "nw_spi_connecter");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("send_data", 1000, send_udp);

    ros::spin();

    return EXIT_SUCCESS;
}
