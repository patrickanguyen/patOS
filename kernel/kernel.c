#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "kernel.h"
#include <stdbool.h>

#define CONSOLE_HEADER() kprint("patOS> ", 0);

void kernel_main(void) 
{
    isr_install();
    irq_install();
    clear_screen();

    CONSOLE_HEADER();

}

void handle_input(char *input)
{
    if (strcmp(input, "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(input, "duck") == 0) {
        kprint("     __\n", VGA_COLOR(BLACK, YELLOW));
        kprint(" ___( o)>\n", VGA_COLOR(BLACK, YELLOW));
        kprint(" \\ <_. )\n", VGA_COLOR(BLACK, YELLOW));
        kprint("  `---'\n", VGA_COLOR(BLACK, YELLOW));
    }
    else {
        kprint("Invalid Command\n", 0);
    }
    CONSOLE_HEADER();
}