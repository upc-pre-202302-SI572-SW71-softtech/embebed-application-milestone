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
  }
  
  // Read data from DHT sensor
  float humidity = dhtObject.readHumidity();
  float temperature = dhtObject.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Now you can send this to your backend
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://localhost:8106/api/devices/param"); // Endpoint
    http.addHeader("Content-Type", "application/json");
    
    // Prepare your JSON payload
    String jsonPayload = "{\"humidity\":\"" + String(humidity) + "\", \"temperature\":\"" + String(temperature) + "\"}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode);   // Print return code
      Serial.println(response);           // Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Free resources
  }

  delay(5000); // Wait for 5 seconds before sending again
}
