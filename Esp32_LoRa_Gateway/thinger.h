#ifndef _THINGER_H_
#define _THINGER_H_

/**
 * @file thinger.h
 * @brief Thinger.io integration for the LoRa gateway node.
 * 
 * This header defines the credentials and interface functions required to 
 * connect the ESP32 to Thinger.io, expose sensor data, and control the node remotely.
 */

// 📡 Thinger.io device credentials (replace with your actual values)
#define USERNAME ""              ///< Your Thinger.io username
#define DEVICE_ID ""            ///< Device ID registered in Thinger.io
#define DEVICE_CREDENTIAL ""    ///< Device credential token

/**
 * @brief Sends environmental sensor data to Thinger.io.
 * 
 * Registers temperature, humidity, pressure, and gas values as readable resources.
 * 
 * @param t Temperature in °C
 * @param h Humidity in %
 * @param p Pressure in hPa
 * @param g Gas resistance in KOhms
 */
void envioDatosBME680(float t, float h, float p, float g);

/**
 * @brief Creates a Thinger.io control button to remotely reset the LoRa node.
 * 
 * Sends an "RST" message over LoRa when activated.
 */
void botonRSTNodo(void);

/**
 * @brief Creates a Thinger.io control button to reboot the gateway itself.
 */
void botonRSTGateway(void);

/**
 * @brief Creates a slider or input in Thinger.io to update the node’s sampling interval.
 * 
 * Sends a LoRa command with the new period (in seconds) to the node.
 */
void tiempo_adquisicion_datosBME680(void);

/**
 * @brief Handles Thinger.io communication in the main loop.
 */
void continuarthinger(void);

// Global flag indicating LoRa availability
extern bool lora_idle;

#endif // _THINGER_H_