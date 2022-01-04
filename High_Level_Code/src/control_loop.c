#include "control_loop.h"
#include "hal_input.h"
#include "hal_hbridge.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

const uint32_t INPUT_TIMEOUT_TICKS = 100;

void control_loop_init(void)
{
    hal_input_init(); //Init the input module
    hal_hbridge_init(); //Init the hbridge module
}

void control_loop_run(void)
{
    input_state_info_t* input_state = get_input_state_info();
    assert(input_state != NULL);


    //Check if the system is timed out
    if (input_state->ticks_since_last_input >= INPUT_TIMEOUT_TICKS)
    {
        input_state->speed = 0; //Set speed to 0
    }

    //Increment ticks since last input
    input_state->ticks_since_last_input++;

    int8_t commanded_speed = input_state->speed;
    bool brake_set = false;

    //If sign change is requested, set the commanded speed to 0 and reset the sign change request flag
    if (input_state->sign_change_requested)
    {
        commanded_speed = 0;
        input_state->sign_change_requested = false;
    }
    else if(input_state->speed == 0 && input_state->BRAKE_MODE_ENABLED)
    {
        commanded_speed = 0;
        brake_set = true;
    }

    hal_hbridge_set_speed(commanded_speed, brake_set);

}

