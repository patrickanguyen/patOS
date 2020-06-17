#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../lib/string.h"
#include <stdint.h>

static void print_letter(uint8_t scancode);

static void keyboard_callback(__attribute__((unused))registers_t *r)
{
    uint8_t scancode = port_byte_in(0x60);
    char sc_ascii[4];
    itoa(scancode, sc_ascii);
    kprint(sc_ascii, VGA_COLOR(BLACK, WHITE));
    kprint(", ", VGA_COLOR(BLACK, WHITE));
    print_letter(scancode);
    kprint("\n", VGA_COLOR(BLACK, WHITE));
}

void init_keyboard(void)
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

static void print_letter(uint8_t scancode) {
    switch (scancode) {
        case 0x0:
            kprint("ERROR", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x1:
            kprint("ESC", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x2:
            kprint("1", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x3:
            kprint("2", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x4:
            kprint("3", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x5:
            kprint("4", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x6:
            kprint("5", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x7:
            kprint("6", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x8:
            kprint("7", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x9:
            kprint("8", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0A:
            kprint("9", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0B:
            kprint("0", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0C:
            kprint("-", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0D:
            kprint("+", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0E:
            kprint("Backspace", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x0F:
            kprint("Tab", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x10:
            kprint("Q", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x11:
            kprint("W", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x12:
            kprint("E", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x13:
            kprint("R", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x14:
            kprint("T", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x15:
            kprint("Y", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x16:
            kprint("U", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x17:
            kprint("I", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x18:
            kprint("O", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x19:
            kprint("P", VGA_COLOR(BLACK, WHITE));
            break;
		case 0x1A:
			kprint("[", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x1B:
			kprint("]", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x1C:
			kprint("ENTER", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x1D:
			kprint("LCtrl", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x1E:
			kprint("A", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x1F:
			kprint("S", VGA_COLOR(BLACK, WHITE));
			break;
        case 0x20:
            kprint("D", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x21:
            kprint("F", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x22:
            kprint("G", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x23:
            kprint("H", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x24:
            kprint("J", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x25:
            kprint("K", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x26:
            kprint("L", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x27:
            kprint(";", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x28:
            kprint("'", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x29:
            kprint("`", VGA_COLOR(BLACK, WHITE));
            break;
		case 0x2A:
			kprint("LShift", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x2B:
			kprint("\\", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x2C:
			kprint("Z", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x2D:
			kprint("X", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x2E:
			kprint("C", VGA_COLOR(BLACK, WHITE));
			break;
		case 0x2F:
			kprint("V", VGA_COLOR(BLACK, WHITE));
			break;
        case 0x30:
            kprint("B", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x31:
            kprint("N", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x32:
            kprint("M", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x33:
            kprint(",", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x34:
            kprint(".", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x35:
            kprint("/", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x36:
            kprint("Rshift", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x37:
            kprint("Keypad *", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x38:
            kprint("LAlt", VGA_COLOR(BLACK, WHITE));
            break;
        case 0x39:
            kprint("Spc", VGA_COLOR(BLACK, WHITE));
            break;
        default:
            /* 'keyup' event corresponds to the 'keydown' + 0x80 */
            if (scancode <= 0x7f) 
            {
                kprint("Unknown key down", VGA_COLOR(BLACK, WHITE));
            } 
            else if (scancode <= 0x39 + 0x80) 
            {
                kprint("key up ", VGA_COLOR(BLACK, WHITE));
                print_letter(scancode - 0x80);
            } 
            else 
            {
                kprint("Unknown key up", VGA_COLOR(BLACK, WHITE));
            }
            break;
    }
}
