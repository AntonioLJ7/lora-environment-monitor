#ifndef _LCD_H_
#define _LCD_H_

/**
 * @brief Initializes the I2C LCD display.
 * 
 * Sets the I2C pins (SDA, SCL), initializes the display,
 * turns on the backlight, and shows a welcome message.
 */
void iniciarLCD(void);

/**
 * @brief Displays BME680 sensor data on a 16x4 LCD.
 * 
 * Shows temperature, humidity, pressure, and gas resistance
 * values on the corresponding lines of the LCD screen.
 * 
 * @param tem Temperature in degrees Celsius
 * @param hum Humidity percentage
 * @param pres Atmospheric pressure in hPa
 * @param gas Gas resistance in KOhms
 */
void visualizarDatos_BME680_LCD(float tem, float hum, float pres, float gas);

#endif // _LCD_H_