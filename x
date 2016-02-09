#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DeviceAddress termpiec = { 0x28, 0x7D, 0x9A, 0xDB, 0x06, 0x00, 0x00, 0x82 };
DeviceAddress termbojl = { 0x28, 0x85, 0x6E, 0xDB, 0x06, 0x00, 0x00, 0xE8 };
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x38, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);  // Set the LCD I2C address
void setup(void)
{
    // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(termpiec, 10);
  sensors.setResolution(termbojl, 10);
 // sensors.setResolution(dogHouseThermometer, 10);
  // start serial port
//  Serial.begin(9600);
//  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  //sensors.begin();
   lcd.begin(16,2);
    lcd.backlight(); 
  lcd.clear();
  lcd.setCursor(0,0);
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("bladd odcz. temp ");
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("nie masz muzgu"); 
    
  } else {
    if (tempC > 84.00) {
    Serial.print("duza t ");
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("muzg przegrz"); 
    
  } else {
     if (26.00 > tempC > 28.00) {
    Serial.print("zacz ");
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("muzg grzeje") ; 
      
      } else {
     if (29.00 > tempC > 32.00) {
   // Serial.print("zacz ");
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("muzg wybuchnie"); 
    
    
   } else {
    
     // Serial.print("C: ");
    Serial.print(tempC);
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print(tempC);
    //Serial.print(" F: ");
  //  Serial.print(DallasTemperature::toFahrenheit(tempC));
  }
}}
  }}
void loop(void)
{

 // sensors.requestTemperatures(); // Send the command to get temperatures 
 // Serial.print("Temperature for the device 1 (index 0) is: ");
  //float x=sensors.getTempCByIndex(0);
//  Serial.println(x);  
   lcd.setCursor(0,0);
    lcd.print("Temp. muzgu: "); 
    //  lcd.setCursor(0,1);
   //   lcd.print("          ");
      //  lcd.setCursor(0,1); 
    //lcd.print(x);
        delay(2000);
  Serial.print("Pobieranie Temperatury...\n\r");
  sensors.requestTemperatures();
  
  Serial.print("temp. pieca: ");
  //printTemperature(termpiec);
  Serial.print("\n\r");
  Serial.print("temp bojler: ");
//  lcd.print(tempC);
  printTemperature(termbojl);
  Serial.print("\n\r");
  
  
   
 
  
}
