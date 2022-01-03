#include "hal_adc.h"
#include <CppUTestExt/MockSupport_c.h>

void hal_adc_init(void)
{
    return;
}

uint16_t hal_adc_get_value(void)
{
    mock_c()->actualCall("hal_adc_get_value");
    uint16_t ret = (uint16_t)(mock_c()->returnUnsignedIntValueOrDefault(0));
    return ret;
}