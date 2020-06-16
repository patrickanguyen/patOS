#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"

void kernel_main() 
{
    clear_screen();
    isr_install();
    
    kprint("Hello World!\n", 0);
}