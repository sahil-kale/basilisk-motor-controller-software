#ifndef HAL_INPUT_H
#define HAL_INPUT_H
#include <stdint.h>
#include <stdbool.h>

void hal_input_init(void);

typedef struct input_state_info
{
    int8_t speed;
    uint32_t ticks_since_last_input;
    bool sign_change_requested;
} input_state_info_t;

input_state_info_t* get_input_state_info(void);

#endif