
//#define WIBLOCKS
/*
#ifdef WIBLOCKS
#include "SPI.h"
#include "DAC.h"
#else
#include "Spi2.h"
#endif
*/

#include <math.h>

//------------------------------
// DAC Data Transfer
#define SLAVESELECT 53 // CS
#define DATAOUT 51 // DIN
#define SPICLOCK 52 // SCLK
//-------------------------------

#define laserEn 31    // laser enable signal
#define fanEn 10    // laser enable signal
#define SS_PIN 53 //16    // Control Signal (53)

//------ Controls -------------------------
int OffsetX = 0;
int OffsetY = 0;
int textSpeed = 15;
int windowX = 0;
int minWindow = 600;
int maxWindow = 3800;
int prevX = 0;
int scaleY = 1;
int scaleX = 1;

#ifdef WIBLOCKS
SPI spi(SPI_TIMEOUT, NB1A_MOSI_PIN, NB1A_MISO_PIN, NB1A_SCK_PIN);
DAC_TLV5618 dac(SS_PIN, DAC_NORMAL, DAC_FAST);
#endif

void setup()
{
  Serial.begin(9600);
  pinMode(laserEn, OUTPUT);
  pinMode(fanEn, OUTPUT);

/*
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA);
  //clr=SPSR;
  //clr=SPDR;

  delay(10);
  setCoords(2048,2048,scaleX,scaleY,OffsetX,OffsetY);    // setCoords(x, y, laserEn);
*/
// Setup SPI Interface code BEGIN /////////////////////////////////////////// 

byte clr;
pinMode(DATAOUT, OUTPUT);
pinMode(SPICLOCK,OUTPUT);
pinMode(SLAVESELECT,OUTPUT);

digitalWrite(SLAVESELECT,HIGH); //disable device

//The SPI control register (SPCR) has 8 bits, each of which control a particular SPI setting.

// SPCR
// | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |0000000000000000000
// | SPIE | SPE | DORD | MSTR | CPOL | CPHA | SPR1 | SPR0 |

// SPIE - Enables the SPI interrupt when 1
// SPE - Enables the SPI when 1
// DORD - Sends data least Significant Bit First when 1, most Significant Bit first when 0
// MSTR - Sets the Arduino in master mode when 1, slave mode when 0
// CPOL - Sets the data clock to be idle when high if set to 1, idle when low if set to 0
// CPHA - Samples data on the falling edge of the data clock when 1, rising edge when 0'
// SPR1 and SPR0 - Sets the SPI speed, 00 is fastest (4MHz) 11 is slowest (250KHz)

SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA);
clr=SPSR;
clr=SPDR;
delay(10);
}

/////////////////////////////////////////////////////////////////////
// DAC SPI Interface
char spi_transfer(volatile char data)
{
SPDR = data; // Start the transmission
while (!(SPSR & (1<<SPIF))) // Wait the end of the transmission
{
};
return SPDR; // return the received byte
}

/////////////////////////////////////////////////////////////////////
// Set the voltage on the 12bit DAC
byte SetXVoltage(short Voltage)
{
digitalWrite(SLAVESELECT,LOW);

//2 byte opcode -- for some reason we have to do this twice to make it stick with the TLV5618
spi_transfer(Voltage>>8);
spi_transfer(Voltage);

spi_transfer(Voltage>>8);
spi_transfer(Voltage);

digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
}

byte SetYVoltage(short Voltage)
{
Voltage = Voltage | 32768; // Use DAC A

digitalWrite(SLAVESELECT,LOW);

//2 byte opcode -- for some reason we have to do this twice to make it stick with the TLV5618
spi_transfer(Voltage>>8);
spi_transfer(Voltage);

spi_transfer(Voltage>>8);
spi_transfer(Voltage);

digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
}

void loop()
{ 
  //return;
  int maxv = 4028;
  int inca = 1;
  int del = 8;
  int ldel = 2;
  int repeat = 2;
//  delay(5);
//  digitalWrite(laserEn,1);
  
  digitalWrite(fanEn,1);
  int squareheight = 600; //4094
  int line_gain = 10;

   digitalWrite(laserEn,1);
   
   int minv=400;
   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(minv,i, scaleX,scaleY,OffsetX,OffsetY);  
   }

   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(i,4095, scaleX,scaleY,OffsetX,OffsetY);  
   }

   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(4095,4095-i, scaleX,scaleY,OffsetX,OffsetY);  
   }

   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(4095-i,minv, scaleX,scaleY,OffsetX,OffsetY);  
   }
   
}

void setCoords(int x, int y, int i_scaleX, int i_scaleY, int i_OffsetX, int i_OffsetY)
{
  delay(1);
  SetXVoltage(x);
  SetYVoltage(y);
  /*
  x = (x*2*i_scaleX) - i_OffsetX;
  y = (y*2*i_scaleY) - i_OffsetY;

 // if (x > 0 && x < 4095)
  {
#ifdef WIBLOCKS
    dac.set_code(DAC_WRITE_BUFFER, x);
    dac.set_code(DAC_WRITE_B_AND_BUFFER, y);
    delay(100);
#else  
    digitalWrite(SS_PIN, LOW);
    Spi.transfer((0x5*16)|(x/256));
    Spi.transfer(x & 0xFF);
    digitalWrite(SS_PIN, HIGH);
    digitalWrite(SS_PIN, LOW);
    Spi.transfer((0x5*16)|(x/256));
    Spi.transfer(x & 0xFF);
    digitalWrite(SS_PIN, HIGH);
    digitalWrite(SS_PIN, LOW);
    Spi.transfer((0xC*16)|(y/256));
    Spi.transfer(y & 0xFF);
    digitalWrite(SS_PIN, HIGH);
    digitalWrite(SS_PIN, LOW);
    Spi.transfer((0xC*16)|(y/256));
    Spi.transfer(y & 0xFF);
    digitalWrite(SS_PIN, HIGH);
  //  delay(4);
#endif
  }
  */

}

