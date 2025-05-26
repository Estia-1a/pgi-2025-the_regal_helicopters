#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}
void dimension (char *source_path) {
    int width ;
    int height ;
    int channel_count ;
    unsigned char *data ;
   
    int resultat = read_image_data (source_path, &data, &width, &height, &channel_count);
    if(resultat) {
    printf("dimension: %d, %d ", width, height);
    }
    else {
     printf("erreur: ");
    }
}
void first_pixel (char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    printf("first_pixel: %d, %d, %d", data[0], data[1], data[2]);
}
void second_line(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
 
    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    printf("second_line: %d, %d, %d", data[3 * width], data[3 * width + 1],  data[3 * width + 2]);
}
void tenth_pixel (char *source_path) {
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("tenth_pixel: %d, %d, %d", data[27], data[28], data[29]);
}
void print_pixel(char *filename, int x, int y) {
    int width, height, channel_count;
    unsigned char *data;

    if (!read_image_data(filename, &data, &width, &height, &channel_count)) {
        printf("Erreur de lecture de l'image\n");
        return;
    }

    pixelRGB *px = get_pixel(data, width, height, channel_count, x, y);
    if (px == NULL) {
        printf("Coordonnées invalides ou erreur mémoire\n");
        return;
    }

    printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, px->R, px->G, px->B);
    free(px);
}
void max_pixel(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int max_sum = -1 ;
    int max_x= 0, max_y = 0;
    pixelRGB max_pixel ={0, 0, 0};

    for (int y = 0; y <height; y++) {
        for (int x = 0; x < width; x++ ) {
            pixelRGB* pixel = get_pixel(data, width, height, channel_count, x, y);
            int sum = pixel->R + pixel->G + pixel->B;

            if ( sum > max_sum) {
                max_sum = sum;
                max_x = x ; 
                max_y = y;
                max_pixel = *pixel;
            }
        }
    }
    printf("max_pixel (%d, %d): %d, %d, %d", max_x, max_y, max_pixel.R, max_pixel.G, max_pixel.B);
}
void min_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int min_sum = 256 * 3 ; 
    int min_x = 0, min_y = 0;
    pixelRGB min_pixel = {255, 255, 255};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB* pixel= get_pixel(data, width, height, channel_count, x, y);
            int sum = pixel->R + pixel ->G + pixel->B;

            if (sum < min_sum ) {
                min_sum=sum;
                min_x=x;
                min_y=y;
                min_pixel=*pixel;
            }
        }
    }
    printf("min_pixel (%d, %d): %d, %d, %d", min_x, min_y, min_pixel.R, min_pixel.G, min_pixel.B);
}