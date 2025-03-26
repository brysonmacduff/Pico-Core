#include "pulse_width_modulator.h"

namespace PicoCore 
{

PulseWidthModulator::PulseWidthModulator(uint8_t gpio, 
    uint32_t pwm_frequency_hz, 
    uint32_t clock_frequency_hz
) : m_gpio(gpio)
{   
    // Configure the gpio pin for pwm usage
    gpio_set_function(m_gpio, GPIO_FUNC_PWM);
    // Get the PWM slice for the specified gpio
    const uint pwm_slice = pwm_gpio_to_slice_num(m_gpio);

    // Initialize the PWM slice
    pwm_set_gpio_level(m_gpio, 0);
    pwm_set_enabled(pwm_slice, true);

    // Get the PWM channel for the specified gpio
    const uint pwm_channel = pwm_gpio_to_channel(m_gpio);
    
    // Compute the clock divider value for the given pwm frequency and Pico clock frequency
    const uint32_t clock_divider = ComputeClockDivider(pwm_frequency_hz, clock_frequency_hz);

    // Set the clock divider value for the given pwm slice
    pwm_set_clkdiv_int_frac(pwm_slice, clock_divider/16, clock_divider & 0xF);

    // Compute the wrap size
    m_wrap = ComputeWrap(pwm_frequency_hz, clock_frequency_hz, clock_divider);

    // Set the wrap value for the given pwm slice
    pwm_set_wrap(pwm_slice, m_wrap);

    printf("PulseWidthModulator::PulseWidthModulator() -> gpio: {%u}, clock_divider: {%u}, wrap: {%u}\n", m_gpio, clock_divider, m_wrap); 
}

// Note that the duty_cycle argument must be a value between zero and one
bool PulseWidthModulator::SetPwmDutyCycle(float duty_cycle)
{
    if(duty_cycle < 0 || duty_cycle > 1)
    {
        return false;
    }

    return SetChannelLevel(duty_cycle);
}

/* This function will set the angle of the servo. 
 * The duty_cycle_fraction argument is a value between zero and one, where zero is 
 * the lower angular limit and one is the upper angular limit of the servo. */
bool PulseWidthModulator::SetChannelLevel(float duty_cycle)
{
    if(duty_cycle < 0 || duty_cycle > 1)
    {
        return false;
    }

    const uint pwm_slice = pwm_gpio_to_slice_num(m_gpio);
    const uint pwm_channel = pwm_gpio_to_channel(m_gpio);
    const uint16_t level = m_wrap * duty_cycle;

    printf("PulseWidthModulator::SetChannelLevel() -> Setting level to: {%u}, for duty_cycle: {%f}\n",level,duty_cycle);

    pwm_set_chan_level(pwm_slice, pwm_channel, level);

    return true;
}

uint32_t PulseWidthModulator::ComputeClockDivider(uint32_t pwm_frequency_hz, uint32_t clock_frequency_hz)
{
    uint32_t clock_divider = clock_frequency_hz / pwm_frequency_hz / 4096 + (clock_frequency_hz % (pwm_frequency_hz * 4096) != 0);

    if(clock_divider / 16 == 0)
    {
        clock_divider = 0;
    }

    return clock_divider;
}

uint16_t PulseWidthModulator::ComputeWrap(uint32_t pwm_frequency_hz, uint32_t clock_frequency_hz, uint32_t clock_divider)
{
    const uint32_t wrap = clock_frequency_hz * 16 / clock_divider / pwm_frequency_hz - 1;
    return wrap;
}
}