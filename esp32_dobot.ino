#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

const int trackingPin = 12;
const int colorPin = 34;
const int redPin = 27;
const int greenPin = 25;
const int orangePin = 26;

void setup() {
  pinMode(trackingPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;
  }
}

void loop() {

  int sensorValue = analogRead(trackingPin);
  Serial.print("Sensorwaarde: ");
  Serial.println(sensorValue);

  if (sensorValue != 0) {
    uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);

    if (r > g && r > b) {
      Serial.println("RED");
      digitalWrite(greenPin, LOW);
      digitalWrite(orangePin, LOW);
      digitalWrite(redPin, HIGH);
    } else if (g > r && g > b) {
      Serial.println("GREEN");
      digitalWrite(greenPin, HIGH);
      digitalWrite(orangePin, LOW);
      digitalWrite(redPin, LOW);
    } else if (b > r && b > g) {
      Serial.println("BLUE");
      digitalWrite(greenPin, LOW);
      digitalWrite(orangePin, HIGH);
      digitalWrite(redPin, LOW);
    } else {
      Serial.println("WTF is dit");
      digitalWrite(greenPin, HIGH);
      digitalWrite(orangePin, HIGH);
      digitalWrite(redPin, HIGH);
    }
  } else {
    Serial.println("Nothing to see here");
    digitalWrite(greenPin, LOW);
    digitalWrite(orangePin, LOW);
    digitalWrite(redPin, HIGH);
  }

  // if (sensorValue > 500) {
  //   digitalWrite(greenPin, LOW);
  //   digitalWrite(orangePin, LOW);
  //   digitalWrite(redPin, HIGH);
  //   delay(2000);
  //   digitalWrite(greenPin, LOW);
  //   digitalWrite(orangePin, HIGH);
  //   digitalWrite(redPin, LOW);
  //   delay(1000);
  //   digitalWrite(greenPin, HIGH);
  //   digitalWrite(orangePin, LOW);
  //   digitalWrite(redPin, LOW);
  //   delay(2000);
  // } else {
  //   digitalWrite(greenPin, LOW);
  //   digitalWrite(redPin, HIGH);
  // }

  // delay(500);
}