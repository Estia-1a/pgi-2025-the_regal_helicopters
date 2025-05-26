#ifndef UTILS_H
#define UTILS_H

typedef struct _pixelRGB {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} pixelRGB;

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const int x, const int y);
void print_pixel(char *filename, int x, int y);

#endif

