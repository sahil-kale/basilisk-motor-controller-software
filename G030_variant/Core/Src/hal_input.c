#include "hal_input.h"
#include "tim.h"

#define SIGNOF(val) ((0 < (val)) - ((val) < 0))

//TODO: UPDATE!!
const uint32_t INPUT_TIMEOUT_TICKS = 100; //Ticks before the system is considered to be timed out

static input_state_info_t input_info = {0};

void hal_input_init(void)
{
    input_info.BRAKE_MODE_ENABLED = 0;
    input_info.sign_change_requested = 0;
    input_info.speed = 50;
    input_info.ticks_since_last_input = 0;

    //Initalize the timer
    HAL_TIM_IC_Start_IT(&htim14, TIM_CHANNEL_1);
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

/**
 * @brief input capture handler design pattern from https://controllerstech.com/input-capture-in-stm32/
 * 
 */

static const uint32_t TIM_CLOCK = 16000000;
static const uint32_t TIM_PRESCALER = 49;
static const uint32_t TIM_ARR = 65306;
static const float min_pulse_width_us = 1000.0f;
static const float max_pulse_width_us = 2000.0f;

static uint32_t IC_VAL_1 = 0;
static uint32_t IC_VAL_2 = 0;
static uint32_t Difference = 0;
static bool is_first_captured = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM14 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
  {
      //Check to see if the first value is not captured
      if(is_first_captured == 0)
      {
        IC_VAL_1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        is_first_captured = 1;
      }
      else //Rising edge is captured, now let is edit the second edge
      {
        IC_VAL_2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        if(IC_VAL_2 > IC_VAL_1)
        {
          Difference = IC_VAL_2 - IC_VAL_1;
        }
        else
        {
          Difference = (TIM_ARR - IC_VAL_1) - IC_VAL_2;
        }

        //Cleanup the timer
        __HAL_TIM_SET_COUNTER(htim, 0);
        is_first_captured = 0;

        float refClock = TIM_CLOCK/TIM_PRESCALER;
        //float frequency = (refClock/Difference);
        float mFactor = 1000000/refClock;
        
        float pulseWidthUs = Difference*mFactor;
        /**Convert pulse width into speed**/
        int8_t last_speed = input_info.speed;

        //Update input info
        input_info.speed = (pulseWidthUs - min_pulse_width_us)/(max_pulse_width_us - min_pulse_width_us)*100;
        input_info.sign_change_requested = (SIGNOF(last_speed) != SIGNOF(input_info.speed));
        input_info.ticks_since_last_input = 0;
      }
  }
}
