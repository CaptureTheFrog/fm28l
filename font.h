#ifndef FM28L_FONT_H
#define FM28L_FONT_H

#define ROUND_UP_TO_MULTIPLE_OF_8(x) (((x) + 7) & ~7)

struct glyph{
    unsigned char width;
    unsigned char height;
    unsigned char descender_offset;
    unsigned char bitmap[32];
};

struct font{
    unsigned char max_width;
    unsigned char max_height;
    unsigned char cap_height;
    char name[256];
    struct glyph glyphs[256];
};

int write_font(const char* filename, const struct font* f);
int read_font(const char* filename, const struct font* f);
int crop_glyph(struct glyph* glyph, unsigned char width, unsigned char height);

#endif //FM28L_FONT_H
