#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

//String sounds[]={"C1.TRW","D1.TRW","E1.TRW","F1.TRW","G1.TRW","A1.TRW","B1.TRW","C2.TRW"};

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
const int FlashChipSelect = 6; // digital pin for flash chip CS pin



// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  sound15; //xy=106,730
AudioPlaySerialflashRaw  sound11; //xy=107,550
AudioPlaySerialflashRaw  sound13; //xy=109,641
AudioPlaySerialflashRaw  sound14; //xy=110,686
AudioPlaySerialflashRaw  sound9; //xy=111,461
AudioPlaySerialflashRaw  sound10; //xy=111,506
AudioPlaySerialflashRaw  sound12; //xy=111,598
AudioPlaySerialflashRaw  sound8; //xy=112,418
AudioPlaySerialflashRaw  sound7; //xy=117,369
AudioPlaySerialflashRaw  sound5;         //xy=120,280
AudioPlaySerialflashRaw  sound6; //xy=121,325
AudioPlaySerialflashRaw  sound1;         //xy=122,88
AudioPlaySerialflashRaw  sound2;         //xy=122,138
AudioPlaySerialflashRaw  sound3;         //xy=122,190
AudioPlaySerialflashRaw  sound4;         //xy=122,237
AudioPlaySerialflashRaw  sound0;         //xy=123,44
AudioMixer4              mix4; //xy=333,670
AudioMixer4              mix3; //xy=334,490
AudioMixer4              mix2;           //xy=344,309
AudioMixer4              mix1;           //xy=350,132
AudioMixer4              mix5; //xy=532,427
AudioOutputI2S           headphones;     //xy=766,352
AudioOutputAnalog        dac;            //xy=803,421
AudioConnection          patchCord1(sound15, 0, mix4, 3);
AudioConnection          patchCord2(sound11, 0, mix3, 3);
AudioConnection          patchCord3(sound13, 0, mix4, 1);
AudioConnection          patchCord4(sound14, 0, mix4, 2);
AudioConnection          patchCord5(sound9, 0, mix3, 1);
AudioConnection          patchCord6(sound10, 0, mix3, 2);
AudioConnection          patchCord7(sound12, 0, mix4, 0);
AudioConnection          patchCord8(sound8, 0, mix3, 0);
AudioConnection          patchCord9(sound7, 0, mix2, 3);
AudioConnection          patchCord10(sound5, 0, mix2, 1);
AudioConnection          patchCord11(sound6, 0, mix2, 2);
AudioConnection          patchCord12(sound1, 0, mix1, 1);
AudioConnection          patchCord13(sound2, 0, mix1, 2);
AudioConnection          patchCord14(sound3, 0, mix1, 3);
AudioConnection          patchCord15(sound4, 0, mix2, 0);
AudioConnection          patchCord16(sound0, 0, mix1, 0);
AudioConnection          patchCord17(mix4, 0, mix5, 3);
AudioConnection          patchCord18(mix3, 0, mix5, 2);
AudioConnection          patchCord19(mix2, 0, mix5, 1);
AudioConnection          patchCord20(mix1, 0, mix5, 0);
AudioConnection          patchCord21(mix5, 0, headphones, 0);
AudioConnection          patchCord22(mix5, 0, headphones, 1);
AudioConnection          patchCord23(mix5, dac);
AudioControlSGTL5000     audioShield;    //xy=737,504
// GUItool: end automatically generated code

void setup() {
  Serial.println("Setup");
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  SPI.setSCK(14);  // Audio shield has SCK on pin 14
  SPI.setMISO(12);
  SPI.setMOSI(7);  // Audio shield has MOSI on pin 7

  if (!SerialFlash.begin(FlashChipSelect)) {
    error("Unable to access SPI Flash chip");
  }else{
    //error("Found SPI Flash chip");
  }
  // by default the Teensy 3.1 DAC uses 3.3Vp-p output
  // if your 3.3V power has noise, switching to the
  // internal 1.2V reference can give you a clean signal
  //dac.analogReference(INTERNAL);

 

 // turn on the output
  audioShield.enable();
  audioShield.volume(0.8);
  
  // reduce the gain on mixer channels, so more than 1
  // sound can play simultaneously without clipping
  mix1.gain(0, 0.25);
  mix1.gain(1, 0.25);
  mix1.gain(2, 0.25);
  mix1.gain(3, 0.25);
  mix2.gain(0, 0.25);
  mix2.gain(1, 0.25);
  mix2.gain(2, 0.25);
  mix2.gain(3, 0.25);
  mix3.gain(0, 0.25);
  mix3.gain(1, 0.25);
  mix3.gain(2, 0.25);
  mix3.gain(3, 0.25);
  mix4.gain(0, 0.25);
  mix4.gain(1, 0.25);
  mix4.gain(2, 0.25);
  mix4.gain(3, 0.25);
  mix5.gain(0, 0.25);
  mix5.gain(1, 0.25);
  mix5.gain(2, 0.25);
  mix5.gain(3, 0.25);

}

void loop() {

  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
  // cap.setThreshholds(40,1);
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      switch(i){
        case 0:
        
          sound0.play("C1.TRW");
        break;
        case 1:
         sound1.play("D1.TRW");
        break;
        case 2:
          sound2.play("E1.TRW");
        break;
        case 3:
         sound3.play("F1.TRW");
        break;
        case 4:
          sound4.play("G1.TRW");
        break;
       case 5:
          sound5.play("A1.TRW");
        break;
        case 6:
          sound6.play("B1.TRW");
        break;
         case 7:
          sound7.play("C2.TRW");
        break;
      }

   
    }
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed da//ta from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  

  // When the buttons are pressed, just start a sound playing.
  // The audio library will play each sound through the mixers
  // so any combination can play simultaneously.
  //
  

}

void error(const char *message) {
  while (1) {
    Serial.println(message);
    delay(2500);
  }
}
