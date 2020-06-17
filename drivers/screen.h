#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define VGA_COLOR(BACKCOLOR, FORECOLOR) ((BACKCOLOR << 4) | FORECOLOR)
enum SCREEN_COLOR {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, 
LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGNETA, YELLOW, WHITE};

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void kprint_at(const char *message, int row, int col, unsigned char attribute_byte);
void kprint(const char *message, unsigned char attribute_byte);
void kprint_back(void);
void clear_screen(void);

#endif