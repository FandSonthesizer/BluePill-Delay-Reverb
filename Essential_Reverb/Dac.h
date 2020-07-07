#include <SPI.h>
#include <Wire.h>

/**
 * Definition for the MCP 4922 Dual Channel 12 bit DAC
 * 48us to write both dac channels twice, hence 12us for one channel write.
 */
#define DAC_CS    PB12
#define DAC_SCK   PB13
#define DAC_MOSI  PB15

#define DAC_FLAGS_A 0b00110000 //Select DAC channel A (MCP 4921 or (MCP 4922)
#define DAC_FLAGS_B 0b10110000 //Select DAC channel B (only on MCP 4922)

SPIClass DAC_SPI(2); // use SPI-2 port


void initDac(void ) {
   pinMode(DAC_CS, OUTPUT);
   digitalWrite(DAC_CS, HIGH);
   DAC_SPI.begin();
}

/**
 * Original method
 */
void sendToDAC(byte channel, int val){
  byte lVal = val;
  byte hVal = (val >> 8);
  digitalWrite(DAC_CS, LOW);
  if(channel == 0){ 
    DAC_SPI.transfer(hVal | DAC_FLAGS_A); //Send data to DAC output 'A' (MCP4921 pin 8 or MCP4922 pin 14)
  }else{
    DAC_SPI.transfer(hVal | DAC_FLAGS_B); //Send data to DAC output 'B' (MCP4922 pin 10)
  }
  DAC_SPI.transfer(lVal);
  digitalWrite(DAC_CS, HIGH);
}


