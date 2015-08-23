#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");  // TODO
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<ros_robo15::Spi_cmd>("send_data", 1000);  // TODO
  ros::Rate loop_rate(10);  // TODO
  int count = 0;
  while (ros::ok())
  {
    ros_robo15::Spi_cmd msg;

    msg.spi_cmd = 17;

    ROS_INFO("0x%x", msg.spi_cmd);
    chatter_pub.publish(msg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
