#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"

void chatterCallback(const std_msgs::Int8::ConstPtr& msg)
{
  ROS_INFO("I heard: [0x%x]", msg->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("rxbuf", 1000, chatterCallback);

  ros::spin();

  return 0;
}
