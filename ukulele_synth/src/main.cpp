
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#include <Arduino.h>
#include <keypad.h>
#include <Audio.h>
#include "chords.h"
#include <Bounce.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

// GUItool: begin automatically generated code

Bounce button0 = Bounce(1, 5);

// GUItool: begin automatically generated code
AudioSynthKarplusStrong string1; //xy=66,132
AudioSynthKarplusStrong string2; //xy=99,171
AudioSynthKarplusStrong string3; //xy=106,220
AudioSynthKarplusStrong string4; //xy=115,274
AudioSynthKarplusStrong string5; //xy=116,328
AudioSynthKarplusStrong string6; //xy=121,381
AudioMixer4 mixer1;              //xy=423,187
AudioMixer4 mixer2;              //xy=444,365
AudioEffectFreeverb freeverb1;   //xy=592,424
AudioMixer4 mixer3;              //xy=644,332
AudioOutputAnalog dac1;          //xy=764,299
AudioConnection patchCord1(string1, 0, mixer1, 0);
AudioConnection patchCord2(string2, 0, mixer1, 1);
AudioConnection patchCord3(string3, 0, mixer1, 2);
AudioConnection patchCord4(string4, 0, mixer1, 3);
AudioConnection patchCord5(string5, 0, mixer2, 1);
AudioConnection patchCord6(string6, 0, mixer2, 2);
AudioConnection patchCord7(mixer1, 0, mixer2, 0);
AudioConnection patchCord8(mixer2, freeverb1);
AudioConnection patchCord9(mixer2, 0, mixer3, 0);
AudioConnection patchCord10(freeverb1, 0, mixer3, 1);
AudioConnection patchCord11(mixer3, dac1);
// GUItool: end automatically generated code

// GUItool: end automatically generated code
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'3', '2', '1', '0'},
    {'7', '6', '5', '4'},
    {'8', '9', 'A', 'B'},
    {'C', 'D', 'E', 'F'}};

char MapKey[] = {'0', '1', '2', '3', '4', '5', '6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', 'F'};
float MapValue[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.99, 0, 0, 0, 0, 0};

byte rowPins[ROWS] = {4, 3, 2, 1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6, 5}; //connect to the column pinouts of the keypad

void strum_up(const float *chord, float velocity);
void strum_dn(const float *chord, float velocity);

const int TOUCH_INPUTS = 6;
bool touched[TOUCH_INPUTS];
int avg[TOUCH_INPUTS];
int startup = 64;
char lastpressed = ' ';
bool majour = false;

#define VARIANCE_TOUCH 200
#define VARIANCE_UNTOUCH 80

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int TOTAL_POTS = 3;

const int NUMBER_READINGS = 5;
int pot_readings[TOTAL_POTS][NUMBER_READINGS]; // the readings from the analog input
int pot_readIndex[TOTAL_POTS];                 // the index of the current reading
int pot_total[TOTAL_POTS];                     // the running total
int pot_average[TOTAL_POTS];                   // the average

//Setup the post 0 everything
void SetupPots()
{
  for (int i = 0; i < TOTAL_POTS; i++)
  {
    pot_readIndex[i] = 0;
    pot_total[i] = 0;
    pot_average[i] = 0;
  }
}

int ReadPot(int pot_index, int pot_pin)
{
  // subtract the last reading:
  pot_total[pot_index] = pot_total[pot_index] - pot_readings[pot_index][pot_readIndex[pot_index]];
  // read from the sensor:
  pot_readings[pot_index][pot_readIndex[pot_index]] = analogRead(pot_pin);
  // add the reading to the total:
  pot_total[pot_index] = pot_total[pot_index] + pot_readings[pot_index][pot_readIndex[pot_index]];
  // advance to the next position in the array:
  pot_readIndex[pot_index] = pot_readIndex[pot_index] + 1;

  // if we're at the end of the array...
  if (pot_readIndex[pot_index] >= NUMBER_READINGS)
  {
    // ...wrap around to the beginning:
    pot_readIndex[pot_index] = 0;
  }

  // calculate the average:
  pot_average[pot_index] = pot_total[pot_index] / NUMBER_READINGS;
  // send it to the computer as ASCII digits
  return pot_average[pot_index];
}

