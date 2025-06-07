# 🌐📊 Smart Age Predictor using WiFi + LCD + API Integration

This project uses an **ESP32** microcontroller to connect to WiFi, fetch age predictions from the [Agify API](https://agify.io), and display the name and predicted age on a 16x2 I2C LCD screen.

---

## 🛠️ Hardware Components

- ESP32 Development Board  
- I2C 16x2 LCD Display (I2C address `0x27`) 
- Micro USB Cable  
- WiFi Connection (Tested on Wokwi Emulator)

---

## 📦 Libraries Used

- `WiFi.h` – Connects ESP32 to WiFi  
- `HTTPClient.h` – Makes HTTP requests to external APIs  
- `LiquidCrystal_I2C.h` – Interfaces with the LCD  
- `ArduinoJson.h` – Parses the JSON response from the API

Install libraries using the Arduino Library Manager if needed.

---

## 🔌 LCD Pin Connection (ESP32)

| LCD Pin | ESP32 Pin |
|---------|-----------|
| SDA     | GPIO 21   |
| SCL     | GPIO 22   |
| VCC     | 3.3V/5V   |
| GND     | GND       |

---

## 🚀 How It Works

1. ESP32 connects to the WiFi network.
2. Sends an HTTP GET request to the Agify API with a fixed name (e.g., `Pritha`).
3. Parses the JSON response to extract the name and predicted age.
4. Displays the results on the 16x2 I2C LCD.
5. Repeats every 10 seconds.

---


