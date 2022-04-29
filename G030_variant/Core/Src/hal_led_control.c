#include "hal_led_control.h"
#include "tim.h"

extern TIM_HandleTypeDef htim1;

#define LED_R_TIM_CHANNEL TIM_CHANNEL_1
#define LED_G_TIM_CHANNEL TIM_CHANNEL_4
#define LED_B_TIM_CHANNEL TIM_CHANNEL_2

void hal_led_init(void)
{
    HAL_TIM_PWM_Start(&htim1, LED_G_TIM_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, LED_B_TIM_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, LED_R_TIM_CHANNEL);
    
    //Set the CCR val to 0
    __HAL_TIM_SET_COMPARE(&htim3, LED_R_TIM_CHANNEL, 0);
    __HAL_TIM_SET_COMPARE(&htim3, LED_G_TIM_CHANNEL, 0);
    __HAL_TIM_SET_COMPARE(&htim3, LED_B_TIM_CHANNEL, 0);
}

void hal_led_set_colour(uint8_t red, uint8_t green, uint8_t blue)
{
    __HAL_TIM_SET_COMPARE(&htim3, LED_R_TIM_CHANNEL, red);
    __HAL_TIM_SET_COMPARE(&htim3, LED_G_TIM_CHANNEL, green);
    __HAL_TIM_SET_COMPARE(&htim3, LED_B_TIM_CHANNEL, blue);
}