/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor
 */
#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int pos = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin(); // initialize the sensor
}

void loop() {
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

    delay(4000);
    lcd.clear();
    lcd.print("It is lovely"); 
    //lcd.write((byte) 0x00);
    //lcd.print(" Daniel ");
    lcd.setCursor(0, 1);
    lcd.print("weather today!");
    delay(1000);
    


  }
}