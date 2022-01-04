#include "control_loop.h"
#include "hal_input.h"
#include "hal_hbridge.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

static bool brake_mode_enabled = true;

void control_loop_init(void)
{
    hal_input_init(); //Init the input module
    hal_hbridge_init(); //Init the hbridge module
}

void control_loop_run(void)
{
    input_state_info_t* input_state = get_input_state_info();
    assert(input_state != NULL);
    
    int8_t speed = input_state->speed;
    
    hal_hbridge_set_speed(speed, brake_mode_enabled);

}

