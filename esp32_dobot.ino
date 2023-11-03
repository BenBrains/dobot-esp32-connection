/*
  Due to a slight oversight, the emergency switch 'feature' had to be removed.
  Otherwise it wouldn't fit..

  These parts have been commented out 
*/

#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// Sensors
const int trackingPin = 12;

// Blocks (color sensor)
const int redBlock = 25;
const int greenBlock = 26;
const int blueBlock = 27;

// Trafficlight
const int redLight = 15;
const int yellowLight = 2;
const int greenLight = 4;

// Misc
const int dobotMoving = 33;
// BTN - const int stopButton = 0;

void setup() {
  // Sensors
  pinMode(trackingPin, INPUT);
  pinMode(dobotMoving, INPUT);

  // Blocks (color sensor)
  pinMode(redBlock, OUTPUT);
  pinMode(greenBlock, OUTPUT);
  pinMode(blueBlock, OUTPUT);

  // Traffic Light
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);

  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("TCS34725 - Found sensor");
  } else {
    Serial.println("TCS34725 - No sensor found >> Check your connections");
    while (1)
      ;
  }
}

void loop() {

  uint16_t r, g, b, c;
  int sensorValue = digitalRead(trackingPin);
  int isMoving = digitalRead(dobotMoving);
  // BTN - int isStopping = digitalRead(stopButton);

  // ???
  // bool isMoving = digitalRead(dobotMoving) == 1;
  // bool isStopping = digitalRead(stopButton) == 1;


  // Handle lights

  /*

    

    if (isStopping) {
      Serial.println("isStopping");
      setLight(HIGH, LOW, LOW);
    } else 
  */
  if (isMoving) {
    Serial.println("isMoving");
    setLight(LOW, HIGH, LOW);
  } else {
    Serial.println("isIdle");
    setLight(LOW, LOW, HIGH);
  }

  if (sensorValue != 0) {

    // A very scuffed solution to make sure the correct color gets detected
    delay(1000);

    tcs.getRawData(&r, &g, &b, &c);

    if (r > g && r > b) {
      Serial.println("RED");
      digitalWrite(greenBlock, LOW);
      digitalWrite(blueBlock, LOW);
      digitalWrite(redBlock, HIGH);

    } else if (g > r && g > b) {
      Serial.println("GREEN");
      digitalWrite(greenBlock, HIGH);
      digitalWrite(blueBlock, LOW);
      digitalWrite(redBlock, LOW);

    } else if (b > r && b > g) {
      Serial.println("BLUE");
      digitalWrite(greenBlock, LOW);
      digitalWrite(blueBlock, HIGH);
      digitalWrite(redBlock, LOW);

    } else {
      Serial.println("WTF is dit");
      digitalWrite(greenBlock, HIGH);
      digitalWrite(blueBlock, HIGH);
      digitalWrite(redBlock, HIGH);
    }
  } else {
    Serial.println("Not seeing shit");
    delay(1000);

    digitalWrite(greenBlock, LOW);
    digitalWrite(blueBlock, LOW);
    digitalWrite(redBlock, LOW);
  }
}

void setLight(int red, int yellow, int green) {
  digitalWrite(redLight, red);
  digitalWrite(yellowLight, yellow);
  digitalWrite(greenLight, green);
}