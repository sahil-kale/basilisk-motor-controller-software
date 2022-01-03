#ifndef HAL_INPUT_H
#define HAL_INPUT_H
#include <stdint.h>

void init_hal_input(void);

typedef struct input_state_info
{
    int8_t speed;
    uint32_t ticks_since_last_input;
    bool sign_change_requested;
} input_state_info_t;

input_state_info_t* get_input_state_info(void);

#endif