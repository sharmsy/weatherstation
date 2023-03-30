/*
 * Use this template to calibrate your thermometer to zero
 *
 * Then follow along in class to add the code to control the stepper motor
 * so the thermometer displays the correct temperature.
 * 
 */
#include "DHT.h"
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 13);
Servo myservo;  // create servo object to control a servo
int pos = 0;

int stepCount = 0;
int stepsPerLoop = 100;
int lastStepsPos = 0;
int moveSteps = 0;
int buttonApin = A0;
int buttonBpin = A1;

void setup() {
  myStepper.setSpeed(rolePerMinute);
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin(); // initialize the sensor
  myservo.attach(3,400,1200);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP); 
  lcd.setCursor(0, 0);
  lcd.print("Use buttons to");
  lcd.setCursor(0, 1);
  lcd.print("Move to 0F");
  delay(3000);
  while((digitalRead(buttonApin) == HIGH) || (digitalRead(buttonBpin) == HIGH)) //the program will continue to run this loop until both buttons are pressed.
  {
    if (digitalRead(buttonApin) == LOW) //moves the stepper motor one direction when one of the buttons is pressed
    {
      Serial.println("clockwise");
      myStepper.step(-stepsPerLoop);
    }
    if (digitalRead(buttonBpin) == LOW) //moves the stepper motor the other direction when the other button is pressed
    {
      Serial.println("counterclockwise");
      myStepper.step(stepsPerLoop);
    }
      lcd.setCursor(0, 0);
      lcd.print("Then press both");
      lcd.setCursor(0, 1);
      lcd.print("to continue");
  }
}

void loop() {
    // attaches the servo on pin 9 to the servo object
  // wait a few seconds between measurements.
  
  delay(2000);
  // read humidity
  int humi  = dht.readHumidity();
  // read temperature as Celsius
  int tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);
  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");
    Serial.print("  |  "); 
    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.println("F");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(humi);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempF);
    lcd.println("F    ");

    pos = (180-map(humi,0,100,0,180)); //converts the humidity value to the corresponding postion value on the servo dial, and saves that value to the pos variable
    Serial.print("Position is:");
    Serial.println(pos);
    myservo.write(pos); //instructs the servo motor to move to the angle equal to the value of the pos variable

    delay(4000);
    lcd.clear();
    lcd.print("It is lovely"); 
    lcd.setCursor(0, 1);
    lcd.print("weather today!");
    delay(1000);
  }
}