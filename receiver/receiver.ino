
#include "SoftwareSerial.h"
#include <LiquidCrystal.h>

#define ledPin 13
#define rs 12
#define en 11
#define d4 10
#define d5 9
#define d6 8
#define d7 7

SoftwareSerial receptor(2,3); // (RX, TX)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char buffer_recebido [10] = {0};
String dado = "0";
int i = 0;

void setup() {
   lcd.begin(16, 20);
   receptor.begin(300); 
   pinMode(ledPin, OUTPUT);
   Serial.begin(115200);
   
}

void loop() {

   if (receptor.available() > 0){
      char received = receptor.read();
      if ( received == ';' ) {
         Serial.println(dado);
         lcd.clear();
         lcd.print("Distancia objeto");
         lcd.setCursor(0, 1);
         lcd.print(dado);
         lcd.print(" em cm.");
         dado = " ";
      } else {
         dado += received;
      }
      
   }
   
}  // fim loop

