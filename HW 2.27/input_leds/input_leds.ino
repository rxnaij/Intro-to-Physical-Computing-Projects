/*
  Analog Input, but with Serial Plotter!
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
  * center pin of the potentiometer to the analog pin
  * one side pin (either one) to ground
  * the other side pin to +5V
 * Button attached to digital input 2, 5V+, and ground
 * LED anode (long leg) attached to digital outputs 6, 9, 10, and 11
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 27 Feb 2019
 By Richard Lu

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */

// pins
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPins[] = {6, 9, 10, 11}; // represents set of LEDs
int buttonPin = 2;

// stores input values
int sensorValue = 0;  // variable to store the value coming from the sensor
int buttonValue = 0; // stores button value

void setup() {
  // declare the ledPin as an OUTPUT:
  for (int i = 0; i < 4; i++) { // initialize set of LEDs
    pinMode(ledPins[i], OUTPUT); 
  }
  pinMode(buttonPin, INPUT); // initialize button
  // I guess I don't have to initialize the potentiometer?
  // begin the serial monitor @ 9600 baud
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);
  Serial.print(" ");

  // writes sensor value into LEDs
  for (int i = 0; i < 4; i++) {
    analogWrite(ledPins[i], sensorValue);
  }

  // listens for button press
  buttonValue = digitalRead(buttonPin);
  if (buttonValue == HIGH) {
    // flashes LEDs in sequence on button press
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
      digitalWrite(ledPins[i], HIGH);
      delay(50);
      digitalWrite(ledPins[i], LOW);
      delay(50);
      }
    }
    delay(20);
  }
 
  delay(20);
}
