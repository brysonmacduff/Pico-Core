#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string>
#include <chrono>
#include <memory>

#define UART_ID uart0 // There are only two uart instance options (UART0 or UART1)
static constexpr uint8_t TX_GPIO = 0; // UART0 TX GPIO PIN
static constexpr uint8_t RX_GPIO = 1; // UART0 RX GPIO PIN
static constexpr uint32_t BAUD_RATE = 115200;
static constexpr uint8_t DATA_BITS = 8;
static constexpr uint8_t STOP_BITS = 1;
static constexpr uart_parity_t PARITY = UART_PARITY_NONE;

static std::chrono::milliseconds TX_DELAY {1000};

std::string rx_message;

// Called via a UART harware interrupt
void UartRxHandler()
{
    while (uart_is_readable(UART_ID)) 
    {
        const char rune = uart_getc(UART_ID);
        rx_message += rune;

        if(rune == '\n')
        {
            printf("UartRxHandler() -> RX: {%s}", rx_message.c_str());
            rx_message.clear();
        }
    }
}

int main()
{
    stdio_init_all();

    uart_inst_t* uart_id = UART_ID;

    uart_init(uart_id, BAUD_RATE);

    gpio_set_function(TX_GPIO, UART_FUNCSEL_NUM(UART_ID, TX_GPIO));
    gpio_set_function(RX_GPIO, UART_FUNCSEL_NUM(UART_ID, RX_GPIO));

    uart_set_hw_flow(uart_id, false, false);
    uart_set_format(uart_id, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(uart_id, false);
    int UART_IRQ = uart_id == uart0 ? UART0_IRQ : UART1_IRQ;

    // Set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, UartRxHandler);
    irq_set_enabled(UART_IRQ, true);
    // Enable the UART to send interrupts - RX only
    uart_set_irq_enables(uart_id, true, false);

    uint32_t counter = 0;
    while(true)
    {
        std::string tx_message = "Hello from TX: " + std::to_string(counter) + "\n";
        uart_puts(uart_id, tx_message.c_str());
        ++counter;
        sleep_ms(TX_DELAY.count());
    }

    return 0;
}