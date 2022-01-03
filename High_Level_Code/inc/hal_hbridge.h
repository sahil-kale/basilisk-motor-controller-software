#ifndef HAL_HBRIDGE_H
#define HAL_HBRIDGE_H
#include <stdint.h>
#include <stdbool.h>

//Init the PWM for the H-Bridge
void hal_hbridge_init(void);

/*
 * Set the speed of the H-Bridge
 * @param speed: the speed to set the H-Bridge to, -100 to 100
 * @param brake_mode_set: if true, the motor terminals are shorted to GND
 */
void hal_hbridge_set_speed(int8_t speed, bool brake_mode_set);

#endif