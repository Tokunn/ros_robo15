#include "ros/ros.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

#include "libspi.h"
#include "wiringPiSPI.h"

#define PACKET_SIZE_BYTE 1
#define BUS 0

#define DEFAULT_CS 0

#define RPI

class SpiRosTransfer
{
    public:
        SpiRosTransfer(int p_cs) {
            this->pub = this->n.advertise<ros_robo15::Spi_cmd>("recive_data", 1000);
            this->sub = this->n.subscribe("send_data", 1000, &SpiRosTransfer::spi_transfer, this);

            this->cs = p_cs;
            this->fd = wiringPiSPISetup(this->cs, 500000);
            if (fd < 0) { return; }
        }


    private:
        ros::NodeHandle n;

        ros::Publisher pub;
        ros::Subscriber sub;

        void spi_transfer(const ros_robo15::Spi_cmd::ConstPtr& txbuf_msg) {
            ROS_INFO("spi_transfer start");
            uint8_t buf_msg = txbuf_msg->spi_cmd;

            ROS_INFO("wiringPiSPIDataRW start");
            wiringPiSPIDataRW(this->cs, &buf_msg, PACKET_SIZE_BYTE); 
            ROS_INFO("wiringPiSPIDataRW end");

            ros_robo15::Spi_cmd rxbuf_msg;
            rxbuf_msg.spi_cmd = buf_msg;
            ROS_DEBUG("transfer data: Send[0x%x] Recive[0x%x]",
                    txbuf_msg->spi_cmd, rxbuf_msg.spi_cmd);
            this->pub.publish(rxbuf_msg);
            ros::spinOnce();
            ROS_INFO("spi_transfer end");
        }

        int fd;
        int cs;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spi_connecter");

    // Check Chip Select
    int cs = DEFAULT_CS;
    if (argc > 1) {
        cs = atoi(argv[1]);
        ROS_INFO("SPI_CS : %d", cs);
    } else {
        ROS_WARN("Not given arguments");
    }

    SpiRosTransfer spirostransfer(cs);

    ros::spin();

    return EXIT_SUCCESS;
}
