#include "hal_input.h"

//TODO: UPDATE!!
const uint32_t INPUT_TIMEOUT_TICKS = 100; //Ticks before the system is considered to be timed out

static input_state_info_t input_info = {0};

void hal_input_init(void)
{
    input_info.BRAKE_MODE_ENABLED = 0;
    input_info.sign_change_requested = 0;
    input_info.speed = 100;
    input_info.ticks_since_last_input = 0;
}

input_state_info_t* get_input_state_info(void)
{
    input_info.ticks_since_last_input++;
    return &input_info;
}

//Timer resolution notes:
/*

16MHz/49 = 326.530kHz
326.530kHz/65306 ARR = 5Hz Rollover period
@326.530kHz, one tick = 0.003ms

*/

//This can be made a function of frequency, but for the purposes of development keeping it as constant
#define TICK_TO_MS (0.003f)
#define FULL_FWD_MS (2.000f)
#define NEUT_MS (1.500f)
#define NEUT_DEADBAND (0.1f)
#define FULL_REV_MS (1.000f)
#define DELTA_TICK_MS (0.500f)


void input_new_tick_delta(uint16_t delta_tick)
{
	float ticks_ms = delta_tick * TICK_TO_MS;
	input_info.ticks_since_last_input = 0;

	if((ticks_ms < NEUT_MS + NEUT_DEADBAND) && (ticks_ms > NEUT_MS - NEUT_DEADBAND))
	{
		input_info.speed = 0;
	}
	else if(ticks_ms <= FULL_FWD_MS)
	{
		int8_t new_speed = (int8_t)((FULL_FWD_MS - (ticks_ms))/DELTA_TICK_MS * 100);
		if(input_info.speed < 0)
		{
			input_info.sign_change_requested = true;
		}
		input_info.speed = new_speed;
	}
	else if(ticks_ms <= FULL_FWD_MS)
	{
		int8_t new_speed = (int8_t)((FULL_REV_MS - (ticks_ms))/DELTA_TICK_MS * 100);
		if(input_info.speed > 0)
		{
			input_info.sign_change_requested = true;
		}
		input_info.speed = new_speed;
	}


}

