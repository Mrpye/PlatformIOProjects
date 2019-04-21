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

String sounds[] = {"KICK.RAW",   "SNARE.RAW", "CLAP.RAW", "HIHAT.RAW",
                   "CHIME3.TRW", "KISS.RAW",  "B1.TRW",   "C2.TRW"};
const int FlashChipSelect = 6; // digital pin for flash chip CS pin

int pattern[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int pattern_index = 0;
int current_sound = 0;
int tempo = 100;

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;
uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;

void setup() {

  // Serial.begin(9600);
  Serial.begin(115200);

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
}

void loop() {

  int tempA = analogRead(A6);
  tempo = map(tempA, 0, 1023, 50, 300);

  currtouchedA = capA.touched();
  currtouchedB = capB.touched();

  for (uint8_t i = 0; i < 13; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BVA(i)) && !(lasttouchedA & _BVA(i))) {
      pattern[current_sound][i] =
          !pattern[current_sound][i]; // set the current pattern
      Serial.print(i);
      Serial.println(" touched A");
    }
  }

  for (uint8_t i = 0; i < 13; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BVB(i)) && !(lasttouchedB & _BVB(i))) {
      if (i < 4) {
        pattern[current_sound][i + 12] =
            !pattern[current_sound][i + 12]; // set the current pattern
      } else {
        current_sound = i - 4;
      }
      Serial.print(i);
      Serial.println(" touched B");
    }
  }
  // reset our state
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;

 //for (uint8_t i = 0; i < 16; i++) {
   // Serial.print(pattern[current_sound][i]);
  //}
 // Serial.print("CURRENT SOUND");
  //Serial.println(current_sound);
}
