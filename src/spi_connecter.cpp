#include "ros/ros.h"
#include "std_msgs/Int8.h"

#include <sstream>
#include <stdlib.h>

#include "libspi.h"

class SpiRosTransfer
{
    public:
        SpiRosTransfer() {
            pub = n.advertise<std_msgs::Int8>("rxbuf", 1000);
            //SpiRosTransfer spirostransfer_object;
            //sub = n.subscribe("txbuf", 1000, &SpiRosTransfer::spi_transfer, &spirostransfer_object);
            sub = n.subscribe("txbuf", 1000, &SpiRosTransfer::spi_transfer, this);
        }

    private:
        ros::NodeHandle n;

        ros::Publisher pub;
        ros::Subscriber sub;

        void spi_transfer(const std_msgs::Int8::ConstPtr& txbuf_msg) {
            ROS_INFO("Send data: [0x%x]", txbuf_msg->data);
            std_msgs::Int8 rxbuf_msg;
            // TODO send txbuf_msg
            //      recive rxbuf_msg
            rxbuf_msg.data = txbuf_msg->data;
            pub.publish(rxbuf_msg);
            ros::spinOnce();
        }
};

/*void spi_transfer(const std_msgs::Int8::ConstPtr& txbuf_msg)
{
    //ros::NodeHandle n;
    //ros::Publisher rxbuf_pub = n.advertise<std_msgs::Int8>("rxbuf", 1000);
    //std_msgs::Int8 rxbuf_msg;
    //rxbuf_msg.data = txbuf_msg->data;
    //ROS_INFO("Send data: [0x%x]", txbuf_msg->data);
    //rxbuf_pub.publish(rxbuf_msg);
    //ros::spinOnce();
    //ROS_INFO("Recive Data:[0x%x]", rxbuf_msg.data);
}*/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spi_connecter");
    SpiRosTransfer spirostransfer;
    //ros::NodeHandle n;
    //ros::Subscriber txbuf_sub = n.subscribe("txbuf", 1000, spi_transfer);
    ros::spin();

    return EXIT_SUCCESS;
}
