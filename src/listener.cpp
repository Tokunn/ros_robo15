#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "ros_robo15/Spi_cmd.h"

void chatterCallback(const ros_robo15::Spi_cmd::ConstPtr& msg)
{
  ROS_INFO("I heard: [0x%x]", msg->spi_cmd);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("recive_data", 1000, chatterCallback);

  ros::spin();

  return 0;
}
