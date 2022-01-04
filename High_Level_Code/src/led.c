#include "led.h"
#include "hal_led_control.h"
#include "hal_input.h"

const colour_value_t FORWARD_COLOUR = {0, 255, 0};
const colour_value_t BACKWARDS_COLOUR = {255, 0, 0};
const colour_value_t NO_MOVEMENT_COLOUR = {0, 0, 0};
const colour_value_t NO_SIGNAL_COLOUR = {0, 0, 255};

void init_led(void)
{
    hal_led_init();
}

void led_controller_run(void)
{
    input_state_info_t* input_state = get_input_state_info();

    if(input_state->ticks_since_last_input >= INPUT_TIMEOUT_TICKS)
    {
        hal_led_set_colour(NO_SIGNAL_COLOUR.red, NO_SIGNAL_COLOUR.green, NO_SIGNAL_COLOUR.blue);
    }
    else
    {
        if(input_state->speed > 0)
        {
            hal_led_set_colour(FORWARD_COLOUR.red, FORWARD_COLOUR.green, FORWARD_COLOUR.blue);
        }
        else if(input_state->speed < 0)
        {
            hal_led_set_colour(BACKWARDS_COLOUR.red, BACKWARDS_COLOUR.green, BACKWARDS_COLOUR.blue);
        }
        else
        {
            hal_led_set_colour(NO_MOVEMENT_COLOUR.red, NO_MOVEMENT_COLOUR.green, NO_MOVEMENT_COLOUR.blue);
        }
    }

}