#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
///eeprom/////////////////////
#include <EEPROM.h>
/////klawiat///////////////////////////////////////
#include <Keypad.h>
 float usttemp = 40 ;
volatile int zmiana=0;       // zmienna pomocnicza, do obslugi klawiszy
long time0, time1;           // interfały czasowe do obsługi LCD
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows] = {7,6,5,4}; //Rows 0 to 3
byte colPins[numCols]= {3,2,1,0}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
#define GORA 12
//#define DOL 12
//////////////////////////////////////////////////////////////////////
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DeviceAddress termpiec = { 0x28, 0x7D, 0x9A, 0xDB, 0x06, 0x00, 0x00, 0x82 };
DeviceAddress termbojl = { 0x28, 0x85, 0x6E, 0xDB, 0x06, 0x00, 0x00, 0xE8 };
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x38, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);  // Set the LCD I2C address
void setup(void)
{
   usttemp=EEPROM.read(0);
  //int czyt = EEPROM.read(1);
//int odczytaj;
//odczytaj = EEPROM.read(1);
     pinMode(GORA, OUTPUT);
//  pinMode(DOL, OUTPUT);
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(termpiec, 10);
  sensors.setResolution(termbojl, 10);

   lcd.begin(16,2);
    lcd.backlight(); 
  lcd.clear();
  lcd.setCursor(0,0);
//  float czyt odczytaj;
  
}

void loop(void)
{
//  float czyt =  EEPROM.read();
    ////////////////////klawiat///
  char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY)
{
   switch(keypressed)
    {
            case '1':
       usttemp--;if(usttemp<8)usttemp=8;EEPROM.write(0,usttemp);
       lcd.clear();
       Serial.print(usttemp);
      lcd.setCursor(0,0); 
      lcd.print("Ustaw temp");
      lcd.setCursor(0,1);
      lcd.print(usttemp);
          delay(10);
      lcd.clear();
      
      break;
     

      
      case '2':
    // float  usttemp = usttemp+3;
      //usttemp++;
        usttemp++;if(usttemp>75)usttemp=75;EEPROM.write(0,usttemp);
               lcd.clear();
       
      lcd.setCursor(0,0); 
      lcd.print("Ustaw temp");
      lcd.setCursor(0,1);
      lcd.print(usttemp);
         // delay(500);
      lcd.clear();
 // LCD_linia2();  // aktualizuję temperaturę na wyswietlaczu
 delay(10);

      break;
      case '7':
      EEPROM.write(0,usttemp);
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Zapisano");
      lcd.setCursor(0,1);
      lcd.print(usttemp);
      delay(5000);
      lcd.clear();
      break;
      case '4':
      digitalWrite(GORA, LOW);
      break;
      
     
      case '5':
      digitalWrite(GORA, HIGH);
      break;
        
    

     
   
      
    
    }

}////////////klawiat........

   sensors.requestTemperatures();
  float piec =  sensors.getTempC(termpiec);
  float bojl =  sensors.getTempC(termbojl);
  ////////////////////////
    if (piec == -127,00) {
   digitalWrite(GORA, HIGH);
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("blad oczytu p"); 
    }
        if (bojl > 70,00) {
   digitalWrite(GORA, HIGH);
     lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print("blad oczytu b"); 
    }
    else
  if (bojl > piec)
  {      
      digitalWrite(GORA, HIGH);
  }
  else     
  if (piec > usttemp+3)
{
   digitalWrite(GORA, LOW);
   //digitalWrite(DOL, LOW);

}
    if (piec < usttemp-3)
{
   digitalWrite(GORA, HIGH);
  // digitalWrite(DOL, HIGH);

//Serial.print(keypressed);
 }//////



// Serial.print(piec);
   lcd.setCursor(0,0);
    lcd.print("piec:   boj: u"); 
    lcd.print(usttemp);
      lcd.setCursor(0,1);
      lcd.print("           ");
        lcd.setCursor(0,1); 
    lcd.print(piec); 
    //lcd.print(usttemp);  
    lcd.print("   ");
    lcd.print(bojl);   
    lcd.print("       "); 
 
    
        delay(200);

}
