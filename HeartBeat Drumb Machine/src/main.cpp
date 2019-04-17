#include "Adafruit_MPR121.h"
#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#ifndef _BVA
#define _BVA(bit) (1 << (bit))
#endif
#ifndef _BVB
#define _BVB(bit) (1 << (bit))
#endif
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 capa = Adafruit_MPR121();
Adafruit_MPR121 capb = Adafruit_MPR121();

// String sounds[] = {"C1.TRW", "D1.TRW", "E1.TRW", "F1.TRW",
//                   "G1.TRW", "A1.TRW", "B1.TRW", "C2.TRW"};
String sounds[] = {"KICK.RAW", "SNARE.RAW", "CLAP.RAW", "HIHAT.RAW",
                   "CHIME3.TRW", "KISS.RAW", "B1.TRW", "C2.TRW"};

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttoucheda = 0;
uint16_t currtoucheda = 0;
uint16_t lasttouchedb = 0;
uint16_t currtouchedb = 0;
const int FlashChipSelect = 6; // digital pin for flash chip CS pin
const int PLAYERS = 32;

//Pin connected to ST_CP of 74HC595
int latchPin = 1;
//Pin connected to SH_CP of 74HC595
int clockPin = 0;
////Pin connected to DS of 74HC595
int dataPin = 8;
byte dataRED;
byte dataGREEN;


// GUItool: begin automatically generated code
AudioPlaySerialflashRaw sound[] = {
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw(),
    AudioPlaySerialflashRaw(), AudioPlaySerialflashRaw()}; // xy=123,44

// GUItool: begin automatically generated code

AudioMixer4 mix5;          // xy=284,96
AudioMixer4 mix7;          // xy=296,547
AudioMixer4 mix6;          // xy=310,331
AudioMixer4 mix8;          // xy=312,782
AudioMixer4 mix10;         // xy=333,1015
AudioMixer4 mix12;         // xy=345,1466
AudioMixer4 mix11;         // xy=359,1250
AudioMixer4 mix13;         // xy=361,1701
AudioMixer4 mix9;          // xy=457,271
AudioMixer4 mix14;         // xy=506,1188
AudioMixer4 mix15;         // xy=573,503
AudioOutputAnalog dac;     // xy=747,360
AudioOutputI2S headphones; // xy=764,309
AudioConnection patchCord1(sound[0], 0, mix5, 1);
AudioConnection patchCord2(sound[1], 0, mix7, 1);
AudioConnection patchCord3(sound[2], 0, mix5, 0);
AudioConnection patchCord4(sound[3], 0, mix6, 1);
AudioConnection patchCord5(sound[4], 0, mix7, 0);
AudioConnection patchCord6(sound[5], 0, mix8, 1);
AudioConnection patchCord7(sound[6], 0, mix5, 2);
AudioConnection patchCord8(sound[7], 0, mix6, 0);
AudioConnection patchCord9(sound[8], 0, mix7, 3);
AudioConnection patchCord10(sound[9], 0, mix8, 0);
AudioConnection patchCord11(sound[10], 0, mix7, 2);
AudioConnection patchCord12(sound[11], 0, mix10, 1);
AudioConnection patchCord13(sound[12], 0, mix6, 3);
AudioConnection patchCord14(sound[13], 0, mix5, 3);
AudioConnection patchCord15(sound[14], 0, mix6, 2);
AudioConnection patchCord16(sound[15], 0, mix8, 3);
AudioConnection patchCord17(sound[16], 0, mix8, 2);
AudioConnection patchCord18(sound[17], 0, mix12, 1);
AudioConnection patchCord19(sound[18], 0, mix10, 0);
AudioConnection patchCord20(sound[19], 0, mix11, 1);
AudioConnection patchCord21(sound[20], 0, mix12, 0);
AudioConnection patchCord22(sound[21], 0, mix13, 1);
AudioConnection patchCord23(sound[22], 0, mix10, 2);
AudioConnection patchCord24(sound[23], 0, mix11, 0);
AudioConnection patchCord25(sound[24], 0, mix12, 3);
AudioConnection patchCord26(sound[25], 0, mix13, 0);
AudioConnection patchCord27(sound[26], 0, mix12, 2);
AudioConnection patchCord28(sound[27], 0, mix11, 3);
AudioConnection patchCord29(sound[28], 0, mix10, 3);
AudioConnection patchCord30(sound[29], 0, mix11, 2);
AudioConnection patchCord31(sound[30], 0, mix13, 3);
AudioConnection patchCord32(sound[31], 0, mix13, 2);
AudioConnection patchCord33(mix5, 0, mix9, 0);
AudioConnection patchCord34(mix7, 0, mix9, 2);
AudioConnection patchCord35(mix6, 0, mix9, 1);
AudioConnection patchCord36(mix8, 0, mix9, 3);
AudioConnection patchCord37(mix10, 0, mix14, 0);
AudioConnection patchCord38(mix12, 0, mix14, 2);
AudioConnection patchCord39(mix11, 0, mix14, 1);
AudioConnection patchCord40(mix13, 0, mix14, 3);
AudioConnection patchCord41(mix9, 0, mix15, 0);
AudioConnection patchCord42(mix14, 0, mix15, 1);
AudioConnection patchCord43(mix15, 0, headphones, 0);
AudioConnection patchCord44(mix15, 0, headphones, 1);
AudioConnection patchCord45(mix15, dac);
AudioControlSGTL5000 audioShield; // xy=758,403
// GUItool: end automatically generated code

