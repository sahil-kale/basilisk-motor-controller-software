#ifndef NON_CRITICAL_THREAD_H
#define NON_CRITICAL_THREAD_H

/**
 * @brief Non critical thread init. Includes temp, voltage, and LED monitoring
 * 
 */
void init_non_critical_thread(void);

/**
 * @brief Non critical thread run. Includes temp, voltage, and LED monitoring
 * 
 */
void non_critical_thread_run(void);

#endif // NON_CRITICAL_THREAD_H