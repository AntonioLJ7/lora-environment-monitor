#ifndef _BME_680_H_
#define _BME_680_H_

/**
 * @brief Initializes the BME680 environmental sensor with predefined settings.
 * 
 * This function sets up the sensor for temperature, humidity, pressure, and gas resistance measurements,
 * including oversampling and gas heater parameters.
 */
void iniciarBME_680(void);

/**
 * @brief Reads the latest values from the BME680 sensor.
 * 
 * This function retrieves the temperature (°C), humidity (%), pressure (hPa), and gas resistance (KOhms),
 * and stores the results in the provided reference variables.
 * 
 * @param tem Reference to float where the temperature will be stored
 * @param hum Reference to float where the humidity will be stored
 * @param pres Reference to float where the pressure will be stored
 * @param gas Reference to float where the gas resistance will be stored
 */
void toma_datos_BME680(float &tem, float &hum, float &pres, float &gas);

#endif // _BME_680_H_