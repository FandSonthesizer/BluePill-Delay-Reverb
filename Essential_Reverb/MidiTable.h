
typedef struct {
  float freq;
  uint16_t octave;
  int note;
  int error;
} tuner_note;


//  1
const float PROGMEM midiFreq[132] = {
//C           C'            D             D'            E            F             F'             G            G'            A            A'            B
8.176,      8.662,        9.177,       9.723,        10.301,     10.913,        11.562,        12.25,       12.978,       13.75,     14.568,        15.434,     
16.352,     17.324,       18.354,      19.445,       20.602,     21.827,        23.125,        24.5,        25.957,       27.5,      29.135,        30.868,     
32.703,     34.648,       36.708,      38.891,       41.203,     43.654,        46.249,        48.999,      51.913,       55.0,      58.27,         61.735,     
65.406,     69.296,       73.416,      77.782,       82.407,     87.307,        92.499,        97.999,      103.826,      110.0,     116.541,       123.471,     
130.813,    138.591,      146.832,     155.563,      164.814,    174.614,       184.997,       195.998,     207.652,      220.0,     233.082,       246.942,     
261.626,    277.183,      293.665,     311.127,      329.628,    349.228,       369.994,       391.995,     415.305,      440.0,     466.164,       493.883,     
523.251,    554.365,      587.33,      622.254,      659.255,    698.456,       739.989,      783.991,      830.609,      880.0,     932.328,       987.767,     
1046.502,   1108.731,     1174.659,    1244.508,     1318.51,    1396.913,      1479.978,     1567.982,     1661.219,     1760.0,    1864.655,      1975.533,     
2093.005,   2217.461,     2349.318,    2489.016,     2637.02,    2793.826,      2959.955,     3135.964,     3322.438,     3520.0,    3729.31,       3951.066,     
4186.009,   4434.922,     4698.636,    4978.032,     5274.041,   5587.652,      5919.911,     6271.927,     6644.875,     7040.0,    7458.62,       7902.133,     
8372.018,   8869.844,     9397.273,    9956.064,     10548.082,  11175.304,     11839.822,    12543.854,    13289.75,     14080.0,   14917.241,     15804.266    
};
const String notes[12] = {
  "C",    "C#",   "D",    "D#",   "E",     "F",     "F#",    "G",     "G#",    "A",     "A#",    "B"
};

float centerOctave[10];

float getFreq(uint16_t note) {
  return pgm_read_float( &midiFreq[note] );
}

void initMTable() {
  int idx = 0;
  //Serial.println("Init Table");
  for (int n = 1; n < 10; n++) {
    int id = n * 12;
    centerOctave[idx] = getFreq(id-1) + (getFreq(id) - getFreq(id-1)) / 2;
    idx += 1;
  }
}
/**
 * Input is the measured frequency
 * Out : octave, note and error
 * Note: to speed up the comparison we first find the ocatve:
 */
tuner_note getTuneResult(float freq) {
  //Serial.println("getTuneResult");
  tuner_note res;
  res.freq = freq;
  res.note = 0;
  res.octave = 0;
  res.error = 0;
  for (int n = 8; n >= 0; n--) {
    if (freq >= centerOctave[n]) {
      res.octave = n+1;
      break;
    }
  }
  res.note = -1; // invalid
  int idx = 12 * res.octave; // index in midi table, start of the octave (#c)
  int lBorder , rBorder;
  float f, width; //
 
  for (int n = 11; n >= 0; n--) {
    f = getFreq(idx + n);
    int lIndex = idx + n - 1;
    int rIndex = idx + n + 1;
    if (lIndex < 0)
      lIndex = 0;
    if (rIndex > 131 )
       rIndex = 131;
    // calculate the band:
    float leftF = getFreq(lIndex);
    float rightF = getFreq(rIndex);
    float diff = f - leftF;
    lBorder = leftF + diff / 2.0; // center between 2 Notes
    diff = rightF - f;
    rBorder = f + diff / 2.0; // center beween 2 Notes
    
    if (freq >= lBorder && freq < rBorder) {
      width = rBorder - lBorder;
      res.note = n;
      break;
    }
  } 
 
  if (res.note >= 0 && width > 0) {
    float diff =  freq - (float)f;
    res.error = (int) (diff * 100.0 / (float)width +0.5); // error in percent
  }
  else {
    res.note = 0;
    res.error = 0;
    res.octave = 0;
  }
  return res;
}
