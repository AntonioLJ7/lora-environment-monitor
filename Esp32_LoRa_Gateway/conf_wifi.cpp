#include "conf_wifi.h"
#include <Arduino.h>
#include <WiFi.h>

// Wi-Fi network credentials
const char* ssid = "";     // Replace with your actual SSID
const char* password = ""; // Replace with your actual password

/**
 * @brief Connects the ESP32 to the specified Wi-Fi network.
 * 
 * Starts the Wi-Fi interface and waits until a connection is established.
 * Displays progress in the serial monitor.
 */
void iniciarWifi(void) {
    Serial.print("🔗 Connecting to WiFi");
    WiFi.begin(ssid, password);

    // Wait until connected
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\n✅ Connected to WiFi");
}