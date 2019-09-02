#include "Adafruit_MPR121.h"
#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#define SDCARD_CS_PIN BUILTIN_SDCARD
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

#ifndef _BVA
#define _BVA(bit) (1 << (bit))
#endif
#ifndef _BVB
#define _BVB(bit) (1 << (bit))
#endif

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw player[] = {
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw()};

AudioMixer4 mixer[] = {AudioMixer4(), AudioMixer4(), AudioMixer4()};

AudioFilterStateVariable filter1;  // xy=934,61
AudioEffectFreeverb freeverb1;     // xy=1097,221
AudioEffectBitcrusher bitcrusher1; // xy=1105,428
AudioOutputI2S i2s2;               // xy=1185,270
AudioControlSGTL5000 sgtl5000_1;   // xy=1176,432
/*
AudioConnection          patchCord1(player[4], 0, mixer[1], 0);
AudioConnection          patchCord2(player[5], 0, mixer[1], 1);
AudioConnection          patchCord3(player[2], 0, mixer[0], 2);
AudioConnection          patchCord4(player[3], 0, mixer[0], 3);
AudioConnection          patchCord5(player[0], 0, mixer[0], 0);
AudioConnection          patchCord6(player[6], 0, mixer[1], 2);
AudioConnection          patchCord7(player[1], 0, mixer[0], 1);
AudioConnection          patchCord8(player[7], 0, mixer[1], 3);
AudioConnection          patchCord9(mixer[1], 0, mixer[2], 1);
AudioConnection          patchCord10(mixer[0], 0, mixer[2], 0);
AudioConnection          patchCord11(mixer[2], 0, filter1, 0);
AudioConnection          patchCord12(mixer[2], 0, filter1, 1);
AudioConnection          patchCord13(mixer[2], freeverb1);
AudioConnection          patchCord14(freeverb1, 0, mixer[2], 2);
AudioConnection          patchCord15(filter1, 0, i2s2, 0);
AudioConnection          patchCord16(filter1, 0, i2s2, 1);
*/

AudioConnection patchCord1(player[4], 0, mixer[1], 0);
AudioConnection patchCord2(player[5], 0, mixer[1], 1);
AudioConnection patchCord3(player[2], 0, mixer[0], 2);
AudioConnection patchCord4(player[3], 0, mixer[0], 3);
AudioConnection patchCord5(player[0], 0, mixer[0], 0);
AudioConnection patchCord6(player[6], 0, mixer[1], 2);
AudioConnection patchCord7(player[1], 0, mixer[0], 1);
AudioConnection patchCord8(player[7], 0, mixer[1], 3);
AudioConnection patchCord9(mixer[1], 0, mixer[2], 1);
AudioConnection patchCord10(mixer[0], 0, mixer[2], 0);
AudioConnection patchCord11(mixer[2], 0, filter1, 0);
AudioConnection patchCord12(mixer[2], 0, filter1, 1);
AudioConnection patchCord13(mixer[2], freeverb1);
AudioConnection patchCord14(mixer[2], bitcrusher1);
AudioConnection patchCord15(freeverb1, 0, mixer[2], 2);
AudioConnection patchCord16(bitcrusher1, 0, mixer[2], 3);
AudioConnection patchCord17(filter1, 0, i2s2, 0);
AudioConnection patchCord18(filter1, 0, i2s2, 1);

// GUItool: end automatically generated code

String sounds[] = {"KICK.RAW",   "SNARE.RAW", "CLAP.RAW", "HIHAT.RAW",
                   "CHIME3.TRW", "KISS.RAW",  "B1.TRW",   "C2.TRW"};
