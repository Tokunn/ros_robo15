#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

const static char       *spiDev0  = "/dev/spidev0.0" ;
const static char       *spiDev1  = "/dev/spidev0.1" ;
const static uint8_t     spiBPW   = 8 ;
const static uint16_t    spiDelay = 0 ;

static uint32_t    spiSpeeds [2] ;
static int         spiFds [2] ;

int wiringPiSPIDataRW (int channel, const unsigned char *txbuf, unsigned char *rxbuf, int len)
{
  struct spi_ioc_transfer spi ;

  channel &= 1 ;

  memset (&spi, 0, sizeof (spi)) ;

  spi.tx_buf        = (unsigned long)txbuf ;
  spi.rx_buf        = (unsigned long)rxbuf ;
  spi.len           = len ;
  spi.delay_usecs   = spiDelay ;
  spi.speed_hz      = spiSpeeds [channel] ;
  spi.bits_per_word = spiBPW ;

  return ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi) ;
}

int wiringPiSPISetupMode (int channel, int speed, int mode)
{
  int fd ;

  mode    &= 3 ;	// Mode is 0, 1, 2 or 3
  channel &= 1 ;	// Channel is 0 or 1

  if ((fd = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR)) < 0)
      return -1;

  spiSpeeds [channel] = speed ;
  spiFds    [channel] = fd ;

  if (ioctl (fd, SPI_IOC_WR_MODE, &mode)            < 0)
      return -1;
  if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0)
      return -1;
  if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0)
      return -1;

  return fd ;
}

int wiringPiSPISetup (int channel, int speed)
{
  return wiringPiSPISetupMode (channel, speed, 0) ;
}
