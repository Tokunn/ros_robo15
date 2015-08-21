#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");  // TODO
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("txbuf", 1000);  // TODO
  ros::Rate loop_rate(10);  // TODO
  int count = 0;
  while (ros::ok())
  {
    std_msgs::Int8 msg;

    msg.data = 17;

    ROS_INFO("0x%x", msg.data);
    chatter_pub.publish(msg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
