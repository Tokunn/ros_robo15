#include "libspi.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define PACKET_SIZE	1
#define BUS 0
#define CS 1

int main() {
    uint8_t packet[PACKET_SIZE] = {0x6};
    SPI *spi = new SPI(BUS, CS, !SPI_CPOL | SPI_CPHA);
    uint8_t *rxbuf = spi->transfer(PACKET_SIZE, packet);

    printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf[0]);

    delete(rxbuf); delete(spi);

    return EXIT_SUCCESS;
}
