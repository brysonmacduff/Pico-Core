#include <cstdint>
#include <stdio.h>
#include <string>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

namespace PicoCore
{
class PulseWidthModulator
{
public:
    static constexpr uint32_t CLOCK_FREQUENCY_HZ = 125000000;

    PulseWidthModulator() = delete;
    PulseWidthModulator(uint8_t gpio, 
        uint32_t pwm_frequency_hz,  
        uint32_t clock_frequency_hz = CLOCK_FREQUENCY_HZ
    );
    ~PulseWidthModulator() = default;

    // The duty_cycle argument is the percentage of the pulse width that the signal is high
    bool SetPwmDutyCycle(float duty_cycle);

protected:

    // Refers to the gpio pin that this instance would use
    uint8_t m_gpio {0};

    // Describes the wrap counter size that is used for switching the pwm signal from high to low
    uint32_t m_wrap {0};

    bool SetChannelLevel(float level);

    static uint32_t ComputeClockDivider(uint32_t pwm_frequency_hz, uint32_t clock_frequency_hz);
    static uint16_t ComputeWrap(uint32_t pwm_frequency_hz, uint32_t clock_frequency_hz, uint32_t clock_divider);
};
}