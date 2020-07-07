#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MidiTable.h"

// If using software SPI (the default case):
#define OLED_MOSI  PC14 // D1
#define OLED_CLK   PB10 // D0
#define OLED_DC    PB1 // DC
#define OLED_CS    PB0 // CS
#define OLED_RESET PB11 // RES

const int width =  SSD1306_LCDWIDTH; // pixel-width of display
const int height = SSD1306_LCDHEIGHT; // pixel height of display
const int LF = 8;     // line feed size

const int BASE = 0;
const int TUNER = 1;
const int PAGEMAX = 2;

const int chDispY = LF;
const int noOnY = LF*2;   // note on-off y pos
const int chDispX = 0;   // midi Channel
const int ntOnX = 42;   // note on x pos
const int ntOffX = 85;   // note off x pos
const int curveOffX = 42;
const int ntW = 42; // width of fields

const int ARROW_WIDTH = 8;
const int DGAP = 3;
int WAVEDISP_WIDTH = width - 2*ARROW_WIDTH - 2 * DGAP;
int xstart = ARROW_WIDTH + DGAP;

uint16_t  page = TUNER;//SCOPE; //BASE;    // this is the ui-page we actually display
uint16_t  opx = 0;
uint16_t  opy = 0;


bool requestToUpdate = true; // if true, execute the  display.display() function
int cx = 0, cy = 0;

 Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
 
void initGraphic() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  //delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}


void displayPage1(tuner_note tn) {
  display.clearDisplay();
  
  int h = 22;
  int off = 5;
  // text display tests
  display.setTextSize(2);
  int y = 2;
  int x = off;
  display.setCursor(x, y);
  display.print("F:"); 
  if (tn.freq > 0)
      display.println(tn.freq);
  else
      display.println("-----");
  off = 15;
  y += h;
  
  // clear old text
  //display.fillRect(x, y, width, h, 0);
  if (tn.freq > 0) {
     x = off+10;
    display.setCursor(x, y);
    display.println(" "+notes[tn.note]+tn.octave); //+ " "+tn.error);
  }
  else {
     x = off;
     display.setCursor(x, y);
     display.println("No Signal");
  }
  if (tn.freq > 0) {
    y += h;
    x = off;
    //display.setCursor(x, y);
    int p = (58 * tn.error) / 50;
   
    x = 63;
    int h1 = 12;
    y += 3;
    display.drawLine(x, y -7, x, y+20, WHITE);
    int c = y + 6;
    int ah = 10;
    if (p > 0) {
      display.fillRect(x, y, p, h1, WHITE);
      display.drawLine(x+p, c - ah, x+p+5, c, WHITE);
      display.drawLine(x+p, c + ah, x+p+5, c, WHITE);
    }
    else if (p != 0) {
      display.fillRect(x+p, y, -p, h1, WHITE);
      display.drawLine(x+p, c - ah, x+p-5, c, WHITE);
      display.drawLine(x+p, c + ah, x+p-5, c, WHITE);
    }
  }
  //display.print("e=");
  //display.println(tn.error);
 
}




