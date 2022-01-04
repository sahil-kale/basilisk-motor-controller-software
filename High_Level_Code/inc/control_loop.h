#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H
#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Initialize the control loop, including PWM modules and timer ISR's
 * 
 */
void control_loop_init(void);

/**
 * @brief runs the control loop from an ISR context.
 */
void control_loop_run(void);

#endif