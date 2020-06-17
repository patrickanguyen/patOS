#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "kernel.h"
#include <stdbool.h>

void kernel_main() 
{
    isr_install();
    irq_install();
    clear_screen();

    kprint(">", 0);
}

void handle_input(char *input)
{
    if (strcmp(input, "clear") == 0) {
        clear_screen();
    }
    else {
        kprint("You said: ", 0);
        kprint(input, 0);
        kprint("\n", 0);
    }
    kprint(">", 0);
}