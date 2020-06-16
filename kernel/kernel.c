#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void kernel_main() 
{
    isr_install();
    irq_install();
    clear_screen();

    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
    __asm__ __volatile__("int $16");

    kprint("Hello World!\n", VGA_COLOR(BLACK, WHITE));
}