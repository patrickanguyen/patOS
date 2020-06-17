#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include <stdbool.h>

void kernel_main() 
{
    isr_install();
    irq_install();
    clear_screen();

    int x = 53;
    char buffer[4];
    itoa(x, buffer);
    kprint(buffer, 0);
    
}