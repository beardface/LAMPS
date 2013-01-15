#include <SPI.h>
#include <math.h>

//------------------------------
// DAC Data Transfer
#define SLAVESELECT 53 // CS
#define DATAOUT 51 // DIN
#define SPICLOCK 52 // SCLK
//-------------------------------

#define laserEn 31    // laser enable signal
#define fanEn 10    // laser enable signal

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

  pinMode(DATAOUT, OUTPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  SPI.begin();
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

//----------------------------------------------------------------------------------------------------------
//----------------------- TLV5618 FUNCTION -----------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
void TLV5618_out(double A, double B){
  byte prev_SPCR = SPCR;                                           // save the previous SPI settings
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA);                             // setup SPI for the DAC
  unsigned int chA = A;
  unsigned int chB = B;
  spi_transfer(2, chB);
  spi_transfer(2, chB);
  spi_transfer(1, chA);
  spi_transfer(1, chA);
  SPCR = prev_SPCR;                                                // restore the previous SPI settings
}

void spi_transfer(int channel, unsigned int data){
  digitalWrite(SLAVESELECT, LOW);
  delayMicroseconds(10);
  if (channel == 1) SPI.transfer((0xC*16)|(data/256));             // output from channel A (1)
  if (channel == 2) SPI.transfer((0x5*16)|(data/256));             // output from channel B (2)
  SPI.transfer(data & 0xFF);
  delayMicroseconds(10);
  digitalWrite(SLAVESELECT, HIGH);
}
//--------------------------------------------------- END FUNCTION -------------------------------------------------------

void loop()
{ 
  return;
  
  int maxv = 4028;
  int inca = 10;
  int del = 8;
  int ldel = 2;
  int repeat = 2;
//  delay(5);
  digitalWrite(fanEn,1);
  
  int squareheight = 600; //4094
  int line_gain = 10;

   digitalWrite(laserEn,1);
   
   int minv=600;
   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(minv,i);  
   }

   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(i,4095);  
   }

   for(int i = 1; i < 4096-minv; i+=inca)
   {
     setCoords(4095,4095-i);  
   }

   for(int i = 1; i < 4096-minv; i+=inca)
   {
     setCoords(4095-i,minv);  
   }
   
   for(int i = minv; i < 4096; i+=inca)
   {
     setCoords(i,i);  
   }
   
   for(int i = 1; i < 4096-minv; i+=inca)
   {
     setCoords(4095-i,4095-i);  
   }
   
}

void setCoords(int x, int y)
{
  delay(5);
  TLV5618_out(x,y);
}
