// include the library code:
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//For I2C_LCD
//LiquidCrystal_I2C lcd(0x3F,20,4);

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("====skinTesting===");
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  dht.begin();
  
  // Print a message to the LCD.
  lcd.print("Temp:  Humidity:");
}

void loop() {
  delay(500);

  // read humidity
  float h = dht.readHumidity();
  // read temperature in Celsius
  float c = dht.readTemperature();

  if (isnan(h) || isnan(c)) {
    lcd.print("ERROR");
    return;
  }
  // Print to Serial
  String strc = "Temp:";
  String strh = "Humidity";
  String str = strc + c + strh +h;
  Serial.println(str);
  
  // Print to LCD
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(c);
  lcd.setCursor(7,1);
  lcd.print(h);  
}