char *string2char(String str) {
  if (str.length() != 0) {
    char *p = const_cast<char *>(str.c_str());
    return p;
  }
}
static uint32_t next;

int pattern[4][16] = {
{0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0}
};
int pattern_index = 0;
int current_sound = 0;
int temp = 100;
void error(const char *message) {
  while (1) {
    Serial.println(message);
    delay(2500);
  }
}
void setup() {
  Serial.println("Setup");
  if (!capa.begin(0x5A)) {
    Serial.println("MPR121 a not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 a found!");
    if (!capb.begin(0x5B)) {
    Serial.println("MPR121 b not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 b found!");

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  SPI.setSCK(14); // Audio shield has SCK on pin 14
  SPI.setMISO(12);
  SPI.setMOSI(7); // Audio shield has MOSI on pin 7

  if (!SerialFlash.begin(FlashChipSelect)) {
    error("Unable to access SPI Flash chip");
  } else {
    // error("Found SPI Flash chip");
  }
  // by default the Teensy 3.1 DAC uses 3.3Vp-p output
  // if your 3.3V power has noise, switching to the
  // internal 1.2V reference can give you a clean signal
  // dac.analogReference(INTERNAL);

  // turn on the output
  audioShield.enable();
  audioShield.volume(1.0);

  sound[0].play("C1.TRW");
  // reduce the gain on mixer channels, so more than 1
  // sound can play simultaneously without clipping
  const float vol = 0.35;
  for (uint8_t i = 0; i < 4; i++) {
    mix5.gain(i, vol);
    mix6.gain(i, vol);
    mix7.gain(i, vol);
    mix8.gain(i, vol);
    mix9.gain(i, vol);
    mix10.gain(i, vol);
    mix11.gain(i, vol);
    mix12.gain(i, vol);
    mix13.gain(i, vol);
    mix14.gain(i, vol);
  }
  mix15.gain(0, 0.5);
  mix15.gain(1, 0.5);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}
// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

void PlaySound(int i) {
  if (!sound[i].isPlaying()) {
    sound[i].stop();
    sound[i].play(string2char(sounds[i]));
  } else {
    sound[i].play(string2char(sounds[i]));
  }
  
}
void loop() {

  // Get the currently touched pads
  int aval=analogRead(A6);
   temp=map(aval,0,1023,50,300);

  currtoucheda = capa.touched();
  currtouchedb = capb.touched();
  // Serial.println(currtoucheda);

  for (uint8_t i = 8; i < 12; i++) {
    if ((currtoucheda & _BVA(i)) && !(lasttoucheda & _BVA(i))) {
      Serial.print(i);
      Serial.println("A touched SOUND SELECT");
      current_sound = i - 8;
      break;
    }
  }
  for (uint8_t i = 8; i < 12; i++) {
    if ((currtouchedb & _BVB(i)) && !(lasttouchedb & _BVB(i))) {
      Serial.print(i);
      Serial.println("B touched SOUND SELECT");
      current_sound = i - 8;
      break;
    }
  }
  for (uint8_t i = 0; i < 16; i++) {
    // cap.setThreshholds(40,1);
    // it if *is* touched and *wasnt* touched before, alert!
    if(i<8){
      if ((currtoucheda & _BVA(i)) && !(lasttoucheda & _BVA(i))) {
        Serial.print(i);
        Serial.println(" touched PATTERN A");
        pattern[current_sound][i] = !pattern[current_sound][i];
      }
    }else{
       if ((currtouchedb & _BVB(i-8)) && !(lasttouchedb & _BVB(i-8))) {
        Serial.print(i);
        Serial.println(" touched PATTERN B");
        pattern[current_sound][i] = !pattern[current_sound][i];
      }
    }

    if (millis() >= next) {
      next = millis() + temp;
      pattern_index = pattern_index + 1;
      if (pattern_index > 16) {
        pattern_index = 0;
      }
      for (int i = 0; i < 4; i++) {
       /// Serial.print(pattern_index);
       //Serial.print(":");
       // Serial.println(pattern[i][pattern_index]);

        if (pattern[i][pattern_index] == 1) {
          PlaySound(i);
        }
      }
    }
  }
dataRED=0;
    dataGREEN=0;

for (int j = 0; j < 16; j++) {
    
   // bitSet( dataGREEN,j);
    //bitSet( dataRED,j);
    digitalWrite(latchPin, 0);
    Serial.println(pattern_index);
    //Serial.println(pattern[current_sound][pattern_index]);
    if(j>7){
        bitSet( dataGREEN,j-8);
       if (pattern[current_sound][pattern_index] == 1) {
     // bitSet( dataGREEN,pattern_index-8);
       }
    }else{
       bitSet( dataRED,j);
       if (pattern[current_sound][pattern_index] == 1) {
     // bitSet( dataRED,pattern_index);
       }
    }
    shiftOut(dataPin, clockPin, dataGREEN);   
    shiftOut(dataPin, clockPin, dataRED);
    digitalWrite(latchPin, 1);
   
}

  lasttoucheda = currtoucheda;
   lasttouchedb = currtouchedb;
}
