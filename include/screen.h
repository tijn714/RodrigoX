#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

extern uint16_t cursor_x;
extern uint16_t cursor_y;
extern uint8_t fg_color;
extern uint8_t bg_color;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
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
void clear_screen(uint8_t color);

void set_cursor(uint16_t x, uint16_t y);

void draw_pixel(uint16_t x, uint16_t y, uint8_t color);
void kputchar(char c, uint16_t x, uint16_t y, uint8_t fg, uint8_t bg);

void kprint(char *str, ...);
void kserial(uint8_t fg, uint8_t bg, char *str, ...);

#endif /* SCREEN_H */