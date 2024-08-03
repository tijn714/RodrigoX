#include "screen.h"
#include "memory.h"
#include "font.h"
#include "io_ports.h"
#include <stdarg.h>

enum color fg_color;
enum color bg_color;

uint16_t cursor_x;
uint16_t cursor_y;


void set_cursor(uint16_t x, uint16_t y) {
    uint16_t pos = y * SCREEN_WIDTH + x;

    outportb(VGA_CRTC_INDEX, 0x0E);
    outportb(VGA_CRTC_DATA, (uint8_t) (pos >> 8));
    outportb(VGA_CRTC_INDEX, 0x0F);
    outportb(VGA_CRTC_DATA, (uint8_t) (pos & 0xFF));
}

void set_color(enum color fg, enum color bg) {
    fg_color = fg;
    bg_color = bg;
}

void set_video_mode() {
    asm("movb $0x00, %ah");
    asm("movb $0x12, %al");
}

void set_miscellaneous_registers() {
    outportb(VGA_MISC_WRITE, 0x63);
}

void set_sequencer_registers() {
    outportb(VGA_SEQ_INDEX, 0);
    outportb(VGA_SEQ_DATA, 0x03);

    outportb(VGA_SEQ_INDEX, 1);
    outportb(VGA_SEQ_DATA, 0x01);

    outportb(VGA_SEQ_INDEX, 2);
    outportb(VGA_SEQ_DATA, 0x0F);

    outportb(VGA_SEQ_INDEX, 3);
    outportb(VGA_SEQ_DATA, 0x00);

    outportb(VGA_SEQ_INDEX, 4);
    outportb(VGA_SEQ_DATA, 0x0E);
}

void set_graphics_controller_registers() {
    outportb(VGA_GC_INDEX, 0);
    outportb(VGA_GC_DATA, 0x00);

    outportb(VGA_GC_INDEX, 1);
    outportb(VGA_GC_DATA, 0x00);

    outportb(VGA_GC_INDEX, 2);
    outportb(VGA_GC_DATA, 0x00);

    outportb(VGA_GC_INDEX, 3);
    outportb(VGA_GC_DATA, 0x00);

    outportb(VGA_GC_INDEX, 4);
    outportb(VGA_GC_DATA, 0x00);

    outportb(VGA_GC_INDEX, 5);
    outportb(VGA_GC_DATA, 0x40);

    outportb(VGA_GC_INDEX, 6);
    outportb(VGA_GC_DATA, 0x05);

    outportb(VGA_GC_INDEX, 7);
    outportb(VGA_GC_DATA, 0x0F);

    outportb(VGA_GC_INDEX, 8);
    outportb(VGA_GC_DATA, 0xFF);
}

void set_attribute_controller_registers() {
    uint8_t d;
    uint8_t ac_data[21] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                           0x41, 0x00, 0x0F, 0x00, 0x00};

    for (uint8_t index = 0; index < 21; index++) {
        outportb(VGA_AC_INDEX, index);
        outportb(VGA_AC_WRITE, ac_data[index]);
    }
    d = inportb(VGA_INSTAT_READ);
    outportb(VGA_AC_INDEX, d | 0x20);
}

void set_crt_controller_registers() {
    uint8_t crtc_data[25] = {0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
                             0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3, 0xFF};
    
    for (uint8_t index = 0; index < 25; index++) {
        outportb(VGA_CRTC_INDEX, index);
        outportb(VGA_CRTC_DATA, crtc_data[index]);
    }
}

void init_vga_registers() {
    set_miscellaneous_registers();
    set_sequencer_registers();
    set_graphics_controller_registers();
    set_attribute_controller_registers();
    set_crt_controller_registers();
}

void init_screen() {
    set_video_mode();
    init_vga_registers();
    cursor_x = 0;
    cursor_y = 0;
    fg_color = YELLOW;
    bg_color = BLACK;
    clear_screen(bg_color);
}

void clear_screen(enum color color) {
    uint8_t *screen = (uint8_t *) SCREEN_MEMORY;
    for (uint32_t i = 0; i < SCREEN_SIZE; i++) {
        screen[i] = color;
    }
}

void draw_pixel(uint16_t x, uint16_t y, enum color color) {
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) return;
    uint8_t *screen = (uint8_t *) SCREEN_MEMORY;
    screen[y * SCREEN_WIDTH + x] = color;
}

void font_char(char c, uint16_t x, uint16_t y, enum color color) {
    const uint8_t *glyph = font[(size_t)c];

    // Draw each pixel of the character glyph
    for (size_t yy = 0; yy < FONT_HEIGHT; yy++) {
        for (size_t xx = 0; xx < FONT_WIDTH; xx++) {
            if (glyph[yy] & (1 << xx)) {
                draw_pixel(x + xx, y + yy, color);
            }
        }
    }
}

void kputchar(char c, uint16_t x, uint16_t y, enum color fg, enum color bg) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y += FONT_HEIGHT;
    } else if (c == '\r') {
        cursor_x = 0;
        // flush the line
        for (size_t i = cursor_y; i < cursor_y + FONT_HEIGHT; i++) {
            for (size_t j = 0; j < SCREEN_WIDTH; j++) {
                draw_pixel(j, i, bg);
            }
        }
    } else if (c == '\t') {
        cursor_x += FONT_WIDTH * 4;
    } else if (c == '\b') {
        if (cursor_x >= FONT_WIDTH) {
            cursor_x -= FONT_WIDTH;
            // flush the character
            for (size_t i = cursor_y; i < cursor_y + FONT_HEIGHT; i++) {
                for (size_t j = cursor_x; j < cursor_x + FONT_WIDTH; j++) {
                    draw_pixel(j, i, bg);
                }
            }
        } else {
            cursor_x = 0;
        }
    } else {
        // Draw the character with background color first
        font_char(c, x, y, bg);

        // Then draw the character with foreground color on top
        font_char(c, x, y, fg);

        // Move cursor position to the right for the next character
        cursor_x += FONT_WIDTH;
    }
}

void kprint(char *str, ...) {
    va_list args;
    va_start(args, str);

    while (*str != '\0') {
        if (*str == '%') {
            str++;
            if (*str == 'd') {
                int num = va_arg(args, int);
                char num_str[12];
                itoa(num, num_str, 10);
                char *num_ptr = num_str;
                while (*num_ptr != '\0') {
                    kputchar(*num_ptr++, cursor_x, cursor_y, fg_color, bg_color);
                }
            } else if (*str == 'x') {
                int num = va_arg(args, int);
                char num_str[12];
                itoa(num, num_str, 16);
                char *num_ptr = num_str;
                while (*num_ptr != '\0') {
                    kputchar(*num_ptr++, cursor_x, cursor_y, fg_color, bg_color);
                }
            } else if (*str == 's') {
                char *s = va_arg(args, char *);
                while (*s != '\0') {
                    kputchar(*s++, cursor_x, cursor_y, fg_color, bg_color);
                }
            } else if (*str == 'c') {
                char c = va_arg(args, int);
                kputchar(c, cursor_x, cursor_y, fg_color, bg_color);
            }
        } else {
            kputchar(*str, cursor_x, cursor_y, fg_color, bg_color);
        }
        str++;
    }
    va_end(args);
}