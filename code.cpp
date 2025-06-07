#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

// LCD Setup (I2C address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C LCD(0x27, 16, 2);

// WiFi Credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// API Endpoint (Agify API)
const char* apiURL = "https://api.agify.io/?name=Pritha";

void setup() {
  Serial.begin(115200);
  
  // Initialize LCD
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Connecting WiFi");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("WiFi Connected");
  delay(1000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(apiURL);
    
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);

      // Parse JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);
      
      if (!error) {
        const char* name = doc["name"];
        int age = doc["age"];

        // Show on LCD
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Name: ");
        LCD.print(name);
        LCD.setCursor(0, 1);
        LCD.print("Age: ");
        LCD.print(age);

        Serial.printf("Name: %s, Age: %d\n", name, age);
      } else {
        Serial.println("JSON Parse Error!");
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Parse Error!");
      }
    } else {
      Serial.print("HTTP Error: ");
      Serial.println(httpCode);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("HTTP Failed");
    }
    
    http.end();
  } else {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("WiFi Lost");
  }

  delay(10000);  // Wait 10 seconds before next request
}