void touch_event(int num, int Current_Chord)
{
  const float *chord;

  switch (Current_Chord)
  {
  case 0:
    if (majour == true)
    {
      chord = Cmajor;
    }
    else
    {
      chord = Cminor;
    }
  case 1:
    if (majour == true)
    {
      chord = Dmajor;
    }
    else
    {
      chord = Dminor;
    }
    break;
  case 2:
    if (majour == true)
    {
      chord = Emajor;
    }
    else
    {
      chord = Eminor;
    }
  case 3:
    if (majour == true)
    {
      chord = Fmajor;
    }
    else
    {
      chord = Fminor;
    }
  case 4:
    if (majour == true)
    {
      chord = Gmajor;
    }
    else
    {
      chord = Gminor;
    }
  case 5:
    if (majour == true)
    {
      chord = Amajor;
    }
    else
    {
      chord = Aminor;
    }
  case 6:
    if (majour == true)
    {
      chord = Bmajor;
    }
    else
    {
      chord = Bminor;
    }
  default:
    chord = Fmajor;
  }

Serial.println(Current_Chord);
   //Left just strum the strings
  if (num == 0)
  {
    if (chord[0] > 20.0)
      string1.noteOn(chord[0], 1.0);
  }
  else if (num == 1)
  {
    if (chord[1] > 20.0)
      string2.noteOn(chord[1], 1.0);
  }
  else if (num == 2)
  {
    if (chord[2] > 20.0)
      string3.noteOn(chord[2], 1.0);
  }
  else if (num == 3)
  {
    if (chord[3] > 20.0)
      string4.noteOn(chord[3], 1.0);
  }
  else if (num == 4)
  {
    if (chord[4] > 20.0)
      string4.noteOn(chord[3], 1.0);
  }
  else if (num == 5)
  {
    if (chord[5] > 20.0)
      string4.noteOn(chord[3], 1.0);
  }
}

void untouch_event(int num)
{
  //Serial.printf("Release %d\n", num);
}

//************************************
//Function just to map the keys to the
//a value
//************************************
float KeyMap(char c)
{
  for (unsigned int i = 0; i < sizeof(MapKey); i++)
  {
    if (MapKey[i] == c)
    { //modified here
      return MapValue[i];
    }
  }
}

void setup()
{

  while (!Serial)
  { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A))
  {
    Serial.println("MPR121 not found, check wiring?");
    while (1)
      ;
  }
  Serial.println("MPR121 found!");

  pinMode(9, INPUT_PULLUP);
  Serial.begin(9600);
  AudioMemory(15);
  SetupPots();
  dac1.analogReference(INTERNAL); // normal volume
  //dac1.analogReference(EXTERNAL); // louder
  mixer1.gain(0, 0.27);
  mixer1.gain(1, 0.27);
  mixer1.gain(2, 0.27);
  mixer1.gain(3, 0.27);
  mixer2.gain(1, 0.27);
  mixer2.gain(2, 0.27);

  mixer3.gain(0, 0);
  mixer3.gain(1, 1);
  freeverb1.roomsize(0.5);
  freeverb1.damping(0.5);
  delay(100);
}

void loop()
{
  int pot1 = ReadPot(0, A6);
  int pot2 = ReadPot(1, A7);
  int pot3 = ReadPot(2, A0);

//front A6
//middle is A7
//back is A0

  int mix = map(pot1, 1, 1023, 0, 100);
  int roomsize = map(pot2, 1, 1023, 0, 100);
  int damp = map(pot3, 1, 1023, 0, 100);
//Serial.print("mix");
 /// Serial.println(mix);
  //Serial.println(roomsize);
  // Serial.println(damp);



  float channel1mix = float(mix) / 100;
  float channel2mix = 1 - channel1mix;
  mixer3.gain(0, channel1mix);
  mixer3.gain(1, channel2mix);

  freeverb1.roomsize(float(roomsize) / 100);
  freeverb1.damping(float(damp) / 100);
  button0.update();

  currtouched = cap.touched();

  int Current_Chord = 0;
  for (uint8_t i = 0; i < 7; i++)
  {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
    {
      Serial.print(i);
      Serial.println(" touched");
      Current_Chord = i;
    }
    // if it *was* touched and now *isnt*, alert!
    // if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)))
    //  {
    // Serial.print(i);
    //  Serial.println(" released");
    // }
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;

  if (button0.fallingEdge())
  {
    Serial.println("Oracle Application Express");
    majour = !majour;
  }
  

  int s[TOUCH_INPUTS];
  int i, diff, variance;

  //Read the strings
  s[0] = touchRead(0) << 10;
  s[1] = touchRead(15) << 10;
  s[2] = touchRead(16) << 10;
  s[3] = touchRead(17) << 10;
  s[4] = touchRead(22) << 10;
  s[5] = touchRead(23) << 10;

  if (startup)
  {
    for (i = 0; i < TOUCH_INPUTS; i++)
    {
      avg[i] += s[i];
    }
    if (--startup == 0)
    {
      avg[i] /= 64;
    }
  }
  for (i = 0; i < TOUCH_INPUTS; i++)
  {
    diff = s[i] - avg[i];
    variance = diff / (avg[i] >> 10);
    Serial.printf("%6d ", variance);
    if (touched[i] == false)
    {
      if (variance >= VARIANCE_TOUCH)
      {
        touched[i] = true;
        touch_event(i, Current_Chord);
      }
    }
    else
    {
      if (variance <= VARIANCE_UNTOUCH)
      {
        touched[i] = false;
        untouch_event(i);
      }
    }
    if (diff > 0)
    {
      avg[i] += diff >> 13; // increase average slowly
    }
    else
    {
      avg[i] += diff >> 6; // decrease average rapidly
    }
  }

  //Serial.printf("%8d  %8d", s[0], avg[0]);
  //Serial.println();

  return;
}
