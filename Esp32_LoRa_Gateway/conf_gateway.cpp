#include "conf_gateway.h"
#include "LoRaWan_APP.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "thinger.h"

// Global variables to store sensor values
float temperature = 0.0;
float humidity = 0.0;
float pressure = 0.0;
float gas = 0.0;

// LoRa radio event handlers
static RadioEvents_t RadioEvents;

/**
 * @brief Initializes the LoRa module in RX mode.
 * 
 * Sets up LoRa reception parameters and prepares the device to receive packets indefinitely.
 */
void iniciarLoRa(void) {
  Serial.println("\n🚀 Starting LoRa...");

  // Assign callback functions for RX and TX events
  RadioEvents.RxDone = OnRxDone;
  RadioEvents.TxDone = OnTxDone;

  // Initialize radio and configure RX settings
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

  Serial.println("📡 Gateway in RX mode (listening for packets)");

  // Start receiving with no timeout
  Radio.Rx(0);
}

/**
 * @brief Callback triggered when a LoRa packet is received.
 * 
 * Parses the incoming JSON-formatted payload and extracts environmental data,
 * then sends it to Thinger.io.
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  Serial.println("\n📥 Packet received!");

  // Convert payload to null-terminated string
  char rxpacket[size + 1];
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';

  Serial.printf("📨 Received message: \"%s\", RSSI: %d, Size: %d, SNR: %d\n", rxpacket, rssi, size, snr);

  // Parse the JSON payload
  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, rxpacket);

  if (error) {
    Serial.print("❌ JSON parse error: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract sensor values
  temperature = doc["temp"];
  humidity = doc["hum"];
  pressure = doc["pres"];
  gas = doc["gas"];

  Serial.printf("🌡️ Temp: %.2f°C, 💧 Hum: %.2f%%, ⬇️ Pressure: %.2f hPa, 🧪 Gas: %.2f KOhm\n",
                temperature, humidity, pressure, gas);

  // Send data to Thinger.io
  envioDatosBME680(temperature, humidity, pressure, gas);

  // Return to RX mode
  Radio.Rx(0);
}

/**
 * @brief Callback when a LoRa transmission completes.
 */
void OnTxDone() {
  Serial.println("✅ TX complete");
  lora_idle = true;
}

/**
 * @brief Keeps LoRa interrupts active for RX/TX processing.
 */
void mantenerRecepcion(void) {
  Radio.IrqProcess();
}