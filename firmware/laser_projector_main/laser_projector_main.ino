
//#define WIBLOCKS

#ifdef WIBLOCKS
#include "SPI.h"
#include "DAC.h"
#else
#include "Spi2.h"
#endif
#define laserEn 31    // laser enable signal

#include <math.h>

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

  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA);
  //clr=SPSR;
  //clr=SPDR;

  delay(10);
  setCoords(2048,2048,scaleX,scaleY,OffsetX,OffsetY);    // setCoords(x, y, laserEn);
}

void circleSimple(int radius)
{
    int x, y, r2;
    
    r2 = radius * radius;
    for (x = -radius; x <= radius; x++) {
        y = (int) (sqrt(r2 - x*x) + 0.5);
        setCoords(x+2000,y+2000,1,1,0,0);
    }
    
    for (x = -radius; x <= radius; x++) {
        y = (int) (sqrt(r2 - x*x) + 0.5);
        setCoords(x+2000,2000-y,1,1,0,0);
    }
}

void loop()
{ 
  int maxv = 4028;
  int inca = 10;
  int del = 0;
  int repeat = 2;
  digitalWrite(laserEn,1);
//  delay(5);
//  digitalWrite(laserEn,1);

  int line_gain = 1000;
  
  //This draws a centered point... how to move it though?
   // Centered b/c it fluxates the dot fast enough near this point.
    for(int x = 0; x < maxv; x+=line_gain)
    {
        setCoords(x,x,1,1,0,0);
    }
    for(int x = maxv; x > 0; x-=line_gain)
    {
        setCoords(maxv-x,maxv-(x),1,1,0,0);
    }
}

void setCoords(int x, int y, int i_scaleX, int i_scaleY, int i_OffsetX, int i_OffsetY)
{
  x = (x*2*i_scaleX) - i_OffsetX;
  y = (y*2*i_scaleY) - i_OffsetY;

  if (x > 0 && x < 4095)
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

}

