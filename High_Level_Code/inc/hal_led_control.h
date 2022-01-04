#ifndef HAL_LED_CONTROL_H
#define HAL_LED_CONTROL_H
#include <stdint.h>

void hal_led_init(void);

/**
 * @brief Set the LED colour
 * 
 * @param red red value
 * @param green green value
 * @param blue blue value
 */
void hal_led_set_colour(uint8_t red, uint8_t green, uint8_t blue);

#endif