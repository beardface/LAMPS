#ifndef __SPI_H__
#define __SPI_H__


///
/// SPI pin assignments for the NB1A and NB2A boards
///

#define SPI_TIMEOUT   10  //milli-seconds

#define NB1A_MOSI_PIN 51  //PB3
#define NB1A_MISO_PIN 50  //PB4
#define NB1A_SCK_PIN  52 //PB5

///
/// Serial Peripheral Interface (SPI) Class
/// 

class SPI {
 private:
  unsigned char _timeout; ///< Number of mS to wait for a transmission to complete.
  unsigned char _mosi_pin;
  unsigned char _miso_pin;
  unsigned char _sck_pin;
 public:
  SPI(unsigned char timeout = SPI_TIMEOUT, 
      unsigned char mosi_pin = NB1A_MOSI_PIN,
      unsigned char miso_pin = NB1A_MISO_PIN,
      unsigned char sck_pin  = NB1A_SCK_PIN);
  void init(unsigned char spcr, unsigned char spsr);
  char write(unsigned char *data, unsigned char num_chars);
  char read(unsigned char *data, unsigned char max_num_chars);
};

extern SPI spi;

#endif
