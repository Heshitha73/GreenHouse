# 🌿 Greenhouse Automated System — ESP32 + Blynk IoT
An intelligent greenhouse monitoring and control system built with ESP32, DHT11 sensor, and the Blynk IoT platform — enabling real-time remote monitoring and fully automated plant care.

---

## 🔧 What It Does
This system continuously reads environmental data and automatically controls actuators to maintain ideal growing conditions:
- When soil moisture too dry (>3500)      💧 Water pump activates for 3 seconds.
- When temperature too high (>35°C)       🌀 Cooling fan turns ON
- When temperature too low (<31°C)        💡 Heating bulb turns ON
- When temperature normal                 ✅ All actuators OFF

---

## 📡 Tech Stack

Hardware: ESP32 microcontroller, DHT11 temperature & humidity sensor, soil moisture sensor, 3-channel relay module (water pump, fan, bulb)
Platform: Blynk IoT — for real-time remote dashboard and virtual pin data streaming
Language: C++ / Arduino Framework
Connectivity: Wi-Fi (ESP32 built-in)

---

## 🚀 Features

✅ Automated irrigation — waters plants only when soil is dry
✅ Temperature regulation — switches between fan and heating bulb based on thresholds
✅ Real-time monitoring — sensor data streamed to Blynk dashboard every second
✅ Remote visibility — monitor your greenhouse from anywhere via the Blynk mobile app

---

## ⚠️ Security Note

Before pushing to GitHub, make sure to remove or hide your Wi-Fi credentials and Blynk Auth Token — store them in a separate config file or use environment variables.
