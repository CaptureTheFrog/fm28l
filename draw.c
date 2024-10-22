#define __STDC_WANT_LIB_EXT2__ 1
#define _GNU_SOURCE

#include "draw.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

unsigned int get_text_width(struct font *font, char *text, size_t n) {
    unsigned int width = 0;
    for (unsigned int i = 0; i < n && text[i] != '\0'; i++) {
        width += font->glyphs[text[i]].width;
    }
    return width;
}

unsigned int get_text_width_const(struct font *font, const char *text) {
    unsigned int width = 0;
    for (unsigned int i = 0; i < strlen(text) && text[i] != '\0'; i++) {
        width += font->glyphs[text[i]].width;
    }
    return width;
}

void draw_text(volatile unsigned char *buffer, struct font *font, char *text, size_t n, unsigned int x, unsigned int y,
               enum draw_justify justify) {
    unsigned int next_x = x;
    if (justify != left) {
        next_x -= (get_text_width(font, text, n) - 1) >> (justify == centre);
    }
    for (unsigned int i = 0; i < n && text[i] != '\0'; i++) {
        draw_glyph(buffer, font, text[i], next_x, y);
        next_x += font->glyphs[text[i]].width;
    }
}

void
draw_text_const(volatile unsigned char *buffer, struct font *font, const char *text, unsigned int x, unsigned int y,
                enum draw_justify justify) {
    draw_text(buffer, font, (char *) text, strlen(text), x, y, justify);
}

void draw_glyph(volatile unsigned char *buffer, struct font *font, char c, unsigned int x, unsigned int y) {
    for (unsigned char gy = 0; gy < font->glyphs[c].height; gy++) {
        for (unsigned char gx = 0; gx < font->glyphs[c].width; gx++) {
            draw_pixel(buffer, x + gx,
                       y + gy + (font->cap_height - font->glyphs[c].height + font->glyphs[c].descender_offset),
                       font->glyphs[c].bitmap[((gy * ((font->glyphs[c].width + 7) & ~7)) / 8) + (gx / 8)]
                               >> (7 - (gx % 8)));
        }
    }
}

void draw_line_horizontal(volatile unsigned char *buffer, unsigned int x1, unsigned int x2, unsigned int y,
                          unsigned char pixel) {
    for (unsigned int x = x1; x <= x2; x++) {
        draw_pixel(buffer, x, y, pixel);
    }
}

void draw_line_vertical(volatile unsigned char *buffer, unsigned int x, unsigned int y1, unsigned int y2,
                        unsigned char pixel) {
    for (unsigned int y = y1; y <= y2; y++) {
        draw_pixel(buffer, x, y, 1);
    }
}

void draw_rectangle(volatile unsigned char *buffer, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2,
                    enum draw_fill_mode, unsigned char outline_pixel, unsigned char fill_pixel) {
    draw_line_horizontal(buffer, x1, x2, y1, outline_pixel);
    draw_line_horizontal(buffer, x1, x2, y2, outline_pixel);
    draw_line_vertical(buffer, x1, y1 + 1, y2 - 1, outline_pixel);
    draw_line_vertical(buffer, x2, y1 + 1, y2 - 1, outline_pixel);
}

void draw_pixel(volatile unsigned char *buffer, unsigned int x, unsigned int y, unsigned char pixel) {
    if (x >= LED_COLS || y >= LED_ROWS) return;
    pixel &= 1;
    buffer[(y * (LED_COLS / 8)) + (x / 8)] &= ~(1 << (7 - (x % 8)));
    buffer[(y * (LED_COLS / 8)) + (x / 8)] |= pixel << (7 - (x % 8));
}

void draw_printf(volatile unsigned char *buffer, struct font *font, unsigned int x, unsigned int y,
                 enum draw_justify justify, const char *fmt, ...) {
    va_list args;
    char *strp;

    va_start(args, fmt);
    int len = vasprintf(&strp, fmt, args);
    if (len != -1) {
        draw_text(buffer, font, strp, len, x, y, justify);
        free(strp);
    }
    va_end(args);
}

void fill_screen(volatile unsigned char *buffer, unsigned char pixel) {
    memset((void *) buffer, (0xFF * pixel) & 0xFF, (ROUND_UP_TO_MULTIPLE_OF_8(LED_COLS) / 8) * LED_ROWS);
}