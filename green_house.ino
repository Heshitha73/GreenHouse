#define BLYNK_TEMPLATE_ID "TMPL6Y3UcVOdp"
#define BLYNK_TEMPLATE_NAME "Greenhouse automated system"
#define BLYNK_AUTH_TOKEN "YPfxWW-4zvOHOGenSTLn0ljY8lzaBRAa"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
// Wi-Fi credentials
char ssid[] = "Pixel 6";
char pass[] = "20047312345";

// Sensor and relay pins
#define SOIL_MOISTURE_PIN 34  // Analog pin for soil moisture sensor
#define TEMPERATURE_PIN 33   // Analog pin for temperature sensor
#define RELAY_WATER_PIN 26   // Digital pin for water pump relay
#define RELAY_FAN_PIN 27     // Digital pin for fan relay
#define RELAY_BULB_PIN 25    // Digital pin for bulb relay
#define DHTTYPE DHT11
DHT dht(TEMPERATURE_PIN, DHTTYPE);
// Thresholds
#define MOISTURE_THRESHOLD 3500   // Soil moisture threshold (adjustable)
#define TEMP_FAN_THRESHOLD 35.0  // Temperature for fan to turn on (Celsius)
#define TEMP_BULB_THRESHOLD 31.0 // Temperature for bulb to turn on (Celsius)

// Blynk virtual pins
#define VPIN_SOIL_MOISTURE V1
#define VPIN_TEMPERATURE V2

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  dht.begin();
  // Pin configurations
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TEMPERATURE_PIN, INPUT);
  pinMode(RELAY_WATER_PIN, OUTPUT);
  pinMode(RELAY_FAN_PIN, OUTPUT);
  pinMode(RELAY_BULB_PIN, OUTPUT);

  digitalWrite(RELAY_WATER_PIN, HIGH);
  digitalWrite(RELAY_FAN_PIN, HIGH);
  digitalWrite(RELAY_BULB_PIN, HIGH);

  // Blynk setup
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer setup
  timer.setInterval(1000L, monitorSensors); // Monitor sensors every 5 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}

// Function to monitor sensors and control relays
void monitorSensors() {
  // Read soil moisture
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  Blynk.virtualWrite(VPIN_SOIL_MOISTURE, soilMoistureValue);

  // Control water relay
  if (soilMoistureValue > MOISTURE_THRESHOLD) {
    Serial.println("Soil is dry. Turning on water pump...");
    digitalWrite(RELAY_WATER_PIN, LOW);
    delay(3000); // Water for 5 seconds
    digitalWrite(RELAY_WATER_PIN, HIGH);
    Serial.println("Watering complete.");
  } else {
    Serial.println("Soil is moist. No watering needed.");
  }

  // Read temperature
  float temperatureC = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperatureC);

  // Control fan and bulb relays
  if (temperatureC > TEMP_FAN_THRESHOLD) {
    Serial.println("Temperature is high. Turning on fan...");
    digitalWrite(RELAY_FAN_PIN, LOW);
    digitalWrite(RELAY_BULB_PIN, HIGH); // Ensure bulb is off
  } else if (temperatureC < TEMP_BULB_THRESHOLD) {
    Serial.println("Temperature is low. Turning on bulb...");
    digitalWrite(RELAY_BULB_PIN, LOW);
    digitalWrite(RELAY_FAN_PIN, HIGH); // Ensure fan is off
  } else {
    Serial.println("Temperature is normal. Fan and bulb are off.");
    digitalWrite(RELAY_FAN_PIN, HIGH);
    digitalWrite(RELAY_BULB_PIN, HIGH);
  }
}
