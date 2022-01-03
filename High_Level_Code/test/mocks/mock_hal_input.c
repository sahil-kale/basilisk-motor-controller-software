#include <CppUTestExt/MockSupport_c.h>
#include "hal_input.h"

void init_hal_input(void)
{
    return;
}

input_state_info_t* get_input_state_info(void)
{
    mock_c()->actualCall("get_input_state_info");
    input_state_info_t* ret = mock_c()->returnPointerValueOrDefault(NULL);
    return ret;
}