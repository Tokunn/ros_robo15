#include "ros/ros.h"
#include "std_msgs/Int8.h"

#include <sstream>
#include <stdlib.h>

#include "libspi.h"

#define PACKET_SIZE_BYTE 1
#define BUS 0
#define CS_MOTOR 0
#define CS_SENSOR 1

class SpiRosTransfer
{
    public:
        SpiRosTransfer() {
            this->pub = this->n.advertise<std_msgs::Int8>("rxbuf", 1000);
            this->sub = this->n.subscribe("txbuf", 1000, &SpiRosTransfer::spi_transfer, this);

            this->spi_motor = new SPI(BUS, CS_MOTOR, !SPI_CPOL | SPI_CPHA);
            this->spi_sensor = new SPI(BUS, CS_SENSOR, !SPI_CPOL | SPI_CPHA);
        }

        ~SpiRosTransfer() {
            delete(spi_motor);
            delete(spi_sensor);
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
            this->pub.publish(rxbuf_msg);
            ros::spinOnce();
        }

        SPI *spi_motor;
        SPI *spi_sensor;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spi_connecter");
    SpiRosTransfer spirostransfer;
    ros::spin();

    return EXIT_SUCCESS;
}
