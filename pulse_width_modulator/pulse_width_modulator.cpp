#include "pulse_width_modulator.h"

namespace PicoCore 
{

PulseWidthModulator::PulseWidthModulator(uint8_t gpio, 
    uint32_t pwm_frequency_hz, 
    uint32_t clock_frequency_hz
) : m_gpio(gpio), m_wrap(MAXIMUM_WRAP_SIZE)
{   
    // Configure the gpio pin for pwm usage
    gpio_set_function(m_gpio, GPIO_FUNC_PWM);

    // Get the PWM slice for the specified gpio
    const uint pwm_slice = pwm_gpio_to_slice_num(m_gpio);
    
    // Compute the clock divider value for the given pwm frequency and Pico clock frequency
    const float clock_divider = ComputeClockDivider(pwm_frequency_hz);

    pwm_set_clkdiv(pwm_slice, clock_divider);
    printf("PulseWidthModulator::PulseWidthModulator() -> gpio: {%u}, wrap: {%u}, clock_divider: {%f}\n", m_gpio, m_wrap, clock_divider); 

    // Set the wrap value for the given pwm slice
    pwm_set_wrap(pwm_slice, m_wrap);

    // Initialize the PWM slice
    pwm_set_gpio_level(m_gpio, 0);
    pwm_set_enabled(pwm_slice, true);
}

// This function sets the signal duty cycle. Note that the duty_cycle argument must be a value between zero and one
bool PulseWidthModulator::SetDutyCycle(float duty_cycle)
{
    if(duty_cycle < 0 || duty_cycle > 1)
    {
        return false;
    }

    const uint pwm_slice = pwm_gpio_to_slice_num(m_gpio);
    const uint pwm_channel = pwm_gpio_to_channel(m_gpio);
    const uint16_t level = m_wrap * duty_cycle;

    printf("PulseWidthModulator::SetChannelLevel() -> Setting level to: {%u}, for duty_cycle: {%f}\n",level, duty_cycle);

    pwm_set_chan_level(pwm_slice, pwm_channel, level);

    return true;
}

float PulseWidthModulator::ComputeClockDivider(uint32_t pwm_frequency_hz)
{
    if(pwm_frequency_hz >= MINIMUM_UNDIVIDED_PWM_FREQUENCY_HZ)
    {
        return MINIMUM_CLOCK_DIVIDER;
    }

    // Compute what the wrap would be if it could be greater than 65535
    const float wrap = static_cast<float>(CLOCK_FREQUENCY_HZ) / static_cast<float>(pwm_frequency_hz) - 1;
    // Compute the number of times the wrap can be divided by the maximum wrap value
    const float clock_divider = wrap / static_cast<float>(MAXIMUM_WRAP_SIZE);

    return clock_divider;
}

}