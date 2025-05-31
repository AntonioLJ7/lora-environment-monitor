#include "lcd.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "bme_680.h"

// Create a 16x4 LCD object at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 4);

/**
 * @brief Initializes the I2C LCD display.
 * 
 * Sets up the LCD to operate over I2C on the Heltec V3 using GPIO6 (SDA) and GPIO7 (SCL).
 * Displays a welcome message for a few seconds and then clears the screen.
 */
void iniciarLCD(void) {
  Wire.begin(6, 7); // SDA = GPIO6, SCL = GPIO7 (specific to Heltec V3)

  lcd.init();             // Initialize the LCD
  lcd.begin(16, 4);       // Explicitly set dimensions: 16 columns, 4 rows
  lcd.backlight();        // Turn on the backlight

  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Monitor systems v1.0 ");

  lcd.setCursor(0, 1);
  lcd.print("ESP32 + LoRa");

  lcd.setCursor(0, 2);
  lcd.print("Univ. Malaga [TFG]");

  lcd.setCursor(0, 3);
  lcd.print("Version 1.0");

  delay(5000);  // Show message for 5 seconds

  lcd.clear();  // Clear the screen for normal operation
}

/**
 * @brief Displays the latest environmental sensor data on the LCD.
 * 
 * Prints temperature, humidity, pressure and gas resistance values
 * on each row of the 16x4 LCD screen.
 * 
 * @param tem Temperature in °C
 * @param hum Humidity in %
 * @param pres Pressure in hPa
 * @param gas Gas resistance in KOhms
 */
void visualizarDatos_BME680_LCD(float tem, float hum, float pres, float gas) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tem);
  lcd.print(" C ");

  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(hum);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Presion: ");
  lcd.print(pres);
  lcd.print(" hPa");

  lcd.setCursor(0, 3);
  lcd.print("Gas: ");
  lcd.print(gas);
  lcd.print(" KOhms");
}
