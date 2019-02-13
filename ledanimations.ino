/*
 * 8-LED Animations
 * 
 * Provides several functions that each light up a series of 8 LEDs in different ways.
 * 
 * The circuit:
 * * 5V connected to power
 * * Digital pins 2 through 9 connected to 8 LEDs of any color
 * * 330 ohm resistors connecting LEDs to ground
 * * GND connected to ground
 * 
 * Created 2/11/2019
 * by Richard Lu
 * modified N/A
 * by N/A
 */

// Set of pins that will be used for this circuit
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numPins = 8;

void setup() {
  // Initialize pins to output mode
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() { // executes code repeatedly
  twoAtATime();

//  alternate();
//    alternateInSequence();
//  alternateAnalog();
}

// 1. Blinks a pair of two adjacent lights at a time.
// 2. Unlights the pair, then blinks the next pair of adjacent lights
void twoAtATime() {
  int delayTime = 800; // time length of pause between lightings

  for (int i = 0; i <= numPins - 1; i+=2) {

    // de-light previous LEDs:
    
    // assign LEDs to de-light
    int offLEDs[] = {i - 2, i - 1};
    // case: if i == 0 (first in sequence), deactivate LAST LEDs in sequence: 6, 7
    if (i == 0) {
      offLEDs[0] = numPins - 2;
      offLEDs[1] = numPins - 1;
    }
    // de-light LEDs
    digitalWrite(ledPins[offLEDs[0]], LOW);
    digitalWrite(ledPins[offLEDs[1]], LOW);

    // light next LEDs:
    
    // lights up next pair of pins
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i + 1], HIGH);
    delay(delayTime);
  }
}

// Blinks every other LEDs in alternating patterns:
// Odd-numbered pins, then even-numbered pins
void alternate() {
  int delayTime = 500;

  // light odd-numbered pins
  for(int i = 0; i < numPins; i += 2) {
    digitalWrite(ledPins[i], HIGH);
  }
  
  delay(delayTime);

  // unlight odd-numbered pins
  for(int i = 0; i < numPins; i += 2) {
    digitalWrite(ledPins[i], LOW);
  }

  // light even-numbered pins
  for(int i = 1; i < numPins; i += 2) {
    digitalWrite(ledPins[i], HIGH);
  }

  delay(delayTime);

  // unlight even-numbered pins
  for(int i = 1; i < numPins; i += 2) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Lights every other LED in order of lowest to highest pin.
// Lights odd LEDs, de-lights all, then lights even LEDs, then de-lights all
void alternateInSequence() {
  int delayTime = 800;
  
  // light odd-numbered pins
  for (int i = 0; i < numPins; i += 2) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
  eraseAllPins();
  delay(delayTime);

  // light even-numbered pins
  for (int i = 1; i < numPins; i += 2) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
  eraseAllPins();
  delay(delayTime);
}

// Helper function: unlights all pins
void eraseAllPins() {
  for (int i = 0; i < numPins; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Fades in and out every other LED: first: all odd LEDs, then all even LEDs
// Identical to alternate, but the lighting is analog (happens gradually)
/* I discovered that this function doesn't work. Only a few of the pins on the board are analog. */
void alternateAnalog() {
  int oddPins[] = {0, 2, 4, 6};
  int evenPins[] = {1, 3, 5, 7};
  
  // light odd-numbered pins
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
//    for (int i = 0; i < 4; i++) {
//      analogWrite(ledPins[oddPins[i]], fadeValue);
//    }
    analogWrite(ledPins[0], fadeValue);
    analogWrite(ledPins[2], fadeValue);
    analogWrite(ledPins[4], fadeValue);
    analogWrite(ledPins[6], fadeValue);
    delay(30);
  }

  // unlight odd-numbered pins
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    for (int i = 0; i < 4; i++) {
      analogWrite(ledPins[oddPins[i]], fadeValue);
    }
    delay(30);
  }

  // light even-numbered pins
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    for (int i = 0; i < 4; i++) {
      analogWrite(ledPins[evenPins[i]], fadeValue);
    }
    delay(30);
  }

  // unlight even-numbered pins
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    for (int i = 0; i < 4; i++) {
      analogWrite(ledPins[evenPins[i]], fadeValue);
    }
    delay(30);
  }
}