int copy_track[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int copy_all[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int pattern[8][8][16] = {{{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

                         {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

int pattern_bank_index = 0;
int pattern_index = 0;
int current_sound = 0;
int tempo = 100;
int last_tempo = 0;
long bpm = 120;
static uint32_t previousTick; 
 
  
const int MODE_TEMPO = 0;
const int MODE_FILTER = 1;
const int MODE_REVERB_VAL = 2;
const int MODE_REVERB_MIX = 3;
const int MODE_BITCRUSH_VAL = 4;
const int MODE_BITCRUSH_MIX = 5;
const int MODE_VOLUME = 6;
const int MODE_COPY_ALL = 10;
const int MODE_COPY_TRACK = 11;
const int MODE_PASTE = 12;
const int MODE_CLEAR_ALL_BANKS = 13;
const int MODE_CLEAR_TRACK = 14;
const int MODE_CLEAR_ALL = 15;

const int COPY_MODE_NONE = 0;
const int COPY_MODE_TRACK = 1;
const int COPY_MODE_ALL = 2;
const int MAX_SOUND_BANKS = 9;

int mode = 0;
int copy_mode = COPY_MODE_NONE;
int freq = 8000;
float rev_mix = 0.0;
float rev_val = 0.0;
float bit_mix = 0.0;
int bit_val = 16;
static uint32_t next;
const int channel = 1;
bool internal_clock = true;
// read pot
const int numReadings = 5;
int readings[numReadings]; // the readings from the analog input
int readIndex = 0;         // the index of the current reading
int total = 0;             // the running total
int average = 0;           // the average
int POT_PIN = A6;
int sound_bank = 1;

// Flash file
const int FlashChipSelect = 6; // digital pin for flash chip CS pin
const int SDchipSelect = 10;   // Audio Shield has SD card CS on pin 10
SerialFlashFile file;
const unsigned long testIncrement = 4096;

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;
uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;

const int buttonFill = 2;
const int buttonPlay = 3;
const int buttonBankUp = 5;
const int buttonBankDown = 4;

bool isplaying = true;
bool isfunction = false;

int latchPin = 16;
int clockPin = 17;
int dataPin = 8;

// holders for infromation you're going to pass to shifting function
byte dataRED;
byte dataGREEN;
byte counter=0;
byte counter2=0;
Bounce playbutton = Bounce(buttonPlay, 30);     // 10 ms debounce
Bounce fillbutton = Bounce(buttonFill, 30);     // 10 ms debounce
Bounce upbutton = Bounce(buttonBankUp, 30);     // 10 ms debounce
Bounce downbutton = Bounce(buttonBankDown, 30); // 10 ms debounce

char *string2char(String str);
void PlaySound(int i);
float eraseBytesPerSecond(const unsigned char *id);
void error(const char *message);
void erase_flash();
void flash_memeory();
bool compareFiles(File &file, SerialFlashFile &ffile);
void shiftOut(int myDataPin, int myClockPin, byte myDataOut);
void blinkAll_2Bytes(int n, int d);
int ReadPot();
void displaypattern();
void Play_Pattern();

void myStart(){
  isplaying=true;
  Serial.println("start"); 
  pattern_index=0;
  counter=0;
  internal_clock=false;
  
}
void myStop(){
  Serial.println("stop"); 
  isplaying=false;
  counter=0;
   internal_clock=false;
}
void myContinue(){
  Serial.println("continue"); 
  isplaying=true;
   internal_clock=false;
   
}

void myClock(){
  //Serial.println("real"); 
  if(internal_clock==false && counter ==0 && isplaying==true){
      Play_Pattern();
   }
  counter++; 
  if(counter == 6) { 
    counter = 0; 
    
  }
  //internal_clock=false;
 /* uint32_t currentTick = micros(); 
  uint32_t tickTime = (currentTick - previousTick); 
  uint32_t tickBeat = 60000000 / (tickTime * 24); 
  previousTick = currentTick; 
  
  
  Serial.print("-----------\n"); 
  
  Serial.print("tickTime: "); 
  Serial.print(tickTime ); 
  Serial.print("\n"); 
  
  Serial.print("tickBeat: "); 
  Serial.print(tickBeat ); 
  Serial.print("\n"); */
}
void myRealTimeSystem(byte realtimebyte) { 
  Serial.println("real"); 
  if(internal_clock==false && counter ==0){
      Play_Pattern();
   }
  counter++; 
  if(counter == 24) { 
    counter = 0; 
    
  }
}
void mySongPosition(uint16_t beats){
  if(beats==0){
    pattern_index=0;
  }else{
   uint16_t t=beats/16;
    uint16_t pos=beats-(t*16);
    pattern_index=pos;
   Serial.print("Song pos"); 
  Serial.println(pos); 
  }
  counter = 0; 
  
  //pattern_index=beats;
}
void setup() {

  // Serial.begin(9600);
  Serial.begin(9600);
  delay(1000);

  pinMode(latchPin, OUTPUT);

  // wait up to 10 seconds for Arduino Serial Monitor
  unsigned long startMillis = millis();
  while (!Serial && (millis() - startMillis < 10000))
    ;
  delay(100);

  Serial.println("Adafruit MPR121 Capacitive Touch sensor A test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!capA.begin(0x5A)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1)
      ;
  }
  Serial.println("MPR121 A found!");

  // Default address is 0x5B, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5B and if SCL then 0x5D
  if (!capB.begin(0x5B)) {
    Serial.println("MPR121 B not found, check wiring?");
    while (1)
      ;
  }

  Serial.println("MPR121 B found!");

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  SPI.setSCK(14); // Audio shield has SCK on pin 14
  SPI.setMISO(12);
  SPI.setMOSI(7); // Audio shield has MOSI on pin 7

  if (!SerialFlash.begin(FlashChipSelect)) {
    Serial.println("Cannot find chip");
    while (1)
      ;
  }

  //*****************
  // Setup the buttons
  //*****************
  pinMode(buttonPlay, INPUT_PULLUP);
  pinMode(buttonFill, INPUT_PULLUP);
  pinMode(buttonBankUp, INPUT_PULLUP);
  pinMode(buttonBankDown, INPUT_PULLUP);

  int flash = digitalRead(buttonPlay);
  if (flash == LOW) {
    displaypattern();
    Serial.println("Flashing Memory");
    erase_flash();
    delay(1000);
    flash_memeory();
    Serial.println("Finished Flashing Memory!!");
  }
  //setup the midi
  usbMIDI.setHandleStart(myStart);
  usbMIDI.setHandleContinue(myContinue);
  usbMIDI.setHandleStop(myStop);
  usbMIDI.setHandleClock(myClock);

  //usbMIDI.setHandleActiveSensing(myActiveSensing);
  //usbMIDI.setHandleSystemReset(mySystemReset);
  usbMIDI.setHandleRealTimeSystem(myRealTimeSystem);
  usbMIDI.setHandleSongPosition(mySongPosition);
  //*****************
  // Setup the volume
  //*****************
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  const float vol = 0.35;

  for (int i = 0; i < 4; i++) {
    mixer[0].gain(i, vol);
    mixer[1].gain(i, vol);
    mixer[2].gain(i, vol);
  }

  filter1.frequency(freq);

  mixer[2].gain(2, rev_mix);
  freeverb1.roomsize(rev_val);

  mixer[2].gain(3, bit_mix);
  bitcrusher1.bits(bit_val);

  // delay(1000);/
  blinkAll_2Bytes(2, 500);
}

void loop() {

  playbutton.update();
  fillbutton.update();
  upbutton.update();
  downbutton.update(); //
                       // isfunction=false;

  if (playbutton.risingEdge()) {
    Serial.println("Play 1 pressed");
    isplaying = !isplaying;
     internal_clock=true;
    if (isplaying == true) {
      pattern_index = 0;
      Serial.println("Playing");
      usbMIDI.sendRealTime(usbMIDI.Start);
      
    }else{
      usbMIDI.sendRealTime(usbMIDI.Stop);
    }
  }

  if (fillbutton.fallingEdge()) {
    isfunction = true;
    Serial.println("fill falling 1 pressed");
  }
  if (fillbutton.risingEdge()) {
    isfunction = false;
    Serial.println("fill 1 pressed");
    Serial.println(isfunction);
  }

  if (upbutton.fallingEdge()) {
    Serial.println("upbutton 1 pressed");
    sound_bank = sound_bank + 1;
    if (sound_bank > 8) {
      sound_bank = MAX_SOUND_BANKS;
    }
  }
  if (downbutton.fallingEdge()) {
    Serial.println("downbutton 1 pressed");
    sound_bank = sound_bank - 1;
    if (sound_bank < 1) {
      sound_bank = 1;
    }
  }

  int tempA = ReadPot();
  
  // Serial.println(tempA);
  if (mode == MODE_TEMPO) { // tempo
    if (abs(tempA - last_tempo) > 3) {
      bpm = map(tempA, 0, 1023, 1000, 1);
      tempo =(bpm/24);
      //Serial.println(tempo);
      last_tempo = tempA;
    }
  } else if (mode == MODE_FILTER) { // filter
    if (abs(tempA - last_tempo) > 3) {
      freq = map(tempA, 0, 1023, 0, 8000);
      filter1.frequency(freq);
      last_tempo = tempA;
    }
  } else if (mode == MODE_REVERB_MIX) { // filter
    if (abs(tempA - last_tempo) > 3) {
      int rev = map(tempA, 0, 1023, 0, 25);
      float revmix = float(rev) / 100;
      Serial.println(revmix);
      mixer[2].gain(2, revmix);
      last_tempo = tempA;
    }
  } else if (mode == MODE_REVERB_VAL) { // filter
    if (abs(tempA - last_tempo) > 3) {
      int rev = map(tempA, 0, 1023, 0, 100);
      float revmix = float(rev) / 100;
      Serial.println(revmix);
      freeverb1.roomsize(revmix);
      last_tempo = tempA;
    }
  } else if (mode == MODE_BITCRUSH_MIX) { // filter
    if (abs(tempA - last_tempo) > 3) {
      int rev = map(tempA, 0, 1023, 0, 50);
      float revmix = float(rev) / 100;
      Serial.println(revmix);
      mixer[2].gain(3, revmix);
      last_tempo = tempA;
    }
  } else if (mode == MODE_VOLUME) { // filter
    if (abs(tempA - last_tempo) > 3) {
      int vol1 = map(tempA, 0, 1023, 0, 100);
      float vol = float(vol1) / 100;
      Serial.println(vol);
      sgtl5000_1.volume(vol);
      last_tempo = tempA;
    }
  } else if (mode == MODE_BITCRUSH_VAL) { // filter
    if (abs(tempA - last_tempo) > 3) {
      int rev1 = map(tempA, 0, 1023, 4, 16);
      int rev2 = map(tempA, 0, 1023, 14100, 44100);
      // float revmix = float(rev) / 100;
      Serial.println(rev1);
      bitcrusher1.bits(rev1);
      bitcrusher1.sampleRate(rev2);
      last_tempo = tempA;
    }
  } else if (mode == MODE_CLEAR_TRACK) { // clear
    for (int i = 0; i < 16; i++) {
      pattern[pattern_bank_index][current_sound][i] = 0;
    }
    mode = MODE_FILTER;
    isfunction = false;
  } else if (mode == MODE_CLEAR_ALL) { // clear
    for (int j = 0; j < 8; j++) {
      for (int i = 0; i < 16; i++) {
        pattern[pattern_bank_index][j][i] = 0;
      }
    }
    mode = MODE_FILTER;
    isfunction = false;
  } else if (mode == MODE_CLEAR_ALL_BANKS) { // clear
    for (int x = 0; x < 8; x++) {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 16; i++) {
          pattern[x][j][i] = 0;
        }
      }
    }
    mode = MODE_FILTER;
    isfunction = false;
  } else if (mode == MODE_COPY_TRACK) { // copy track
    if (pattern_bank_index < 8) {
      for (int i = 0; i < 16; i++) {
        copy_track[i] = pattern[pattern_bank_index][current_sound][i];
      }
    }
    mode = MODE_FILTER;
    copy_mode = COPY_MODE_TRACK;
    isfunction = false;
  } else if (mode == MODE_COPY_ALL) { // copy track
    if (pattern_bank_index < 8) {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 16; i++) {
          copy_all[j][i] = pattern[pattern_bank_index][j][i];
        }
      }
    }
    mode = MODE_FILTER;
    copy_mode = COPY_MODE_ALL;
    isfunction = false;
  } else if (mode == MODE_PASTE && copy_mode != COPY_MODE_NONE) { // copy track
    if (pattern_bank_index < 8) {
      if (copy_mode == COPY_MODE_TRACK) {
        for (int i = 0; i < 16; i++) {
          pattern[pattern_bank_index][current_sound][i] = copy_track[i];
        }
      } else if (copy_mode == COPY_MODE_ALL) {
        for (int j = 0; j < 8; j++) {
          for (int i = 0; i < 16; i++) {
            pattern[pattern_bank_index][j][i] = copy_all[j][i];
          }
        }
      }
    }
    // copy_mode=COPY_MODE_NONE;
    mode = MODE_FILTER;
    isfunction = false;
  }

  currtouchedA = capA.touched();
  currtouchedB = capB.touched();

  for (uint8_t i = 0; i < 13; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BVA(i)) && !(lasttouchedA & _BVA(i))) {
      if (isfunction == false) {

        pattern[pattern_bank_index][current_sound][i] =
            !pattern[pattern_bank_index][current_sound]
                    [i]; // set the current pattern

        Serial.print("Patter index");
        Serial.println(i);
      } else if (isfunction == true) {
        // lETS SEE WHAT FUNCTION TO SET
        switch (i) {
        case MODE_TEMPO:
          mode = MODE_TEMPO;
          isfunction = false;
          Serial.println("MODE_TEMPO");
          break;
        case MODE_FILTER:
          mode = MODE_FILTER;
          isfunction = false;
          Serial.println("MODE_FILTER");
          break;
        case MODE_REVERB_VAL:
          mode = MODE_REVERB_VAL;
          isfunction = false;
          Serial.println("MODE_REVERB_VAL");
          break;
        case MODE_REVERB_MIX:
          mode = MODE_REVERB_MIX;
          isfunction = false;
          Serial.println("MODE_REVERB_MIX");
          break;
        case MODE_BITCRUSH_MIX:
          mode = MODE_BITCRUSH_MIX;
          isfunction = false;
          Serial.println("MODE_BITCRUSH_MIX");
          break;
        case MODE_BITCRUSH_VAL:
          mode = MODE_BITCRUSH_VAL;
          isfunction = false;
          Serial.println("MODE_BITCRUSH_VAL");
          break;
        case MODE_VOLUME:
          mode = MODE_VOLUME;
          isfunction = false;
          Serial.println("MODE_VOLUME");
          break;
        case MODE_COPY_TRACK:
          mode = MODE_COPY_TRACK;
          isfunction = false;
          Serial.println("MODE_COPY_TRACK");
          break;
        case MODE_COPY_ALL:
          mode = MODE_COPY_ALL;
          isfunction = false;
          Serial.println("MODE_COPY_ALL");
          break;
        }
      }
    }
  }

  for (uint8_t i = 0; i < 13; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BVB(i)) && !(lasttouchedB & _BVB(i))) {
      if (i < 4) {
        if (isfunction == false) {
          pattern[pattern_bank_index][current_sound][i + 12] =
              !pattern[pattern_bank_index][current_sound]
                      [i + 12]; // set the current pattern
          Serial.print("Patter index");
          Serial.println(i + 12);
        } else if (isfunction == true) {
          Serial.print("function mode");
          // lETS SEE WHAT FUNCTION TO SET
          switch (i + 12) {
          case MODE_PASTE:
            mode = MODE_PASTE;
            isfunction = false;
            Serial.println("MODE_PASTE");
            break;
          case MODE_CLEAR_TRACK:
            mode = MODE_CLEAR_TRACK;
            isfunction = false;
            Serial.println("MODE_CLEAR_TRACK");
            break;
          case MODE_CLEAR_ALL:
            mode = MODE_CLEAR_ALL;
            isfunction = false;
            Serial.println("MODE_CLEAR_ALL");
            break;
          case MODE_CLEAR_ALL_BANKS:
            mode = MODE_CLEAR_ALL_BANKS;
            isfunction = false;
            Serial.println("MODE_CLEAR_ALL_BANKS");
            break;
          }
        }
      } else {
        if (isfunction == false) {
          if (isplaying == false) {
            isfunction = false;
            usbMIDI.sendNoteOn((60+(i - 4)), 99, channel);  // 60 = C4
            PlaySound(i - 4);
            usbMIDI.sendNoteOff((60+(i - 4)), 99, channel);  // 60 = C4
          } else {
            current_sound = i - 4;
          }

          Serial.print("current sound");
          Serial.println(current_sound);
        } else if (isfunction == true) {
          pattern_bank_index = i - 4;
          Serial.print("current pattern_bank_index");
          Serial.println(pattern_bank_index);
        }
      }
    }
  }
  // reset our state
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;

  if(internal_clock==true){
    if (millis() >= next) {
      next = millis() + tempo;
      
      if(internal_clock==true && counter2 ==0){
        
        Play_Pattern();
      }
      usbMIDI.sendRealTime(usbMIDI.Clock);
      counter2++; 
      if(counter2 >= 6) { 
        counter2 = 0; 
        
      }
      //Play_Pattern();
    }
  }
  
   // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void Play_Pattern(){
  dataRED = 0;
    dataGREEN = 0;
    digitalWrite(latchPin, 0);
    // Display the pattern
    for (int i = 0; i < 16; i++) {
      if (pattern[pattern_bank_index][current_sound][i] == 1) {
        SetPattern(i);
      } else if (i == pattern_index) {
        if (isplaying == true) {
          SetPattern(i);
        }
      }
    }

    for (int i = 0; i < 8; i++) {
      if (pattern[pattern_bank_index][i][pattern_index] == 1) {
        if (isplaying == true) {
          PlaySound(i);
        }
      }
    }
    pattern_index = pattern_index + 1;
    if (pattern_index > 15) {
      pattern_index = 0;
    }
    // Display the data
    shiftOut(dataPin, clockPin, dataRED);
    shiftOut(dataPin, clockPin, dataGREEN);
    digitalWrite(latchPin, 1);
}
void displaypattern() {

  // Display the pattern
  for (int i = 0; i < 16; i++) {
    dataRED = 0;
    dataGREEN = 0;
    digitalWrite(latchPin, 0);
    SetPattern(i);
    // Display the data
    shiftOut(dataPin, clockPin, dataRED);
    shiftOut(dataPin, clockPin, dataGREEN);
    digitalWrite(latchPin, 1);
    delay(20);
  }
}
void SetPattern(int i) {
  i = 15 - i;
  if (i < 8) {
    bitSet(dataGREEN, i);
  } else {
    bitSet(dataRED, i - 8);
  }
}

