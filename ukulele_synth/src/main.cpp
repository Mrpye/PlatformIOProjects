#include <Arduino.h>
#include <keypad.h>
#include <Audio.h>
#include "chords.h"

// GUItool: begin automatically generated code
AudioSynthKarplusStrong string1;
AudioSynthKarplusStrong string2;
AudioSynthKarplusStrong string3;
AudioSynthKarplusStrong string4;
AudioSynthKarplusStrong string5;
AudioSynthKarplusStrong string6;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioOutputAnalog dac1;
AudioConnection patchCord1(string1, 0, mixer1, 0);
AudioConnection patchCord2(string2, 0, mixer1, 1);
AudioConnection patchCord3(string3, 0, mixer1, 2);
AudioConnection patchCord4(string4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, 0, mixer2, 0);
AudioConnection patchCord6(string5, 0, mixer2, 1);
AudioConnection patchCord7(string6, 0, mixer2, 2);
AudioConnection patchCord8(mixer2, 0, dac1, 0);
// GUItool: end automatically generated code

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

const int TOUCH_INPUTS = 4;

bool touched[TOUCH_INPUTS];
int avg[TOUCH_INPUTS];
int startup = 64;
char lastpressed = ' ';
bool majour = false;

#define VARIANCE_TOUCH 200
#define VARIANCE_UNTOUCH 80

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void touch_event(int num)
{
  const float *chord;
  if (lastpressed == ' ')
  {
    if(majour==true){ chord = Fmajor;}else{ chord = Fminor;}
   
  }
  else if (lastpressed == '0')
  {
      if(majour==true){ chord = Fmajor;}else{ chord = Fminor;}

  }
  else if (lastpressed == '1')
  {
     if(majour==true){ chord = Cmajor;}else{ chord =Cminor;}

  }
  else if (lastpressed == '2')
  {
    
      if(majour==true){ chord = Gmajor;}else{ chord = Gminor;}
    
   
  }
  else if (lastpressed == '3')
  {
     if(majour==true){ chord = Dmajor;}else{ chord =Dminor;}
    
  }
  else if (lastpressed == '4')
  {
 if(majour==true){ chord = Amajor;}else{ chord =Aminor;}
  }
  else if (lastpressed == '5')
  {
    if(majour==true){ chord = Emajor;}else{ chord =Eminor;}
  }
  else if (lastpressed == '6')
  {
     if(majour==true){ chord = Bmajor;}else{ chord =Bminor;}
  }else{
    if(majour==true){ chord = Fmajor;}else{ chord = Fminor;}
  }
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
  Serial.begin(9600);
  AudioMemory(15);

  dac1.analogReference(INTERNAL); // normal volume
  //dac1.analogReference(EXTERNAL); // louder
  mixer1.gain(0, 0.27);
  mixer1.gain(1, 0.27);
  mixer1.gain(2, 0.27);
  mixer1.gain(3, 0.27);
  mixer2.gain(1, 0.27);
  mixer2.gain(2, 0.27);
  delay(100);
}

void loop()
{
// char customKey = customKeypad.getKey();
//if (customKey != NO_KEY){
  //  Serial.println("hello");
 //}
 
  if (customKeypad.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if (customKeypad.key[i].stateChanged) // Only find keys that have changed state.
      {
        if(customKeypad.key[i].kstate==PRESSED){
          Serial.println(customKeypad.key[i].kchar);
          if(customKeypad.key[i].kchar=='F'){
            majour=true;
            Serial.println("majour");
          }else if(customKeypad.key[i].kchar=='E'){
            majour=false;
             Serial.println("minor");
          }else{
            lastpressed=customKeypad.key[i].kchar;
          }
        }
      }
    }
  }

  int s[TOUCH_INPUTS];
  int i, diff, variance;

  //Read the strings
  s[0] = touchRead(0) << 10;
  s[1] = touchRead(15) << 10;
  s[2] = touchRead(16) << 10;
  s[3] = touchRead(17) << 10;

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
    //Serial.printf("%6d ", variance);
    if (touched[i] == false)
    {
      if (variance >= VARIANCE_TOUCH)
      {
        touched[i] = true;
        touch_event(i);
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
