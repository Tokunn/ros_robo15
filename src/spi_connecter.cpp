#include "ros/ros.h"
#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

#include "libspi.h"

#define PACKET_SIZE_BYTE 1
#define BUS 0

#define DEFAULT_CS 0

#define RPI

class SpiRosTransfer
{
    public:
        SpiRosTransfer(int cs) {
            this->pub = this->n.advertise<ros_robo15::Spi_cmd>("recive_data", 1000);
            this->sub = this->n.subscribe("send_data", 1000, &SpiRosTransfer::spi_transfer, this);

#ifdef RPI
            this->spi = new SPI(BUS, cs, !SPI_CPOL | SPI_CPHA);
#endif
        }

        ~SpiRosTransfer() {
#ifdef RPI
            delete(spi);
#endif
        }

    private:
        ros::NodeHandle n;

        ros::Publisher pub;
        ros::Subscriber sub;

        void spi_transfer(const ros_robo15::Spi_cmd::ConstPtr& txbuf_msg) {
            ros_robo15::Spi_cmd rxbuf_msg;
#ifdef RPI
            // send txbuf_msg
            uint8_t *rxbuf = this->spi->transfer(PACKET_SIZE_BYTE, (uint8_t*)&txbuf_msg->spi_cmd);
            rxbuf_msg.spi_cmd = *rxbuf;
            delete(rxbuf);
            // recive rxbuf_msg
#endif
            ROS_DEBUG("transfer data: Send[0x%x] Recive[0x%x]",
                    txbuf_msg->spi_cmd, rxbuf_msg.spi_cmd);
            this->pub.publish(rxbuf_msg);
            ros::spinOnce();
        }

        SPI *spi;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spi_connecter");

    int cs = DEFAULT_CS;
    if (argc > 1) {
        cs = atoi(argv[1]);
        ROS_INFO("SPI_CS : %d", cs);
    }
    else {
        ROS_WARN("Not given arguments");
    }

    SpiRosTransfer spirostransfer(cs);

    ros::spin();

    return EXIT_SUCCESS;
}
