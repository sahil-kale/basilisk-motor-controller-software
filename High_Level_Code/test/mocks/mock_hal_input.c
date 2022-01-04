#include <CppUTestExt/MockSupport_c.h>
#include "hal_input.h"
#include <stdio.h>

const uint32_t INPUT_TIMEOUT_TICKS = 100;

void hal_input_init(void)
{
    return;
}

input_state_info_t* get_input_state_info(void)
{
    mock_c()->actualCall("get_input_state_info");
    input_state_info_t* ret = mock_c()->returnPointerValueOrDefault(NULL);
    //printf("%p", (void *)ret);
    return ret;
}