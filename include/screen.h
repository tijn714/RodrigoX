#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

extern uint16_t cursor_x;
extern uint16_t cursor_y;

enum color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};

extern enum color fg_color;
extern enum color bg_color;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define SCREEN_MEMORY 0xA0000

#define VGA_MISC_WRITE 0x3C2
#define VGA_SEQ_INDEX  0x3C4
#define VGA_SEQ_DATA   0x3C5
#define VGA_GC_INDEX   0x3CE
#define VGA_GC_DATA    0x3CF
#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA  0x3D5
#define VGA_AC_INDEX   0x3C0
#define VGA_AC_WRITE   0x3C0
#define VGA_INSTAT_READ 0x3DA

void init_screen();
void clear_screen(enum color color);

void draw_pixel(uint16_t x, uint16_t y, enum color color);
void kputchar(char c, uint16_t x, uint16_t y, enum color fg, enum color bg);

void kprint(char *str, ...);
void kprint_at(uint16_t x, uint16_t y, char *str, ...);
void kserial(enum color fg, enum color bg, char *str, ...);
void kserial_at(uint16_t x, uint16_t y, enum color fg, enum color bg, char *str, ...);

#endif /* SCREEN_H */
