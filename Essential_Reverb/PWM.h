/**
 * Used for analog out, using PWM
 */
#include "Essential_Reverb.h"

//----------- PWM Pins ---------------
#define PWM_OUT       PA8    // PA8 PWM output pin, Audio out
#define PWM_OUT2      PA11    // PWM output pin, ADSR out

const uint16_t pwm_cnt =  20;     // pwm freq @ 50kHz , 10us=max ampl. 720 20us=max ampl. 1440


void initPwm(void) {
  /**
    * Pwm Set for analog out: 50kHz, 0-1420
   */
    HardwareTimer timer1 = HardwareTimer(1);  // using timer 1, can be 2,3,4...
    timer1.setPrescaleFactor(1);              // Pre-scale factor 1-65536
    timer1.setPeriod(pwm_cnt); //0-1420 @ 50kHz    // microseconds uSec 
    pinMode(PWM_OUT, PWM);      // synthesizer analog output
  
  /**
    * Pwm Set for analog out: 50kHz, 0-1420
   */
    HardwareTimer timer3 = HardwareTimer(3);  // using timer 1, can be 2,3,4...
    timer3.setPrescaleFactor(1);              // Pre-scale factor 1-65536
    timer3.setPeriod(pwm_cnt); //0-1420 @ 50kHz    // microseconds uSec 
    pinMode(PWM_OUT2, PWM);   // Filter AD output
}


