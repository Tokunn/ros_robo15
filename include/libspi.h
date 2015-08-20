#ifndef _LIBSPI_H
#define _LIBSPI_H	1

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#ifndef LOW
	#define LOW	0
#endif

#ifndef HIGH
	#define HIGH	1
#endif

#include <string>
#include <exception>
using namespace std;

class SPIException: public exception {
 public:
	string msg;
	
	explicit SPIException( const string &str ) {
		msg = str;
	}
	
	string getString(void) {
		return msg;
	}
	
	virtual ~SPIException(void) throw() { };
};

class SPI {
 private:
	int bus;
	int ce;
	uint8_t mode;
	
	int fd;
	
	int bits_per_word;
	int cs_change;
	int speed;
	int delay_usecs;
	
 public:
	SPI( int, int, uint8_t );
	
	void setSpeed( int );
	void setCSActive( int );
	void setBits( int);
	void setDelay(int);
	
	uint8_t *transfer( int, uint8_t *);
	
	~SPI(void);
};

#endif
