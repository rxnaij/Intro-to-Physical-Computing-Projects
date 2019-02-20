/*
  HW 2.20 - Melody + lights

  Plays a melody and flashes the LED along.

  circuit:
  - 8 ohm speaker on digital pin 5
  - RGB LED on digital pins 9, 10, and 11

  created 21 Jan 2010
  modified 30 Aug 2019
  by Richard Lu
  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h" // key file for tones

// pin for speaker
const int tonePin = 5;

// pins for LED
const int redPin = 9;
const int bluePin = 10;
const int greenPin = 11;

void setup() {
}

void loop() {
  playSong();
}

// Plays "Somewhere Over the Rainbow" on speaker
void playSong() {
  // Somewhere Over the Rainbow melody: {pitch, length of note}
  const int songMelody[][2] = {
    {NOTE_C4, 2}, {NOTE_C5, 2},
    {NOTE_B4, 4}, {NOTE_G4, 8}, {NOTE_A4, 8}, {NOTE_B4, 4}, {NOTE_C5, 4},
    {NOTE_C4, 2}, {NOTE_A4, 2},
    {NOTE_G4, 2}, {NOTE_B3, 4}, {NOTE_AS3, 4},
    {NOTE_A3, 2}, {NOTE_F4, 2},
    {NOTE_E4, 4}, {NOTE_C4, 8}, {NOTE_D4, 8}, {NOTE_E4, 4}, {NOTE_F4, 4},
    {NOTE_C4, 4}, {NOTE_B3, 8}, {NOTE_C4, 8}, {NOTE_D4, 4}, {NOTE_E4, 4},
    {NOTE_C4, 1},
    };
  const int noteDuration = 1500;  // length of a whole note in ms
  // helpful constants to make following code clear
  const int PITCH = 0;
  const int TIME = 1;

  // plays melody
  for (int i = 0; i < 25; i++) {
    // plays note
    int duration = noteDuration / songMelody[i][TIME]; // determine duration of each note
    tone(tonePin, songMelody[i][PITCH], duration); // play note
    lightLED(i); // lights LED alternating colors, depending on the current note

    // briefly pauses between notes so they don't get jumbled together
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    // ends tone
    noTone(tonePin);
  }
}

// Flashes LED light different colors depending on input
void lightLED(int val){
  int r = 255;
  int g = 255;
  int b = 255;
  if (val % 2 == 0) {
    g = 0;
    b = 0;
  } else if(val % 2 == 1) {
    r = 0;
    b = 0;
  }
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
