#include "SPI.h"

#include <inttypes.h>
#include "Arduino.h"


/// 
/// Constructor for the SPI Class. 
/// 
/// The pin assignments for the SPI port need to be passed to the
/// constructor. The pin numbers need to be Arduino (or Sanguino) pin
/// numbers since initialization is performed using pinMode and
/// digitalWrite commands. The default values are for the wiblocks
/// NB1A board. Constants for the NB2A board (which is Sanguino
/// compatible) are defined in the header file.
///
/// No hardware is initialized by the constructor. A call to
/// Init is required to initialize the pins and setup the
/// control register (SPCR) and the status register (SPSR).
///
/// \param[in] timeout number of milliseconds to wait for the SPI port
/// to complete transmission.  the default value is 10mS.
///
/// \param[in] mosi_pin the pin number of the MOSI pin. 
/// \param[in] miso_pin the pin number of the MISO pin.
/// \param[in] sck_pin  the pin number of the SCK pin.
///
/// \todo Add circular buffers for interrupt driven IO
///

SPI::SPI(unsigned char timeout, 
	 unsigned char mosi_pin, 
	 unsigned char miso_pin, 
	 unsigned char sck_pin) {
  _timeout = timeout;
  _mosi_pin = mosi_pin;
  _miso_pin = miso_pin;
  _sck_pin = sck_pin;
};

///
/// Initialize the SPI control register and SPI status
/// register.
///
/// \param[in] spcr SPI control register
/// \param[in] spsr SPI status register
///

void SPI::init(unsigned char spcr, unsigned char spsr) {
  digitalWrite(_mosi_pin, LOW);
  digitalWrite(_sck_pin, LOW);
  pinMode(_mosi_pin, OUTPUT);
  pinMode(_sck_pin,  OUTPUT);
  pinMode(_miso_pin, INPUT);
  SPCR = spcr;
  SPSR = spsr;
};


///
/// Write characters to the SPI port.
/// 
/// \param[in] *data pointer to an array of characters to be transmitted
/// \param[in] num_chars number of characters to be transmitted.
/// 

char SPI::write(unsigned char *data, unsigned char num_chars) {
  unsigned char *p;
  unsigned char i = 0;
  unsigned char count = 0;
  p = data;
  for ( i = 0; i < num_chars; i++) {
    SPDR = *p++;   
    count = 0;
    while (1) {
      if (SPSR & (1<<SPIF)) break; // transmission complete
      delay(1);
      //      if (++count == _timeout) return(-1);
      if (++count == 10) return(-1);
    }
  }
  return(0);
};

///
/// Read characters from the SPI port 
///
/// \param[in] *data pointer to an array of characters that will receive 
///            the characters that are read.
/// \param[in] max_num_chars number of characters to read.
///
/// \todo Write it ;)
///
char SPI::read(unsigned char *data, unsigned char max_num_chars) {
  return(-1);
};

