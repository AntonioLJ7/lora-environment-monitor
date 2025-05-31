#ifndef _CONF_WIFI_H_
#define _CONF_WIFI_H_

/**
 * @file conf_wifi.h
 * @brief Wi-Fi connection interface for the ESP32-based gateway.
 * 
 * This header declares the function responsible for connecting the device to
 * a specified Wi-Fi network. The implementation is defined in conf_wifi.cpp.
 */

/**
 * @brief Initializes the Wi-Fi connection.
 * 
 * Attempts to connect to the pre-configured Wi-Fi network.
 * Blocks until a successful connection is established.
 */
void iniciarWifi(void);

#endif // _CONF_WIFI_H_