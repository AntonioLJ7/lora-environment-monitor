#ifndef _CONF_GATEWAY_H_
#define _CONF_GATEWAY_H_

#include <stdint.h>

/**
 * @file conf_gateway.h
 * @brief LoRa configuration and interface for the gateway node.
 * 
 * This file defines the parameters used to initialize the LoRa module and
 * declares the functions used for setting up and handling LoRa communication
 * in the gateway.
 */

// LoRa configuration parameters for the EU868 band (change to 915E6 for US)
#define RF_FREQUENCY              868000000    ///< LoRa radio frequency in Hz
#define TX_OUTPUT_POWER           14           ///< Transmission power in dBm
#define LORA_BANDWIDTH            0            ///< [0: 125 kHz, 1: 250 kHz, 2: 500 kHz]
#define LORA_SPREADING_FACTOR     7            ///< Spreading factor (SF7 to SF12)
#define LORA_CODINGRATE           1            ///< [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH      8            ///< Length of the preamble
#define LORA_SYMBOL_TIMEOUT       0            ///< Symbol timeout (0 = no timeout)
#define LORA_FIX_LENGTH_PAYLOAD_ON false       ///< Variable payload length
#define LORA_IQ_INVERSION_ON      false        ///< Standard IQ setup (not inverted)

/**
 * @brief Initializes the LoRa module for the gateway.
 */
void iniciarLoRa(void);

/**
 * @brief Callback function when a LoRa packet is received.
 * 
 * @param payload Pointer to the received payload
 * @param size Size of the payload
 * @param rssi Signal strength
 * @param snr Signal-to-noise ratio
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/**
 * @brief Processes LoRa interrupts for RX/TX events.
 */
void mantenerRecepcion(void);

/**
 * @brief Callback function when a LoRa transmission completes.
 */
void OnTxDone(void);

#endif // _CONF_GATEWAY_H_