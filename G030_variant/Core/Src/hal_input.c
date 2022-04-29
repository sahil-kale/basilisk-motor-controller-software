#include "hal_input.h"

//TODO: UPDATE!!
const uint32_t INPUT_TIMEOUT_TICKS = 100; //Ticks before the system is considered to be timed out

static input_state_info_t input_info = {0};

void hal_input_init(void)
{
    input_info.BRAKE_MODE_ENABLED = 0;
    input_info.sign_change_requested = 0;
    input_info.speed = 50;
    input_info.ticks_since_last_input = 0;
}

input_state_info_t* get_input_state_info(void)
{
    return &input_info;
}

//Timer resolution notes:
/*

16MHz/49 = 326.530kHz
326.530kHz/65306 ARR = 5Hz Rollover period
@326.530kHz, one tick = 0.003ms

*/

