#include "../drivers/screen.h"

void kernel_main() {
    clear_screen();
    kprint("Hello World\n");
    kprint("Cool beans");
}