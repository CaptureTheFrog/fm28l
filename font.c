#include <stdio.h>
#include "font.h"

int write_font(const char* filename, const struct font* f) {
    // Open the file in binary write mode
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the font struct to the file
    size_t written = fwrite(f, sizeof(struct font), 1, file);
    if (written != 1) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);
    return 0;
}

int read_font(const char* filename, const struct font* f) {
    // Open the file in binary read mode
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the font struct from the file
    size_t read = fread((void *)f, sizeof(struct font), 1, file);
    if (read != 1) {
        perror("Error reading from file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);
    return 0;
}

int crop_glyph(struct glyph* glyph, unsigned char width, unsigned char height){
    struct glyph old_glyph = *glyph;

    // sanity checks
    if(old_glyph.width == width && old_glyph.height == height)
        return 0; // no crop needed
    if(((width/8)*height) > sizeof(glyph->bitmap))
        return 1; // too big for bitmap field

    // lazy crop
    glyph->width = width;
    glyph->height = height;

    if(ROUND_UP_TO_MULTIPLE_OF_8(old_glyph.width) != ROUND_UP_TO_MULTIPLE_OF_8(width) && width !=0 && height != 0){
        // oh, good. we have to do some actual maths here.
        for(int y = 0; y < old_glyph.height; y++){
            for(int x_ = 0; x_ < ((old_glyph.width < width ? old_glyph.width : width) / 8)+1; x_++){
                glyph->bitmap[(y * ((width/8)+1)) + x_] = old_glyph.bitmap[(y * ((old_glyph.width/8)+1)) + x_];
            }
        }
    }

    return 0;
}