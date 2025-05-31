#include "conf_wifi.h"        // Wi-Fi configuration and initialization
#include "conf_gateway.h"     // Gateway-specific logic and control
#include "thinger.h"          // Thinger.io integration
#include "LoRaWan_APP.h"      // LoRaWAN stack for Heltec board

/**
 * @brief Setup function for the LoRa gateway node.
 * 
 * Initializes serial communication, the LoRa module, Wi-Fi connection,
 * and gateway-specific functionality such as reset buttons and data acquisition.
 */
void setup() {
  Serial.begin(115200);

  // Initialize Heltec board with slow clock
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  // Initialize LoRa radio
  iniciarLoRa();

  // Connect to Wi-Fi network
  iniciarWifi();

  // Check for manual reset of the gateway
  botonRSTGateway();

  // Check for remote reset command for the remote node
  botonRSTNodo();

  // Start the loop that checks for incoming BME680 packets
  tiempo_adquisicion_datosBME680();
}

/**
 * @brief Main loop for the LoRa gateway.
 * 
 * Maintains connection with Thinger.io and listens for incoming LoRa packets continuously.
 */
void loop() {
  // Keep Thinger.io connection alive and handle resources
  continuarthinger();

  // Keep LoRa receiver active
  mantenerRecepcion();
}