char *string2char(String str) {
  if (str.length() != 0) {
    char *p = const_cast<char *>(str.c_str());
    return p;
  }
}

float eraseBytesPerSecond(const unsigned char *id) {
  if (id[0] == 0x20)
    return 152000.0; // Micron
  if (id[0] == 0x01)
    return 500000.0; // Spansion
  if (id[0] == 0xEF)
    return 419430.0; // Winbond
  if (id[0] == 0xC2)
    return 279620.0; // Macronix
  return 320000.0;   // guess?
}

void PlaySound(int i) {
  String soundfile = String(sound_bank) + "_" + String(i + 1) + ".RAW";
  if (!player[i].isPlaying()) {
    player[i].stop();

    player[i].play(string2char(soundfile));
  } else {
    player[i].play(string2char(soundfile));
  }
}

void flash_memeory() {
  Serial.println("Copy all files from SD Card to SPI Flash");

  if (!SD.begin(SDchipSelect)) {
    error("Unable to access SD card");
  }
  if (!SerialFlash.begin(FlashChipSelect)) {
    error("Unable to access SPI Flash chip");
  }

  File rootdir = SD.open("/");
  while (1) {
    // open a file from the SD card
    Serial.println();
    File f = rootdir.openNextFile();
    if (!f)
      break;
    const char *filename = f.name();
    Serial.print(filename);
    Serial.print("    ");
    unsigned long length = f.size();
    Serial.println(length);

    // check if this file is already on the Flash chip
    if (SerialFlash.exists(filename)) {
      Serial.println("  already exists on the Flash chip");
      SerialFlashFile ff = SerialFlash.open(filename);
      if (ff && ff.size() == f.size()) {
        Serial.println("  size is the same, comparing data...");
        if (compareFiles(f, ff) == true) {
          Serial.println("  files are identical :)");
          f.close();
          ff.close();
          continue; // advance to next file
        } else {
          Serial.println("  files are different");
        }
      } else {
        Serial.print("  size is different, ");
        Serial.print(ff.size());
        Serial.println(" bytes");
      }
      // delete the copy on the Flash chip, if different
      Serial.println("  delete file from Flash chip");
      SerialFlash.remove(filename);
    }

    // create the file on the Flash chip and copy data
    if (SerialFlash.create(filename, length)) {
      SerialFlashFile ff = SerialFlash.open(filename);
      if (ff) {
        Serial.print("  copying");
        // copy data loop
        unsigned long count = 0;
        unsigned char dotcount = 9;
        while (count < length) {
          char buf[256];
          unsigned int n;
          n = f.read(buf, 256);
          ff.write(buf, n);
          count = count + n;
          Serial.print(".");
          if (++dotcount > 100) {
            Serial.println();
            dotcount = 0;
          }
        }
        ff.close();
        if (dotcount > 0)
          Serial.println();
      } else {
        Serial.println("  error opening freshly created file!");
      }
    } else {
      Serial.println("  unable to create file");
    }
    f.close();
  }
  rootdir.close();
  delay(10);
  Serial.println("Finished All Files");
}
void erase_flash() {
  unsigned long startMillis = millis();
  delay(100);

  if (!SerialFlash.begin(FlashChipSelect)) {
    while (1) {
      Serial.println("Unable to access SPI Flash chip");
      delay(1000);
    }
  }
  unsigned char id[5];
  SerialFlash.readID(id);
  unsigned long size = SerialFlash.capacity(id);

  if (size > 0) {
    Serial.print("Flash Memory has ");
    Serial.print(size);
    Serial.println(" bytes.");
    Serial.println("Erasing ALL Flash Memory:");
    // Estimate the (lengthy) wait time.
    Serial.print("  estimated wait: ");
    int seconds = (float)size / eraseBytesPerSecond(id) + 0.5;
    Serial.print(seconds);
    Serial.println(" seconds.");
    Serial.println("  Yes, full chip erase is SLOW!");
    SerialFlash.eraseAll();
    unsigned long dotMillis = millis();
    unsigned char dotcount = 0;
    while (SerialFlash.ready() == false) {
      if (millis() - dotMillis > 1000) {
        dotMillis = dotMillis + 1000;
        Serial.print(".");
        dotcount = dotcount + 1;
        if (dotcount >= 60) {
          Serial.println();
          dotcount = 0;
        }
      }
    }
    if (dotcount > 0)
      Serial.println();
    Serial.println("Erase completed");
    unsigned long elapsed = millis() - startMillis;
    Serial.print("  actual wait: ");
    Serial.print(elapsed / 1000ul);
    Serial.println(" seconds.");
  }
}
bool compareFiles(File &file, SerialFlashFile &ffile) {
  file.seek(0);
  ffile.seek(0);
  unsigned long count = file.size();
  while (count > 0) {
    char buf1[128], buf2[128];
    unsigned long n = count;
    if (n > 128)
      n = 128;
    file.read(buf1, n);
    ffile.read(buf2, n);
    if (memcmp(buf1, buf2, n) != 0)
      return false; // differ
    count = count - n;
  }
  return true; // all data identical
}
void error(const char *message) {
  while (1) {
    Serial.println(message);
    delay(2500);
  }
}

// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  // on the rising edge of the clock,
  // clock idles low

  // internal function setup
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  // clear everything out just in case to
  // prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  // for each bit in the byte myDataOutï¿½
  // NOTICE THAT WE ARE COUNTING DOWN in our for loop
  // This means that %00000001 or "1" will go through such
  // that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--) {
    digitalWrite(myClockPin, 0);

    // if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if (myDataOut & (1 << i)) {
      pinState = 1;
    } else {
      pinState = 0;
    }

    // Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    // register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    // zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  // stop shifting
  digitalWrite(myClockPin, 0);
}

// blinks the whole register based on the number of times you want to
// blink "n" and the pause between them "d"
// starts with a moment of darkness to make sure the first blink
// has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}

int ReadPot() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(POT_PIN);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  return average;
}