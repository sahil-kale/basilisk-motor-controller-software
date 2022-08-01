#ifndef LED_H
#define LED_H
#include <stdint.h>

//This is only public for the sake of unit testing lol
typedef struct colour_value
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} colour_value_t;

extern const colour_value_t FORWARD_COLOUR;
extern const colour_value_t BACKWARDS_COLOUR;
extern const colour_value_t NO_MOVEMENT_COLOUR;
extern const colour_value_t NO_SIGNAL_COLOUR;


void init_led(void);

/**
 * @brief Runs the LED controller with the appropriate LED colour
 * 
 */
void led_controller_run(void);

#endif
