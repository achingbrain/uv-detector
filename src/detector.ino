#import <Arduino.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int SELECT = 0;
int UP = 1;
int RIGHT = 2;
int DOWN = 3;
int LEFT = 4;

//Hardware pin definitions
int UVINPUT = A1; //Output from the sensor
int REF_3V3 = A2; //3.3V power on the Arduino board
int lastButton = -1;
int page = 0;

void setup () {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // set up pins
  pinMode(UVINPUT, INPUT);
  pinMode(REF_3V3, INPUT);
}

void switchPage () {
  lcd.clear();
  page = page == 0 ? 1 : 0;
}

void loop () {
  int button = analogRead(A0);

  if (button < 60) {
    if (lastButton != RIGHT) {
      switchPage();
    }

    lastButton = RIGHT;
  } else if (button < 200) {
    if (lastButton != UP) {
      switchPage();
    }

    lastButton = UP;
  } else if (button < 400){
    if (lastButton != DOWN) {
      switchPage();
    }

    lastButton = DOWN;
  } else if (button < 600){
    if (lastButton != LEFT) {
      switchPage();
    }

    lastButton = LEFT;
  } else if (button < 800){
    if (lastButton != SELECT) {
      switchPage();
    }

    lastButton = SELECT;
  } else {
    lastButton = -1;
  }

  int uvLevel = averageAnalogRead(UVINPUT);
  int refLevel = averageAnalogRead(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level

  if (page == 1) {
    lcd.setCursor(0,0);
    lcd.print("Ref: ");
    lcd.print(refLevel);

    lcd.setCursor(0,1);
    lcd.print("Voltage: ");
    lcd.print(outputVoltage);
  } else {
    lcd.setCursor(0,0);
    lcd.print("UV level: ");
    lcd.print(uvLevel);

    lcd.setCursor(0,1);
    lcd.print("UV: ");
    lcd.print(uvIntensity);
  }

  delay(100);
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for(int x = 0 ; x < numberOfReadings ; x++) {
    runningValue += analogRead(pinToRead);
  }

  runningValue /= numberOfReadings;

  return runningValue;
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
