#include "hal_hbridge.h"
#include "tim.h"
#include "main.h"
#include "gpio.h"

extern TIM_HandleTypeDef htim3;

#define PWM_B_HIGH_TIM_CHANNEL TIM_CHANNEL_1
#define PWM_A_HIGH_TIM_CHANNEL TIM_CHANNEL_2

#define ABS(N) ((N<0)?(-N):(N))

void hal_hbridge_init(void)
{
    HAL_TIM_PWM_Start(&htim3, PWM_A_HIGH_TIM_CHANNEL);
    HAL_TIM_PWM_Start(&htim3, PWM_B_HIGH_TIM_CHANNEL);
    //Set the CCR val to 0
    __HAL_TIM_SET_COMPARE(&htim3, PWM_A_HIGH_TIM_CHANNEL, 0);
    __HAL_TIM_SET_COMPARE(&htim3, PWM_B_HIGH_TIM_CHANNEL, 0);
}

void hal_hbridge_set_speed(int8_t speed, bool brake_mode_set)
{
	volatile int8_t dump = speed;
    if(speed == 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, PWM_A_HIGH_TIM_CHANNEL, 0);
        __HAL_TIM_SET_COMPARE(&htim3, PWM_B_HIGH_TIM_CHANNEL, 0);

        if(brake_mode_set)
        {
            //Short phases to each other via GND
            HAL_GPIO_WritePin(A_LOW_GPIO_Port, A_LOW_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B_LOW_GPIO_Port, B_LOW_Pin, GPIO_PIN_SET);
        }
        else
        {
            //Leave phases floating
            HAL_GPIO_WritePin(A_LOW_GPIO_Port, A_LOW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_LOW_GPIO_Port, B_LOW_Pin, GPIO_PIN_RESET);
        }

    }
    else if(speed > 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, PWM_A_HIGH_TIM_CHANNEL, ABS(speed));
        __HAL_TIM_SET_COMPARE(&htim3, PWM_B_HIGH_TIM_CHANNEL, 0);
        
        //Make opposite phase low short phase to GND, leave other side unasserted
        HAL_GPIO_WritePin(A_LOW_GPIO_Port, A_LOW_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B_LOW_GPIO_Port, B_LOW_Pin, GPIO_PIN_SET);

    }
    else
    {
        __HAL_TIM_SET_COMPARE(&htim3, PWM_A_HIGH_TIM_CHANNEL, 0);
        __HAL_TIM_SET_COMPARE(&htim3, PWM_B_HIGH_TIM_CHANNEL, ABS(speed));

        //Make opposite phase low short phase to GND, leave other side unasserted
        HAL_GPIO_WritePin(A_LOW_GPIO_Port, A_LOW_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B_LOW_GPIO_Port, B_LOW_Pin, GPIO_PIN_RESET);
    }

}
