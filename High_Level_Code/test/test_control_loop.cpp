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
        mock_c()->checkExpectations();
        mock_c()->clear();
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

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", true);

    control_loop_run();

}

TEST(ControlLoop, speed_is_0_with_sign_change_requested)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

}

//Test that speed is set to 50 with no sign change requested
TEST(ControlLoop, speed_is_50_with_no_sign_change_requested)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

}

const uint32_t INPUT_TIMEOUT_TICKS = 100;
//Test that the speed is set to 0 if the input is not received for a while
TEST(ControlLoop, speed_is_0_if_input_is_not_received_for_a_while)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = INPUT_TIMEOUT_TICKS;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", true);

    control_loop_run();

}

//Test with speed going from positive, to negative, and assert the speeds along the way
TEST(ControlLoop, speed_is_positive_to_negative)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Simulate speed of -50 command now

    input_state.speed = -50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Tick over of 0 has occured, now make sure it gets set to -50

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", -50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

}

//Test speed going from negative number to positive number
TEST(ControlLoop, speed_is_negative_to_positive)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = -50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", -50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Simulate speed of 50 command now

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Tick over of 0 has occured, now make sure it gets set to 50

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

}

//Test speed going from positive number to 0 and brake mode is set
TEST(ControlLoop, speed_is_positive_to_0_and_brake_mode_is_set)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Simulate speed of 0 command now

    input_state.speed = 0;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", true);

    control_loop_run();
}

//Test speed going from negative to 0 and brake mode is set
TEST(ControlLoop, speed_is_negative_to_0_and_brake_mode_is_set)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = -50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", -50)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Simulate speed of 0 command now

    input_state.speed = 0;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = true;

    //Brake mode should be false since we just requested a sign change. In reality this happens at a super fast rate

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", false);

    control_loop_run();

    //Now, ensure that brake mode is set

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_hbridge_set_speed")
            ->withIntParameters("speed", 0)
            ->withBoolParameters("brake_mode_set", true);

    control_loop_run();
}