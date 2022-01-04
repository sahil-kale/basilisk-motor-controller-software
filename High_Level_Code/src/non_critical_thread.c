#include "non_critical_thread.h"
#include "led.h"
#include "hal_adc.h"

void non_critical_thread_init(void)
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

    //Get voltage value
    uint16_t voltage_value = hal_adc_get_voltage_value();

        //Run the LED controller
    led_controller_run();

}