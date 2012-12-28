

#ifdef WIBLOCKS
#include "SPI.h"
#include "DAC.h"
#else
#include "Spi2.h"
#endif
#define laserEn 31    // laser enable signal

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
  setCoords(0,0,scaleX,scaleY,OffsetX,OffsetY);    // setCoords(x, y, laserEn);
}

void loop()
{ 
  digitalWrite(laserEn,0);
  return;

  int t_x = 0;
  int t_y = 0;
  for(int m=0; m < 2; m++)
  {
    for(int v=1; v < 4095; v+=2)
    {
      switch (m)
      {
      case 0:
        t_x = 1;
        t_y = v;
        break;
      case 1:
        t_x = 1;
        t_y = 4095-v;
        break;
      case 2:
        t_x = 4094;
        t_y = (4095-v);
        break;
      case 3:
        t_x = (4095-v);
        t_y = 1;
        break;
      default:
        break;
      }
      digitalWrite(laserEn,0);
      setCoords(t_x,t_y,scaleX,scaleY,OffsetX,OffsetY);    // setCoords(x, y, laserEn);
      delayMicroseconds(500);
      digitalWrite(laserEn,1);
      delay(1);
    }
  }
}

void setCoords(int x, int y, int i_scaleX, int i_scaleY, int i_OffsetX, int i_OffsetY)
{
  x = (x*i_scaleX) - i_OffsetX;
  y = (y*i_scaleY) - i_OffsetY;

  if (x > 0 && x < 4095)
  {
#ifdef WIBLOCKS
    dac.set_code(DAC_WRITE_BUFFER, x);
    dac.set_code(DAC_WRITE_B_AND_BUFFER, y);
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
#endif
  }

}

