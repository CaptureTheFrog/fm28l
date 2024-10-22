#ifndef FM28L_DRAW_H
#define FM28L_DRAW_H

#include <stddef.h>
#include "font.h"

enum draw_justify {
    left, centre, right
};

enum draw_fill_mode {
    outline_only, fill
};

void draw_text(volatile unsigned char *buffer, struct font *font, char *text, size_t n, unsigned int x, unsigned int y,
               enum draw_justify justify);

void
draw_text_const(volatile unsigned char *buffer, struct font *font, const char *text, unsigned int x, unsigned int y,
                enum draw_justify justify);

void draw_printf(volatile unsigned char *buffer, struct font *font, unsigned int x, unsigned int y,
                 enum draw_justify justify, const char *fmt, ...);

void draw_glyph(volatile unsigned char *buffer, struct font *font, char c, unsigned int x, unsigned int y);

void draw_line_horizontal(volatile unsigned char *buffer, unsigned int x1, unsigned int x2, unsigned int y,
                          unsigned char pixel);

void draw_line_vertical(volatile unsigned char *buffer, unsigned int x, unsigned int y1, unsigned int y2,
                        unsigned char pixel);

void draw_rectangle(volatile unsigned char *buffer, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2,
                    enum draw_fill_mode, unsigned char outline_pixel, unsigned char fill_pixel);

void draw_pixel(volatile unsigned char *buffer, unsigned int x, unsigned int y, unsigned char pixel);

void fill_screen(volatile unsigned char *buffer, unsigned char pixel);

unsigned int get_text_width_const(struct font *font, const char *text);

unsigned int get_text_width(struct font *font, char *text, size_t n);


#endif //FM28L_DRAW_H
