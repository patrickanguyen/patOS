#include "screen.h"
#include "ports.h"

void print_char(char character, int col, int row, char attribute_byte);
void clear_screen();
int get_screen_offset(int row,  int col);
int get_cursor_offset(void);
void set_cursor_offset(int offset);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint_at(char *message, int row, int col)
{
    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(row, col);
    }
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    char* letter = message;
    while (*letter != '\0') {
        print_char(*letter, row, col, WHITE_ON_BLACK);

        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
        ++letter;
    }
}

void kprint(char *message)
{
    kprint_at(message, -1, -1);
}

void print_char(char character, int row, int col, char attribute_byte)
{
    unsigned char *video_mem = (unsigned char*) VIDEO_ADDRESS;

    /* If attribute byte is 0, assume default*/
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(row, col);
    }
    else {
        offset = get_cursor_offset();
    }

    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(rows, MAX_COLS - 1);
    }
    else {
        video_mem[offset] = character;
        video_mem[offset + 1] = attribute_byte;
    }

    offset += 2;
    /*offset = handle_scrolling(offset);*/
    set_cursor_offset(offset);
}

void clear_screen(void)
{
    int screen_size = MAX_COLS * MAX_ROWS;
    char *video_mem = (char*)VIDEO_ADDRESS;

    int i;
    for (i = 0; i < screen_size; ++i) {
        video_mem[i * 2] = ' ';
        video_mem[2*i + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_screen_offset(0,0));
}

int get_screen_offset(int row,  int col)
{
    return 2 * (row * MAX_COLS + col);
}

int get_cursor_offset(void) 
{
    /* Use VGA ports to get cursor pos */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;

    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}