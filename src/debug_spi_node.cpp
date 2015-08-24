//#include "ros/ros.h"
//#include "ros_robo15/Spi_cmd.h"

#include <sstream>
#include <stdlib.h>

#include "libspi.h"

#define PACKET_SIZE 1
#define BUS 0

#define CS 0


int main(int argc, char **argv)
{
    //ros::init(argc, argv, "debug_spi_node");

    uint8_t packet[PACKET_SIZE] = {0x6};
    SPI *spi = new SPI(BUS, CS, !SPI_CPOL | SPI_CPHA);
    uint8_t *rxbuf = spi->transfer(PACKET_SIZE, packet);

    printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf[0]);

    delete(rxbuf); delete(spi);

    //ros::spin();

    return EXIT_SUCCESS;

}
