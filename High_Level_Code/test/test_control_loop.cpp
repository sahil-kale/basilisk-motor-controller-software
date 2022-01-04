#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport_c.h>
extern "C"
{
    #include "control_loop.h"
}
#include "hal_input.h"

TEST_GROUP(ControlLoop)
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

TEST(ControlLoop, speed_is_0_with_brake)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state;
    input_state.speed = 0;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    control_loop_run();

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", true);
}
