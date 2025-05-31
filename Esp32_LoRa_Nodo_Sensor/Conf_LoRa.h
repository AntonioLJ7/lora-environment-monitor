#ifndef _CONF_LORA_H_
#define _CONF_LORA_H_

#include <stdint.h>

// LoRa radio frequency (EU868 ISM band)
#define RF_FREQUENCY                                868000000 // Hz

// Transmission output power
#define TX_OUTPUT_POWER                             5        // dBm

// LoRa configuration parameters
#define LORA_BANDWIDTH                              0        // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR                       7        // Spreading factor [SF7..SF12]
#define LORA_CODINGRATE                             1        // Coding rate [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]

// Preamble configuration
#define LORA_PREAMBLE_LENGTH                        8        // Length of the preamble
#define LORA_SYMBOL_TIMEOUT                         0        // Symbol timeout for reception
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false    // Variable-length payload
#define LORA_IQ_INVERSION_ON                        false    // IQ inversion disabled

// Reception timeout (in ms)
#define RX_TIMEOUT_VALUE                            1000

// Maximum buffer size for payload
#define BUFFER_SIZE                                 80       // Max size of LoRa message

// Function prototypes
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);  // Callback when data is received
void OnTxTimeout(void);                                                    // Callback when transmission times out
void OnTxDone(void);                                                       // Callback when transmission is done
void iniciarLoRa(void);                                                    // Initializes LoRa module
void envioPaquetes(float tem, float hum, float pres, float gas);           // Sends sensor data over LoRa

// Global variables shared across modules
extern int tiempo_muestreo;  // Sampling interval in seconds
extern bool lora_idle;       // Indicates whether LoRa is ready to transmit

#endif // _CONF_LORA_H_