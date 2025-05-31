#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Arduino.h>
#include "bme_680.h"

// Reference pressure at sea level (used for altitude calculations if needed)
#define SEALEVELPRESSURE_HPA (1013.25)

// Create an instance of the BME680 sensor
Adafruit_BME680 bme;

// Initializes the BME680 sensor with the desired settings
void iniciarBME_680(void) {
  if (!bme.begin()) {
    Serial.println("❌ BME680 sensor not found!");
    while (1); // Halt if sensor initialization fails
  }

  // Configure oversampling and filter settings
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // Heat the gas sensor to 320°C for 150 ms
}

// Reads data from the BME680 sensor and stores the values in the provided references
void toma_datos_BME680(float &tem, float &hum, float &pres, float &gas) {
  // Attempt to perform a reading
  if (!bme.performReading()) {
    Serial.println("⚠️ BME680 reading failed");
    return;
  }

  // Store values in user-provided variables
  tem = bme.temperature;
  hum = bme.humidity;
  pres = bme.pressure / 100.0;          // Convert Pa to hPa
  gas = bme.gas_resistance / 1000.0;    // Convert Ohms to KOhms
}