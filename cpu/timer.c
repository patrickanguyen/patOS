#include "timer.h"
#include "../drivers/screen.h"
#include "ports.h"
#include "../kernel/util.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_callback(__attribute__((unused)) registers_t *r)
{
    ++tick;
}

void init_timer(uint32_t freq)
{
    /* Install interrupt handler */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get PIT value */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);

}