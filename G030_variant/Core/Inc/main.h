/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_TEMP_Pin GPIO_PIN_0
#define ADC_TEMP_GPIO_Port GPIOA
#define ADC_VOLTAGE_Pin GPIO_PIN_1
#define ADC_VOLTAGE_GPIO_Port GPIOA
#define RC_IN_Pin GPIO_PIN_4
#define RC_IN_GPIO_Port GPIOA
#define A_LOW_Pin GPIO_PIN_5
#define A_LOW_GPIO_Port GPIOA
#define PWM_B_HIGH_Pin GPIO_PIN_6
#define PWM_B_HIGH_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_8
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOA
#define B_LOW_Pin GPIO_PIN_12
#define B_LOW_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_3
#define LED_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
