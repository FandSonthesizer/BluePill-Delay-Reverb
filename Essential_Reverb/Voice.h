/**
 * Describes the voices
 */

#include "Saw2048Int.h" // 
#include "Log.h" // 
#include "Essential_Reverb.h"


const int TRI = 0;
const int SAW = 1;
const int RMP = 2;
const int SQR = 3;
const int SIN = 4;
const int WMAX = 5; // number of waveforms

const uint32_t ISR_RATE = 40000;

const uint32_t z40 = 104857600;
const uint32_t z20 = 209715200;
const uint32_t z10 = 419430400;

const int MAXVOICE = 1;
const uint16_t maxPWMAmplitude = 1440; // 1440, 960

uint16_t maxPWMAmplitude2 = maxPWMAmplitude / 2;
const uint16_t maxDACAmplitude = 4095;
uint16_t maxDACAmplitude2 = maxDACAmplitude / 2;
const uint16_t tableAmplitude = 2047;


/**
 * Note: the voice-index is the same as the adsr index! (a slot)
 */
typedef struct {
  uint32_t step;
  uint32_t gstep; // glide step
  uint32_t tableIndex;
  int16_t oldOutput;
  int16_t vOutput;
  uint16_t waveForm;              // which wavetable to play (saw, sin etc.)
  uint16_t clockCnt;
  uint16_t clockDividerIndex;          // how many clock pulses to count for one period
  uint16_t volume;                // volume of this lfo
  int16_t sample;                // a sample value
  int16_t glide;                 // amount to glide to the next sample value
  int16_t gstart;                // where to start to glide
  
 } Voice_type;

// Interrupt setup:
const uint16_t isr_cnt =  25;     // interrupt rate 100us= 10khz; 50us = 20khz; 25us = 40KHz
//const uint32_t ISR_RATE = 10000;  // interrupt rate 10000Hz = 10 pulses per ms = 100us per isr
const uint16_t rateMultiplier = 100; //100us per isr
const int DAC0 = 0;
const int DAC1 = 1;

const int LFOPrecision = 11;      // multiply index counter with 2^11 to be able to go below 1 Hz with a good enough precision

/**
 * One entry per simultane playing lfo
 */
Voice_type lfo; //
Voice_type voc; //
 
uint32_t tableLength = SawLengthInt;  // length of the 16bit high res int wavetable
uint32_t tableLength2 = tableLength / 2;
uint32_t lfoTableIndexMax = (tableLength << LFOPrecision) - 1; ;  // here the table overflows
uint32_t lfoTableIndexMax2 = lfoTableIndexMax >> 1;               // half of the table, used for the clock led

// global vars 
bool state = false;

/**
 * Method declaration
 */
void getWaveAmp(uint16_t);


void initVoices() {
  /** 
   *  Setup Timer 2 to 25u (40000 per second)
   */
  Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
  Timer2.setPeriod(isr_cnt);                          // in microseconds (25u)
  Timer2.setCompare(TIMER_CH1, 1);                   
  Timer2.attachInterrupt(TIMER_CH1, handler_Synth);   // in this routine the synth moves through the wave-table
  
  lfo.step = 0;
  lfo.waveForm = SAW;
  lfo.volume = 4095; 
  voc.step = 0;
  voc.waveForm = RMP;
  voc.volume = 4095; 
  
}

/**
 * Select the waveform of a voice
 */
void selectWaveForm(int w) {
  lfo.waveForm = w;
}


/**
 * 
 * @param p one period in us 1/ 1000000 sec
 */
void setFreq(uint16_t p) {
   lfo.step = z40 / p;
   
}


void addStep() {
  //lfo[n].oldOutput = lfo[n].vOutput; // previous value
  //Serial.print("old=");
  //Serial.print(lfo[n].oldOutput);

  uint16_t indexInTable = 0;

  lfo.tableIndex += lfo.step; //
  indexInTable = lfo.tableIndex >> LFOPrecision; //remember: the tableIndex was multiplied by 2048, so divide here
  indexInTable = indexInTable & 0x7ff; // & 2048 makes sure, that the table index is always inside the table!
  //Serial.print("indexInTable=");
  //Serial.println(indexInTable);
  int16_t c = 0;
  // High Res table (0-4095 as amplitude)
  switch(lfo.waveForm) {
    case SAW:
      c = getSawInt(indexInTable);
    break;
    case RMP:
      c = getSawInt(indexInTable);  
      c = c * -1;
    break;
    case SQR:
      if ( indexInTable < tableLength2) {
        c = maxDACAmplitude2; 
      }
      else {
        c = -maxDACAmplitude2; 
      }
      break;
    }
  /*Serial.print(" raw out=");
    Serial.print(c);
    Serial.print(" vol=");
    Serial.print(lfo[n].volume);
  */
 
  int32_t z1 = c * lfo.volume; // volume = 0-4095
  lfo.vOutput = z1 >> 12; // : 4096
  // Serial.print(" out=");
  // Serial.print(lfo[n].vOutput);
}


void addVCStep() {
  uint16_t indexInTable = 0;
  voc.tableIndex += voc.step; //
  indexInTable = voc.tableIndex >> LFOPrecision; //remember: the tableIndex was multiplied by 2048, so divide here
  indexInTable = indexInTable & 0x7ff; // & 2048 makes sure, that the table index is always inside the table!
  int16_t c = 0;
  // High Res table (0-4095 as amplitude)
  switch(voc.waveForm) {
    case SAW:
      c = getSawInt(indexInTable);
    break;
    case RMP:
      c = getSawInt(indexInTable);  
      c = c * -1;
    break;
    case SQR:
      if ( indexInTable < tableLength2) {
        c = maxDACAmplitude2; 
      }
      else {
        c = -maxDACAmplitude2; 
      }
      break;
  }
  voc.vOutput = c;
}

 

