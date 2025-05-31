# lora-environment-monitor
LoRa-based environmental monitoring system with ESP32, BME680 and Thinger.io.
LoRa Environmental Monitoring System (ESP32 + BME680 + Thinger.io)

This project is a wireless environmental monitoring system using two Heltec ESP32 LoRa boards:

One board acts as a sensor node: it collects environmental data (temperature, humidity, pressure, gas resistance) using a BME680 sensor and sends it via LoRa.

The other board is the gateway: it receives data via LoRa and forwards it to Thinger.io, a cloud IoT platform for visualization and control.

:satellite: Architecture Overview

[BME680 Sensor] --> [ESP32 Node + LCD] --LoRa--> [ESP32 Gateway] --WiFi--> [Thinger.io Dashboard]

:wrench: Requirements

Hardware:

2x Heltec ESP32 LoRa V3 (or compatible SX1262-based boards)

1x BME680 sensor (I2C)

1x LCD 16x4 with I2C interface

Software:

Arduino IDE

PlatformIO (optional, for advanced users)

Libraries:

LoRaWan_APP (included with Heltec board support)

Adafruit_BME680

LiquidCrystal_I2C

ArduinoJson

ThingerESP32

:gear: How It Works

Node:

Initializes BME680 and LCD

Measures environmental data every 60 seconds (default, configurable via LoRa)

Displays values on LCD

Sends a JSON string via LoRa: { "temp": 23.5, "hum": 45.0, "pres": 1013.0, "gas": 9.5 }

Gateway:

Listens for incoming LoRa packets

Parses JSON and sends data to Thinger.io

Provides controls in the dashboard:

RST_Nodo: remotely resets the node

RST_Gateway: reboots the gateway

tiempoBME: sets the sampling interval of the node

:computer: Thinger.io Setup

Create an account on Thinger.io

Create a new device:

ID: LoRa_Gateway

Credentials: generate and copy the token

Use these in thinger.h:

#define USERNAME "your_user"
#define DEVICE_ID "LoRa_Gateway"
#define DEVICE_CREDENTIAL "your_token"

Define resources:

Temperatura, Humedad, Presion, Gas

tiempoBME (input/output integer)

RST_Nodo (boolean input)

RST_Gateway (boolean input)

:rocket: Upload and Run

For the Node:

Upload the code with bme_680.cpp, lcd.cpp, and Conf_LoRa.h

Ensure the sensor is connected properly (I2C)

Connect LCD to SDA=6, SCL=7 (Heltec default)

For the Gateway:

Upload the code with conf_gateway.cpp, thinger.cpp, conf_wifi.cpp

Make sure the gateway is near a WiFi access point

Use the same LoRa settings as the node

:file_folder: Repository Structure

/src
├── node/
│   ├── main.cpp
│   ├── bme_680.cpp/h
│   ├── lcd.cpp/h
│   └── Conf_LoRa.h
├── gateway/
│   ├── main.cpp
│   ├── conf_gateway.cpp/h
│   ├── conf_wifi.cpp/h
│   ├── thinger.cpp/h
└── README.md

:copyright: License

MIT License

Author: AntonioLJ17
