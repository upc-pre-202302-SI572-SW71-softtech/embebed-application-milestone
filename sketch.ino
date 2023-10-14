#include "DHT.h"

 #define DHTPIN 33

 #define DHTTYPE DHT22

int pinLed1 = 26;
int pinSns1 = 25;
int pinTmp1 = 33;

DHT dhtObject(DHTPIN, DHTTYPE) ;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinSns1, INPUT_PULLUP);
  pinMode(pinTmp1, INPUT);
  dhtObject.begin();
}

void loop() {
  int statusSns1 = digitalRead(pinSns1);
  int tmpValue = analogRead(pinTmp1);
  if (statusSns1 == HIGH) {
    digitalWrite(pinLed1, HIGH);
  } else {
    digitalWrite(pinLed1, LOW);
  }

  float Humidity = dhtObject.readHumidity();
  float Temperature = dhtObject.readTemperature();


  Serial.println("Temperature:");
  Serial.print(Temperature) ;
  Serial.print("degrees celsius, ");

  Serial.println("Humidity:");
  Serial.print(Humidity);
  Serial.print("%.");
    
  delay(1000);
}
