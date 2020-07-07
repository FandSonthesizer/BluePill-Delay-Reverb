
#include "Graphic.h"
#include "Voice.h"
#include "PWM.h"
#include "Dac.h" 

uint32_t triggerCount, mil;
uint64_t gTick = 0;
uint64_t startMeasureTime = 0, measureFreqCounter, triggerTime;
uint32_t period = 20000;
int uTick = 0, globalTic;
uint16_t freq = 0, q;
float f2 = 0.0;
uint16_t measureFreqInterval = 1000; //0.1 sec Interval

uint64_t lastSampleTime = 0;
uint16_t sampleInterval = 50; // 50 us 800u

const uint16_t bufferLength = 7000;
uint16_t ebuffer[bufferLength];
uint16_t writePointer = 0;
uint16_t readPointer = 0;
uint16_t readPointer2 = 0;
uint16_t readPointer3 = 0;
uint16_t readPointer4 = 0;
uint16_t fillRate = 0;
boolean doRead = false;
uint16_t edelay = 3500; // 0-6999
int16_t head2Pos = -300;
uint16_t oldV;

const bool align = false; 

int lifeRate = 499;
bool test = false;
const int clockPin = PB4;
bool start = true, life;
boolean echo = false;
   
tuner_note tn;

void setup() {
  pinMode(PC13, OUTPUT); //  Onboard LED
  initDac();
  initPwm();
  initVoices();
  initMTable(); // octave limit table
  initISR();
  initGraphic();
  
  pinMode(clockPin, INPUT_PULLDOWN);
  attachInterrupt(clockPin, TriggerReceived, FALLING); //LOW, FALLING, RISING, CHANGE
  Serial.begin(115200);
}


  
void loop() {
  if (millis() > 500 && start) {
    start = false;
    if (align) {
      //Serial.println("Start Alignment");
      pwmWrite(PWM_OUT, maxPWMAmplitude);
      pwmWrite(PWM_OUT2, maxPWMAmplitude);
    }
    else {
      Serial.println("Signal Analyzer");
    }
    startMeasureTime = 0;
    triggerCount = 0;
    if (echo)
      readPointer = bufferLength - 5000;
    else
      readPointer = bufferLength - 2000;
      
    readPointer2 = bufferLength - 3200;
    readPointer3 = bufferLength - 2300;
    readPointer4 = bufferLength - 3500;
    writePointer = 0;
  }
  else {
   // Fast read of Analog in
   
   // 0-4095
   uint64_t actual = micros();
   uint16_t diff = actual - lastSampleTime;
   if (diff >= sampleInterval ) {
     lastSampleTime = actual;
     uint16_t v = adc_read(ADC2, PA2);
     uint16_t vb = adc_read(ADC2, PA0);

    
     v = (v + vb) >> 1;
    //uint16_t v = glidingAverage(adc_read(ADC2, PA2));
     
     //int diff = 2047 - v;
    /* if (abs(diff) < 100)
        v = 2027;
      */
     // Serial.println(v);
     //ebuffer[writePointer++] = (v * 2 +oldV) / 3;  // write signal
    // v = (v + oldV) / 2;
     ebuffer[writePointer++] = (v + oldV) / 2;  // write signal
     if (writePointer >= bufferLength)
        writePointer = 0;
        
     v = ebuffer[readPointer++];                  // read Signal
     if (readPointer >= bufferLength)
        readPointer = 0;

        
     uint16_t v2 = ebuffer[readPointer2++];
     if (readPointer2 >= bufferLength)
        readPointer2 = 0;

     uint16_t v3 = ebuffer[readPointer3++];
     if (readPointer3 >= bufferLength)
        readPointer3 = 0;
     uint16_t v4 = ebuffer[readPointer4++];
     if (readPointer4 >= bufferLength)
        readPointer4 = 0;
        
     uint16_t out = v;
     if (!echo)
        out = (v >> 2) + (v2 >> 2) + (v3 >> 2) + (v4 >> 2);

     
     sendToDAC(DAC0, out);
     pwmWrite(PWM_OUT, (maxPWMAmplitude * out) >> 12);
     oldV = out;
     
     
     //
     
   }

   
   test = !test;
   //uint16_t v = (Nscale * maxPWMAmplitude) >> 12;
   //pwmWrite(PWM_OUT, v );  //
   
   //-------------------------------------
   
  
   }
}

void initISR() {
  /** 
   *  Setup Timer 2 to 25u (40000 per second)
   */
  Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
  Timer2.setPeriod(isr_cnt);                          // in microseconds (100u = 10kHz)
  Timer2.setCompare(TIMER_CH1, 1);                   
  Timer2.attachInterrupt(TIMER_CH1, handler_Synth);   // in this routine the synth moves through the wave-table
}

/**
 * Here we measure one period of the trigger signal
 */
void TriggerReceived() {
 uint64_t actual = micros();
  period = actual - triggerTime;
  if (period > 0) {
    lfo.step = z40 / period;
    lfo.tableIndex = 0; // Sync
    voc.step = (lfo.step * 5) / 7;
    //voc.tableIndex = 0; // Sync
  }
  triggerTime = actual;
  
}

void handler_Synth(void) {
  gTick++;   // count up all the time at 10khz
  globalTic++;            
  if (globalTic > 39) {
    globalTic = 0;        // 40 tics at 40 khz is one millisec.
    // one millisecond has passed--------------
    mil++;                // increase millisecond tic, used for button debounce etc.
     // Lifesign of interrupt routine, let the onboard LED blink
    uint16_t dif = mil - q;
    if (dif > lifeRate) {  // Lifesign routine 499
      q = mil;
      life = !life;
      digitalWrite(PC13, life); // Lifesign
    }
  }
  /*if (!start && !align ) { //&& period > 0
    // doVoice
       addStep();
       //sendToDAC(DAC0, lfo.vOutput + maxDACAmplitude2); 
       
       addVCStep();
       sendToDAC(DAC1, voc.vOutput + maxDACAmplitude2); 
   }
   */
}

/**
   * Update the display
   */
  void updateDisplay() {
   switch (page) {
    case TUNER: // tuner page, shown on start-up
      if (requestToUpdate) {
       displayPage1(tn);
      }
      break;
   }
   if (requestToUpdate) {
     requestToUpdate = false;
     display.display();
   }
  }

uint32_t mcount, avgsum;
uint16_t CAVERAGE = 4;
  /**
 * Gliding Average value.
 * This method simulates a capacitor to even out the noisyness of the stm32's adc.
 * @param newval the ne value, read from adc
 * @param potCh which channel to read
 */
uint32_t glidingAverage(uint16 newval) {
   uint16 average = 0; 
   if (mcount < CAVERAGE) { // initial loading of the capacitor
      avgsum += newval;
      average = avgsum / mcount;
      mcount++;
   }
   else {
    // now hold and change the charge
      avgsum -= avgsum / CAVERAGE;
      avgsum += newval;
      average = avgsum / CAVERAGE;
   }
   return average;
}

  
