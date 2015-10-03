int wiringPiSPIDataRW(int channel, const unsigned char *txbuf,
        unsigned char *rxbuf, int len);
int wiringPiSPISetupMode(int channel, int speed, int mode);
int wiringPiSPISetup(int channel, int speed);
