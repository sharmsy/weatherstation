//Coding and Robotics
//03.23.2023
/*
  Stepper Motor Calibration

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve in one direction when one button is pressed, then
  in the other direction when the other button is pressed.
  
  The steps in one direction will be printed to the LCD screen.

*/

#include <Stepper.h>
#include <LiquidCrystal.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 17;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 13);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int buttonApin = A0;
int buttonBpin = A1;

int stepsPerLoop = 100;
int stepCount = 0;

void setup() {
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP); 
  lcd.setCursor(0, 0);
  lcd.print("Steps: ");
  lcd.setCursor(7, 0);
  lcd.print(stepCount);

}

void loop() {  
  if (digitalRead(buttonApin) == LOW)
  {
    Serial.println("clockwise");
    myStepper.step(stepsPerLoop);
    stepCount = stepCount + stepsPerLoop;
    lcd.setCursor(7, 0);
    lcd.print(stepCount);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerLoop);
  }
}
