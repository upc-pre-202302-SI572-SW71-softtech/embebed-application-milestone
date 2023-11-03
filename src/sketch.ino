#include "lib.h"

#define DHTPIN 33
#define DHTTYPE DHT22

#define PINLED  26
#define PINMOTION  25
#define PINTEMPERATURE  33
// Defining the WiFi channel speeds up the connection:
#define WIFI_CHANNEL 6

// URL to send data
const String url  = "";
// API key
const String apiKey = "";


HTTPClient http;

// Initialize DHT object with DHTTYPE and DHTPIN
DHT dhtObject(DHTPIN, DHTTYPE) ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PINLED, OUTPUT);
  pinMode(PINMOTION, INPUT_PULLUP);
  pinMode(PINTEMPERATURE, INPUT);

  // Connect to WiFi network
  WiFi.begin(SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize DHT sensor.
  dhtObject.begin();
}

void loop() {
  Serial.println(WiFi.status());
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost");
    return;
  }
  else {
    Serial.println("WiFi connection is OK");
    //http.begin(url);
    // Send HTTP GET request
    /*int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) {
      StaticJsonDocument<768> doc;
      DeserializationError error = deserializeJson(doc, http.getString());
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        delay(2500);
        return;
      }

      Serial.print("HTTP Response: ");
      Serial.println(httpCode);
    }*/
  }
  
  // 2. Read data from sensor
  // 3. Send data to server
  int statusSns1 = digitalRead(PINMOTION);
  int tmpValue = analogRead(PINTEMPERATURE);

  if (statusSns1 == HIGH) {
    digitalWrite(PINLED, HIGH);
  } else {
    digitalWrite(PINLED, LOW);
  }

  float Humidity = dhtObject.readHumidity();
  float Temperature = dhtObject.readTemperature();

  /*
  Serial.println("Temperature:");
  Serial.print(Temperature) ;
  Serial.print("degrees celsius, ");

  Serial.println("Humidity:");
  Serial.print(Humidity);
  Serial.print("%.");
   */ 
  delay(5000);
}
