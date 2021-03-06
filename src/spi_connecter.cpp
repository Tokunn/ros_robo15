#include "ros/ros.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

#include "wiringspi.h"

#define PACKET_SIZE_BYTE 1
#define BUS 0
#define DEFAULT_CS 1
#define SPEED 10000000
#define MODE 3

class SpiRosTransfer
{
    public:
        SpiRosTransfer(int tmp_cs) {
            this->pub = this->n.advertise<ros_robo15::Spi_cmd>("recive_data", 10);
            this->sub = this->n.subscribe("send_data", 1000,
                    &SpiRosTransfer::spi_transfer, this);
            this->cs = tmp_cs;
            wiringPiSPISetupMode(this->cs, SPEED, MODE);
        }

    private:
        ros::NodeHandle n;
        ros::Publisher pub;
        ros::Subscriber sub;

        int cs;

        void spi_transfer(const ros_robo15::Spi_cmd::ConstPtr& txbuf_msg) {
            ros_robo15::Spi_cmd rxbuf_msg;

            wiringPiSPIDataRW(this->cs, &txbuf_msg->spi_cmd,
                    &rxbuf_msg.spi_cmd, PACKET_SIZE_BYTE);

            ROS_DEBUG("transfer data: Send[0x%x] Recive[0x%x]",
                    txbuf_msg->spi_cmd, rxbuf_msg.spi_cmd);

            this->pub.publish(rxbuf_msg);
            ros::spinOnce();
        }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spi_connecter");

    // Check Chip Select
    int cs = DEFAULT_CS;
    if (argc > 1) {
        cs = atoi(argv[1]);
        ROS_INFO("SPI_CS : %d", cs);
    }
    SpiRosTransfer spirostransfer(cs);
    ros::spin();

    return EXIT_SUCCESS;
}
