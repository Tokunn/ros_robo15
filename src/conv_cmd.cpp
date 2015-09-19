#include "ros/ros.h"
#include "ros_robo15/Gamepad_cmd.h"
#include "ros_robo15/Spi_cmd.h"

#include "gamepad_cmd.h"

#include <sstream>
#include <stdlib.h>

class TempCenterNode
{
    public:
        TempCenterNode() {
            this->pub = this->n.advertise<ros_robo15::Spi_cmd>("send_data", 1000);
            this->sub = this->n.subscribe("gamepad_cmd", 1000,
                    &TempCenterNode::cmd_temp_transfer, this);
        }
    private:
        ros::NodeHandle n;

        ros::Publisher pub;
        ros::Subscriber sub;

        void cmd_temp_transfer(const ros_robo15::Gamepad_cmd::ConstPtr& p_gamepad_cmd_buf) {
            ros_robo15::Gamepad_cmd gamepad_cmd_buf = *p_gamepad_cmd_buf;
            ros_robo15::Spi_cmd txbuf_msg;
            txbuf_msg.spi_cmd = (uint8_t)makeFirCmd(gamepad_cmd_buf);
            //txbuf_msg.spi_cmd = (uint8_t)gamepad_cmd_buf->button_x; // TODO
            //ROS_DEBUG("publish data: %d", txbuf_msg.spi_cmd);       // TODO
            this->pub.publish(txbuf_msg);
            txbuf_msg.spi_cmd = (uint8_t)makeMovCmd(gamepad_cmd_buf);
            this->pub.publish(txbuf_msg);
            ros::spinOnce();
        }
};


int main(int argc, char **argv) {
    ros::init(argc, argv, "conv_cmd_node");

    TempCenterNode tempcenter_node;

    ros::spin();

    return EXIT_SUCCESS;
}
