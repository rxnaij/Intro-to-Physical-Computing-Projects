/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

const int fanPin = 8;
const int ledPin = 3;

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");

    // Initialize delayTime
    delayTime = 1000;

    Serial.println();

    pinMode(fanPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}


void loop() { 
    printValues();
    delay(delayTime);
}


/*  printValues()
 *  Prints current values detected by BME sensor
*/
void printValues() {
    // Temperature
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    // Pressure
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    // Altitude
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    // Humidity
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();

    lightLED();
    digitalWrite(fanPin, spinFan());
}

void lightLED() {
    int humidity = bme.readHumidity();
    int power = map(bme.readHumidity(), 15, 55, 0, 255);
    analogWrite(ledPin, power);
}

float spinFan() {
    if (bme.readTemperature() > 30) {
      return HIGH;
      Serial.println("Fan is spinning");
    } else {
      return LOW;
    }
}
