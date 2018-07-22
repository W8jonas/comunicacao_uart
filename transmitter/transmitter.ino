
#include "SoftwareSerial.h" 
#include <Ultrasonic.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     5

SoftwareSerial transmissor(2,3); // (RX, TX)
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    
unsigned long dist = 0;
char enviar_ [10] = {0,0,0,0,0,0,0,0,0,0};

void setup() {
  transmissor.begin(300);
  Serial.begin(115200);
}

void loop() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  dist = int (cmMsec * 100) ;

  if (dist > 9999 || dist < 0 ) {
     dist = 0;
  }

  String enviar = String (dist) + ';';
  enviar.toCharArray(enviar_, 10);

  for (int i = 0; i < (enviar.length()); i++){
     transmissor.print(enviar_[i]);
     if (enviar.length()-i == 4) {
        Serial.print(','); 
        transmissor.print(',');
     }
     Serial.print(enviar_[i]);
     delay(100);
  }
  Serial.println(" ");
  delay(100);
}

