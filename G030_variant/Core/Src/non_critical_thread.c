#include "non_critical_thread.h"
#include "led.h"
#include "hal_adc.h"

/* @TODO: MODIFY THESE VALUES TO EXPERIMENTAL VALUES */
const uint16_t MAX_TEMP_ADC_VALUE = 384;
const uint16_t MAX_VOLTAGE_ADC_VALUE = 301;

void init_non_critical_thread(void)
{
    //Init the ADC's
    hal_adc_init();

    //Init the LED's
    init_led();
}

void non_critical_thread_run(void)
{

    //Get temperature value
    uint16_t temp_value = hal_adc_get_temp_value();

    if(temp_value >= MAX_TEMP_ADC_VALUE)
    {
        //Do something
    }

    //Get voltage value
    uint16_t voltage_value = hal_adc_get_voltage_value();

    if(voltage_value >= MAX_VOLTAGE_ADC_VALUE)
    {
        //Do something
    }

        //Run the LED controller
    led_controller_run();

}