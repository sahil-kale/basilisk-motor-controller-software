#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport_c.h>

extern "C"
{
    #include "led.h"
}
#include "hal_input.h"

TEST_GROUP(LED)
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

//Test forward colour is passed when positive speed is given
TEST(LED, forward_colour_is_passed_when_positive_speed_is_given)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;
    input_state.BRAKE_MODE_ENABLED = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_led_set_colour")
            ->withUnsignedIntParameters("red", FORWARD_COLOUR.red)
            ->withUnsignedIntParameters("green", FORWARD_COLOUR.green)
            ->withUnsignedIntParameters("blue", FORWARD_COLOUR.blue);

    led_controller_run();
}

//Test backwards colour is passed when negative speed is given
TEST(LED, backwards_colour_is_passed_when_negative_speed_is_given)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = -50;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;
    input_state.BRAKE_MODE_ENABLED = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_led_set_colour")
            ->withUnsignedIntParameters("red", BACKWARDS_COLOUR.red)
            ->withUnsignedIntParameters("green", BACKWARDS_COLOUR.green)
            ->withUnsignedIntParameters("blue", BACKWARDS_COLOUR.blue);

    led_controller_run();
}

//Test no movement colour is passe when speed is 0
TEST(LED, no_movement_colour_is_passed_when_speed_is_0)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 0;
    input_state.ticks_since_last_input = 0;
    input_state.sign_change_requested = false;
    input_state.BRAKE_MODE_ENABLED = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_led_set_colour")
            ->withUnsignedIntParameters("red", NO_MOVEMENT_COLOUR.red)
            ->withUnsignedIntParameters("green", NO_MOVEMENT_COLOUR.green)
            ->withUnsignedIntParameters("blue", NO_MOVEMENT_COLOUR.blue);

    led_controller_run();
}

//Test that timeout colour is passed when no input is given
TEST(LED, timeout_colour_is_passed_when_no_input_is_given)
{
    mock_c()->ignoreOtherCalls();

    static input_state_info_t input_state; 

    input_state.speed = 0;
    input_state.ticks_since_last_input = INPUT_TIMEOUT_TICKS;
    input_state.sign_change_requested = false;
    input_state.BRAKE_MODE_ENABLED = true;

    mock_c()->expectOneCall("get_input_state_info")
            ->andReturnPointerValue(&input_state);

    mock_c()->expectOneCall("hal_led_set_colour")
            ->withUnsignedIntParameters("red", NO_SIGNAL_COLOUR.red)
            ->withUnsignedIntParameters("green", NO_SIGNAL_COLOUR.green)
            ->withUnsignedIntParameters("blue", NO_SIGNAL_COLOUR.blue);

    led_controller_run();
}
