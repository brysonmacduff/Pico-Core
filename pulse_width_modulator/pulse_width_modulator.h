#include <cstdint>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

namespace PicoCore
{
class PulseWidthModulator
{
public:
    // Note that this class assumes a Pico clock frequency of 125 MHz
    static constexpr uint32_t CLOCK_FREQUENCY_HZ = 125000000;

    PulseWidthModulator() = delete;
    PulseWidthModulator(uint8_t gpio, 
        uint32_t pwm_frequency_hz,  
        uint32_t clock_frequency_hz = CLOCK_FREQUENCY_HZ
    );
    ~PulseWidthModulator() = default;

    // The duty_cycle argument is the percentage of the pulse width that the signal is high
    bool SetDutyCycle(float duty_cycle);

protected:

    // The wrap counter is a 16 bit register, which places the following limit on the maximum integer it can store
    static constexpr uint16_t MAXIMUM_WRAP_SIZE = 65535;
    // Refers to the minimum signal frequency (rounded up) that can be generated without the use of a clock divider, assuming a clock frequency of 125 MHz
    static constexpr uint16_t MINIMUM_UNDIVIDED_PWM_FREQUENCY_HZ = 1908;
    // Refers to the minimum clock divider value, which is used when a divider is not needed (PWM frequency is at least 1908 Hz)
    static constexpr float MINIMUM_CLOCK_DIVIDER = 1;

    // Refers to the gpio pin that this instance uses to generate a PWM signal
    uint8_t m_gpio {0};
    // Describes the wrap counter size that is used for switching the pwm signal from high to low
    uint16_t m_wrap {MAXIMUM_WRAP_SIZE};

    static float ComputeClockDivider(uint32_t pwm_frequency_hz);
};
}