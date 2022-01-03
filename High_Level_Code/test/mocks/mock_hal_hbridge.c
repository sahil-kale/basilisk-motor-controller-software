#include <CppUTestExt/MockSupport_c.h>
#include "hal_hbridge.h"

void hal_hbridge_init(void)
{
    return;
}

void hal_hbridge_set_speed(int8_t speed, bool brake_mode_set)
{
    mock_c()->actualCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", speed)
            ->withBoolParameters("brake_mode_set", brake_mode_set);
}
