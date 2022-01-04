#include <CppUTestExt/MockSupport_c.h>
#include "hal_led_control.h"

void hal_led_init()
{
    return;
}

void hal_led_set_colour(uint8_t red, uint8_t green, uint8_t blue)
{
    mock_c()->actualCall("hal_led_set_colour")
            ->withUnsignedIntParameters("red", red)
            ->withUnsignedIntParameters("green", green)
            ->withUnsignedIntParameters("blue", blue);
}
