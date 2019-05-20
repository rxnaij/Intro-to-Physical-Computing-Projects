// Small LED initialize
#include "LedControl.h"
#include "binary.h"

// Connect to data pins 12 (Data), 11 (Write), 10 (CS)
LedControl small = LedControl(12, 11, 10, 1);

unsigned long delayTime = 1000;

// Small LED face states
byte happy[8] = {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};
byte satisfied[8] = {B00111100,B01000010,B10100101,B10000001,B10100001,B10011101,B01000010,B00111100};
byte neutral[8] = {B00111100, B01000010,B10100101,B10000001,B10111101,B10000001,B01000010,B00111100};
byte dissatisfied[8] = {B00111100,B01000010,B10100101,B10000001,B10111001,B10000101,B01000010,B00111100};
byte sad[8] = {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};

// Large LED initialize
#include "Adafruit_HT1632.h"
#include "Adafruit_GFX.h"

// Connect to data pins 2 (Data), 3 (Write), 4 (CS)
#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

// Large LED data
int grid[16][24][1];
int currentX;
int currentY;
int type;

// Control initialize
int potPin = A0; // Potentiometer in analog pin A0
int button = 5;  // Button in data pin 5
int buttonState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize Small LED
  small.shutdown(0, false);
  small.setIntensity(0, 8);
  small.clearDisplay(0);

  // Initialize Large LED
  currentX = 0;
  currentY = 0;
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.setTextWrap(false);

  // Initialize controls
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Takes the potentiometer reading and displays the corresponding face on the screen
  int reading = analogRead(potPin); // assigns potentiometer input to reading
  int faceVal = drawFaces(reading); // assigns face value to faceVal; displays face
  displayMood(faceVal); // display accumulated mood pixels
}

// Displays a face on the small LED
// reading: potentiometer value set by user
int drawFaces(int reading){
  int face = map(reading, 0, 1023, 0, 5);
  if (face == 0) {
    for (int i = 0; i < 8; i++) {
      small.setRow(0, i, happy[i]);
    }
  } else if (face == 1) {
     for (int i = 0; i < 8; i++) {
       small.setRow(0, i, satisfied[i]);
     }
  } else if (face == 2) {
    for (int i = 0; i < 8; i++) {
      small.setRow(0, i, neutral[i]);
    }
  } else if (face == 3) { 
    for (int i = 0; i < 8; i++) {
      small.setRow(0, i, dissatisfied[i]);
    }
  } else if (face == 4) { 
    for (int i = 0; i < 8; i++) {
      small.setRow(0, i, sad[i]);
    }
  }
  return face;
}

// Display mood pixels, adds mood pixels when button is pushed
void displayMood(int val) {
    matrix.setRotation(0);
    matrix.setCursor(0, 0);

  // read the state of the pushbutton value:
    buttonState = digitalRead(button);
  
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      // redraws existing pixels
      for (int i = 0; i < currentX; i++) {
        for (int j = 0; j < currentY; j++) {
          matrix.drawPixel(i, j, 1);
        }
      }
      // draws newest pixel
      matrix.drawPixel(currentX, currentY, 1);
      grid[currentX][currentY][0] = val;
      currentY = currentY + 1; // advances to next pixel
      // end of line: advances to next line
      if (currentY > 23) {
        currentX = currentX + 1;
        currentY = 0;
      }
    }
    matrix.writeScreen();
    delay(1000);
}
