// This file includes the main function of test program that can be run on the raspberry pi pico

#include "pulse_width_modulator.h"
#include <stdio.h>
#include <chrono>

using namespace PicoCore;

// PWM parameters
static constexpr uint8_t PWM_GPIO = 5; // Corresponds to pin 7
static constexpr uint32_t PWM_FREQUENCY_HZ = 50;

// The time between changing the PWM signal duty cycle
static constexpr std::chrono::milliseconds DELAY {1000};

// Miuzei FS08MD servo duty cycle values (between 0 and 1)
static constexpr float LOWER_BOUND_DUTY_CYCLE = 0.025;
static constexpr float MIDPOINT_DUTY_CYCLE = 0.075;
static constexpr float UPPER_BOUND_DUTY_CYCLE = 0.125;

int main()
{
    stdio_init_all();
    sleep_ms(DELAY.count());
    printf("main() -> Beginning pulse width modulator test.\n");
    sleep_ms(DELAY.count());
    PulseWidthModulator pwm(PWM_GPIO, PWM_FREQUENCY_HZ);

    while(true)
    { 
        sleep_ms(DELAY.count());
        pwm.SetDutyCycle(LOWER_BOUND_DUTY_CYCLE);
        sleep_ms(DELAY.count());
        pwm.SetDutyCycle(MIDPOINT_DUTY_CYCLE);
        sleep_ms(DELAY.count());
        pwm.SetDutyCycle(UPPER_BOUND_DUTY_CYCLE);
        sleep_ms(DELAY.count());
        pwm.SetDutyCycle(MIDPOINT_DUTY_CYCLE);
    }

    return 0;
}