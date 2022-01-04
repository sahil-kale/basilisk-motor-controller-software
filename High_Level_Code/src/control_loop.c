#include "control_loop.h"
#include "hal_input.h"
#include "hal_hbridge.h"

void control_loop_init(void)
{
    hal_input_init(); //Init the input module
    hal_hbridge_init(); //Init the hbridge module
}

void control_loop_run(void)
{
    
}

