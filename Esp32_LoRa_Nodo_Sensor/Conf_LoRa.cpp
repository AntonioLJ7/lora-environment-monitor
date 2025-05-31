#include "Conf_LoRa.h"          // LoRa configuration parameters
#include "LoRaWan_APP.h"        // LoRaWAN stack for the Heltec board
#include <Arduino.h>
#include <ArduinoJson.h>        // Used for creating JSON strings
#include "bme_680.h"            // Sensor functions

char txpacket[BUFFER_SIZE];     // Buffer for outgoing packet
char rxpacket[BUFFER_SIZE];     // Buffer for incoming packet

int tiempo_muestreo = 60;       // Default sampling time in seconds

static RadioEvents_t RadioEvents; // Structure for assigning radio callbacks
bool lora_idle = true;           // Indicates if LoRa is ready to transmit

// Initialize the LoRa radio with transmission and reception settings
void iniciarLoRa(void){
  RadioEvents.TxDone = OnTxDone;
  RadioEvents.TxTimeout = OnTxTimeout;
  RadioEvents.RxDone = OnRxDone;

  Radio.Init(&RadioEvents);

  Radio.SetChannel(RF_FREQUENCY);

  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000); 
}

// Compose and send sensor data packet via LoRa
void envioPaquetes(float tem, float hum, float pres, float gas){
  if (lora_idle) {
    // Create JSON string with environmental data
    sprintf(txpacket, "{\"temp\":%.2f,\"hum\":%.2f,\"pres\":%.2f,\"gas\":%.2f}", tem, hum, pres, gas);

    Serial.printf("\r\nSending packet \"%s\", length %d\r\n", txpacket, strlen(txpacket));

    // Send the packet through LoRa
    Radio.Send((uint8_t *)txpacket, strlen(txpacket));

    // LoRa is now busy
    lora_idle = false;
  }
}

// Callback when a packet is received
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  Serial.println("\n📥 Packet received!");
  
  // Copy payload into local buffer and null-terminate
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';

  String msg = String(rxpacket);

  // Check if the message is to update the sampling period
  if (msg.startsWith("PERIODO=")) {
    int nuevo_periodo = msg.substring(8).toInt();
    if (nuevo_periodo > 0) {
      tiempo_muestreo = nuevo_periodo;
      Serial.printf("⏱️ New sampling period: %d seconds\n", tiempo_muestreo);
    }
  }

  // Check if the message is a reset command
  if (msg == "RST") {
    Serial.println("🔁 RST command received. Rebooting...");
    delay(100);  // Allow time for serial output
    ESP.restart();
  }

  // Re-enable reception mode after handling packet
  Serial.println("🔁 Listening reactivated after reception.");
  Radio.Rx(0);  // Start listening with no timeout
}

// Callback when transmission times out
void OnTxTimeout(void) {
  Radio.Sleep();
  Serial.println("⚠️ TX Timeout...");
  lora_idle = true;
}

// Callback when transmission is completed successfully
void OnTxDone(void) {
  Serial.println("✅ TX complete");
  lora_idle = true;

  // Switch to indefinite reception mode
  Serial.println("👂 Node is now listening for packets...");
  Radio.Rx(0);
}
