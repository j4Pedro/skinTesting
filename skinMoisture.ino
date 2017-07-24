// include the library code:
#include <Wire.h>
#include <Adafruit_Sensor.h>        /* https://github.com/adafruit/Adafruit_Sensor.git */
#include <LiquidCrystal.h>  
//#include <LiquidCrystal_I2C.h>    /* https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/ */
#include "DHT.h"

// set the DHT Pin
#define DHT1PIN 6
#define DHT2PIN 8

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//For I2C_LCD
//LiquidCrystal_I2C lcd(0x3F,20,4);

#define DHT1TYPE DHT11    // DHT 11
#define DHT2TYPE DHT11
//#define DHTTYPE DHT22   // DHT 22 (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht1(DHT1PIN, DHT1TYPE);
DHT dht2(DHT2PIN, DHT2TYPE);

//set Count row
int count = 0;
int ctRow = 0;

void setup() {
  Serial.begin(9600); 
  Serial.println("==skinTesting==");
  
  //setting PLX-DAQ
  Serial.println("CLEARDATA");
  Serial.println("LABEL,TIME,Temperture1,Humidity1,Temperture2,Humidity2");
  
  dht1.begin();
  dht2.begin();
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp:  Humidity:");
}

void loop() {
  delay(500);

  // read humidity
  float h1 = dht1.readHumidity();
  float h2 = dht2.readHumidity();
  // read temperature in Celsius
  float c1 = dht1.readTemperature();
  float c2 = dht2.readTemperature();
  
  //Sensor 1
  if (isnan(h1) || isnan(c1)) {
    Serial.println("Failed to read from Sensor1");
    lcd.print("Error_Sensor1");
    return;
  }else{
  // Print to Serial
  /*
  String strc1 = "Temp1:";
  String strh1 = "Humidity1:";
  String str1 = strc1 + c1 + strh1 +h1;
  Serial.println(str1);
  */
  }
  
  //Sensor 2
  if (isnan(h2) || isnan(c2)) {
    Serial.println("Failed to read from Sensor2");
    lcd.print("Error_Sensor2");
    return;
  }else{
  // Print to Serial
  /*
  String strc2 = "Temp2:";
  String strh2 = "Humidity2:";
  String str2 = strc2 + c2 + strh2 +h2;
  Serial.println(str2);
  */
  }
  //print to excel by PLX-DAQ
  Serial.print("DATA,TIME,");
  Serial.print(",");
  Serial.print(c1);
  Serial.print(",");
  Serial.print(h1);
  Serial.print(",");
  Serial.print(c2);
  Serial.print(",");
  Serial.println(h2);
  // Count row
  ctRow++;
  count++;
  if (ctRow > 360) 
   {
    ctRow=0;
    Serial.println("ROW,SET,2");
   }  
  // Print to LCD
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print((c1+c2)/2);
  lcd.setCursor(7,1);
  lcd.print((h1+h2)/2);
  }
 
