#ifndef HAL_ADC_H
#define HAL_ADC_H
#include <stdint.h>

void hal_adc_init(void);

/**
 * @brief Returns the ADC value from onboard temperature sensor
 * 
 * @return uint16_t 12 bit ADC result
 */
uint16_t hal_adc_get_temp_value(void);

/**
 * @brief Returns the ADC value from onboard voltage divider
 * 
 * @return uint16_t 12 bit ADC result
 */
uint16_t hal_adc_get_voltage_value(void);

#endif