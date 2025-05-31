#include "LoRaWan_APP.h"     // LoRaWAN stack for the Heltec board
#include "Arduino.h"         // Core Arduino library
#include "lcd.h"             // LCD display control functions
#include "bme_680.h"         // BME680 sensor control functions
#include "Conf_LoRa.h"       // Custom configuration for LoRa parameters

// Environmental sensor variables
float tem = 0.0;
float hum = 0.0;
float pres = 0.0;
float gas = 0.0;

// Last timestamp when data was sent
unsigned long ultimo_envio = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize LCD and sensor
  iniciarLCD();
  iniciarBME_680();

  // Initialize the Heltec board with LoRa and slow clock configuration
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  // Configure LoRa settings
  iniciarLoRa();

  // Take the first measurement and show it on the LCD
  toma_datos_BME680(tem, hum, pres, gas);
  visualizarDatos_BME680_LCD(tem, hum, pres, gas);

  // Send the first data packet via LoRa
  envioPaquetes(tem, hum, pres, gas);
}

void loop() {
  // Check whether it is time to take a new measurement and send data
  controlarMuestreo();

  // Handle LoRa-related interrupts (non-blocking)
  Radio.IrqProcess();
}

// Check sampling interval and send data if needed
void controlarMuestreo() {
  unsigned long ahora = millis();

  // Check if the sampling interval has passed and LoRa is idle
  if (ahora - ultimo_envio >= tiempo_muestreo * 1000UL && lora_idle) {
    // Take sensor readings
    toma_datos_BME680(tem, hum, pres, gas);

    // Update values on the LCD display
    visualizarDatos_BME680_LCD(tem, hum, pres, gas);

    // Send readings via LoRa
    envioPaquetes(tem, hum, pres, gas);

    // Update timestamp
    ultimo_envio = ahora;
  }
}
