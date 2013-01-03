// UTouch_QuickDraw (C)2010-2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a quick demo of how to use the library.
//
// This program requires the UTFT library.
//
// It is assumed that the display module is connected to an
// appropriate shield or that you know how to change the pin 
// numbers in the setup.
//

#include "UTFT.h"
#include "UTouch.h"

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next two lines for the Arduino 2009/UNO
//UTFT        myGLCD(ITDB24D,19,18,17,16);   // Remember to change the model parameter to suit your display module!
//UTouch      myTouch(15,10,14,9,8);

// Uncomment the next two lines for the Arduino Mega
UTFT        myGLCD(ITDB32S, 38,39,40,41);   // Remember to change the model parameter to suit your display module!
UTouch      myTouch(6,5,4,3,2);

int cProgress = 0;
int cCount = 0;
int lProgress = 0;
int lCount = 0;

void drawGrid()
{
    myGLCD.setColor(255,255,255);
    myGLCD.fillRect(81,10,242,159);
    //Draw Grid
    int gridSize = 15;
    for(int x=0; x < 10; x++)
    {
      for(int y=0; y < 10; y++)
      {
        myGLCD.setColor(255,0,0);
        myGLCD.fillRect(x*gridSize+90,y*gridSize+10, x*gridSize+92,y*gridSize+12);
      } 
    }
}

void clearScreen()
{
  //Blank Screen
  myGLCD.fillScr(255,255,255);
  
  //Draw Stop Button
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRect (10, 10, 70, 60);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRect (10, 10, 70, 60);
    myGLCD.print("STOP", 20, 27);
    
    //Draw Border
    myGLCD.setColor(0,0,0);
    myGLCD.drawLine(80,10,80,230);

    drawGrid();
    
    myGLCD.setColor(0,0,0);
    myGLCD.drawRect(80,160,311,190);
}

void drawHeightProgress()
{
   lProgress++;
   myGLCD.setColor(0,0,0);
   myGLCD.drawRect(243, 10, 310, 160);
   
   int lWidth = 20;
   int lBorder = 5;
   
   myGLCD.setColor(0,255,0);
   myGLCD.fillRect(244, 159-(lProgress*(lWidth+lBorder)), 310, 159-((lProgress-1)*(lWidth+lBorder)));
}

void drawLayerProgress()
{
   int pWidth = 5;
   int pBorder = 2;
   int pCount = 34;
   if((cCount > (cProgress+1)*10))
   {
     cProgress++;
     if(cProgress < pCount)
     {
        for(int c = 0; c < cProgress; c++)
        {
           myGLCD.setColor(0,255,0);
           myGLCD.fillRect(81+c*(pWidth+pBorder), 161, 80+c*(pWidth+pBorder)+pWidth, 189);
        }
     }
     else
     {
       drawHeightProgress();
       drawGrid();
       cProgress=0;
       cCount = 0;
       myGLCD.setColor(255,255,255);
       myGLCD.fillRect(81, 161, 310, 189);
     }
   }
}

void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(0, 0, 255);
  clearScreen();
}

// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
 /*
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  */
}

void loop()
{
  long x, y;
  
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if ((x!=-1) and (y!=-1))
    {
      if(x >=10 && x <= 70 && y >= 10 && y<=70)
      {
        waitForIt(10, 10, 70, 60);
        drawGrid();
      }
      else if(x > 70)
      {
         myGLCD.setColor(100,0,255);
         myGLCD.fillRect (x-1, y-1,x+2,y+2);
         cCount++;
         drawLayerProgress();
      }
    }
  }
}

