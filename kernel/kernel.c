#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include <stdint.h>

void kernel_main() 
{
    isr_install();
    irq_install();
    
    clear_screen();
    
}