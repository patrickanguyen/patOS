#include "../drivers/screen.h"
#include "util.h"

void kernel_main() 
{
    clear_screen();
    
    kprint("Hello World!\n", VGA_COLOR(BLUE, WHITE));
    kprint("Nice to meet you", VGA_COLOR(BLUE, WHITE));
}