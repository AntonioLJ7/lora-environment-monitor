#include "thinger.h"
#include <Arduino.h>
#include <ThingerESP32.h>
#include <ArduinoJson.h>
#include "LoRaWan_APP.h"
#include "conf_gateway.h"
#include "conf_wifi.h"

// Thinger.io credentials
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// Wi-Fi credentials (redundant here if already used in conf_wifi)
const char* SSID = "";
const char* PASSWORD = "";

bool lora_idle = true;
int periodo_actual = 60;  // Default data acquisition interval (seconds)

/**
 * @brief Registers environmental sensor values to Thinger.io resources.
 * 
 * This function links temperature, humidity, pressure, and gas values
 * to resources that can be read remotely from Thinger.io.
 */
void envioDatosBME680(float t, float h, float p, float g){
  thing.add_wifi(SSID, PASSWORD);

  thing["Temperatura"] >> [=](pson &out){ out = t; };
  thing["Humedad"]     >> [=](pson &out){ out = h; };
  thing["Presion"]     >> [=](pson &out){ out = p; };
  thing["Gas"]         >> [=](pson &out){ out = g; };
}

/**
 * @brief Adds a Thinger.io control to remotely reset the gateway device.
 */
void botonRSTGateway(void){
  thing["RST_Gateway"] << [](pson& activated){
    if (activated) {
      ESP.restart();
    }
  };
}

/**
 * @brief Adds a Thinger.io control to remotely reset the LoRa node.
 * 
 * Sends a LoRa message with the content "RST" to trigger a software reset on the node.
 */
void botonRSTNodo(void){
  thing["RST_Nodo"] << [](pson& activated){
    if (activated) {
      Serial.println("🔁 RST_Nodo button activated → Sending LoRa reset command to node...");

      const char* rstMessage = "RST";
      Radio.Send((uint8_t *)rstMessage, strlen(rstMessage));
      delay(1000);  // Allow time for sending

      Radio.Rx(0);  // Return to RX mode
    }
  };
}

/**
 * @brief Adds a Thinger.io control to set and display the data acquisition interval.
 * 
 * This resource acts as a slider on the dashboard to send a new sampling period to the node.
 */
void tiempo_adquisicion_datosBME680(void){
  thing["tiempoBME"] << [](pson &in){
    if (in.is_empty()) {
      // Dashboard request to show current value
      in = periodo_actual;
    } else {
      // User has changed the slider value
      periodo_actual = in;
      Serial.printf("🕒 New period received: %d\n", periodo_actual);

      String msg = "PERIODO=" + String(periodo_actual);
      Radio.Send((uint8_t *)msg.c_str(), msg.length());
      delay(100);

      Radio.Rx(0);  // Return to listening mode
    }
  };
}

/**
 * @brief Handles Thinger.io connection and events in the main loop.
 */
void continuarthinger(void){
  thing.handle();
}
