#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport_c.h>
extern "C"
{
    #include "non_critical_thread.h"
}

#include "hal_adc.h"
#include "hal_input.h"

TEST_GROUP(NonCriticalThread)
{
    void setup()
    {
    }

    void teardown()
    {
        mock_c()->checkExpectations();
        mock_c()->clear();
    }
};

//Ensure that temp & voltage monitoring is called
TEST(NonCriticalThread, temp_voltage_monitoring_is_called)
{
    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;
    input_state.BRAKE_MODE_ENABLED = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);
    mock_c()->ignoreOtherCalls();

    mock_c()->expectOneCall("hal_adc_get_temp_value")
            ->andReturnUnsignedIntValue(0);
    
    mock_c()->expectOneCall("hal_adc_get_voltage_value")
            ->andReturnUnsignedIntValue(0);

    non_critical_thread_run();
}
