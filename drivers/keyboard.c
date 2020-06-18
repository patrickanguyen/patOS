#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../lib/string.h"
#include "../kernel/kernel.h"
#include <stdint.h>
#include <stdbool.h>

#define RELEASED(key) (key + 0x80)

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A

#define KEY_BUFFER_MAX 256
#define SC_MAX 57

static char key_buffer[KEY_BUFFER_MAX];
static size_t key_buffer_size = 0;
static bool shift_state = false;

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

const char sc_ascii_shift[] = { '?', '?', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ':', '\"', '~', '?', '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

static void append_key_buffer(char letter);
static void remove_key_buffer(void);

static void keyboard_callback(__attribute__((unused)) registers_t *r)
{
    uint8_t scancode = port_byte_in(0x60);

    /* Check if LSHIFT is pressed */
    if (scancode == RELEASED(LSHIFT)) {
        shift_state = false;
        return;
    }
    else if (scancode == LSHIFT) {
        shift_state = true;
        return;
    }
    
    if (scancode > SC_MAX) {
        return;
    }

    /* Remove character from buffer */
    if (scancode == BACKSPACE) {
        if (key_buffer_size > 0) {
            remove_key_buffer();
            kprint_back();
        }  
    }
    /* Pass input over to kernel to handle */
    else if (scancode == ENTER) {
        kprint("\n", 0);
        handle_input(key_buffer);
        key_buffer[0] = '\0';
        key_buffer_size = 0;
    }
    /* Add character to buffer */
    else {
        if (key_buffer_size < KEY_BUFFER_MAX) {
            char letter;

            /* Undefined key */
            if (sc_ascii[scancode] == '?') {
                return;
            }

            /* Capitalize letter if LSHIFT is pressed */
            if (shift_state) {
                letter = sc_ascii_shift[scancode];
            }
            else {
                letter = sc_ascii[scancode];
            }

            append_key_buffer(letter);
            char str[] = {letter, '\0'};
            kprint(str, 0);
        }
    }
}

void init_keyboard(void)
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

static void append_key_buffer(char letter)
{
    key_buffer[key_buffer_size++] = letter;
    key_buffer[key_buffer_size] = '\0';
}

static void remove_key_buffer(void)
{
    key_buffer[--key_buffer_size] = '\0';
}