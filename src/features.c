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
void max_component(char *source_path, char component) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    int max_value = -1; 
    int max_x_component = 0, max_y_component = 0 ;

    for (int y = 0; y < height ; y++ ) { 
        for (int x = 0; x < width; x++) {
            pixelRGB* pixel = get_pixel(data, width, height, channel_count, x, y);
            int value ;

            if (component == 'R'){
                value = pixel->R;
            } else if (component == 'G') { 
                value = pixel->G;
            } else {
                value = pixel->B;
            }

            if (value > max_value) { 
                max_value = value;
                max_x_component=x; 
                max_y_component=y;  
            }
        }

    }
    printf("max_component %c ( %d, %d ): %d", component, max_x_component , max_y_component , max_value);
}
void min_component(char *source_path, char component) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    int min_value = 256 ; 
    int min_x_component = 0, min_y_component = 0 ;

    for (int y = 0; y < height ; y++ ) { 
        for (int x = 0; x < width; x++) {
            pixelRGB* pixel = get_pixel(data, width, height, channel_count, x, y);
            int value ;

            if (component == 'R'){
                value = pixel->R;
            } else if (component == 'G') { 
                value = pixel->G;
            } else {
                value = pixel->B;
            }

            if (value < min_value) { 
                min_value = value;
                min_x_component=x; 
                min_y_component=y;  
            }
        }

    }
    printf("min_component %c ( %d, %d ): %d", component, min_x_component , min_y_component , min_value);
}
void stat_report(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    /*max_pixel*/ 
    int max_sum=-1;
    int max_x=0, max_y= 0; 
    pixelRGB max_pixel = {0, 0, 0};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
            int sum = pixel->R + pixel->G + pixel->B;

            if ( sum > max_sum ) {
                max_sum = sum;
                max_x =  x ;
                max_y = y;
                max_pixel = *pixel;
            }  
        }
    }

    /*min_pixel*/ 
    int min_sum = 256 * 3;
    int min_x = 0, min_y = 0;
    pixelRGB min_pixel = {255, 255, 255};

    for (int y=0 ; y < height; y++) {
        for (int x=0; x< width; x++) {
            pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
            int sum = pixel->R + pixel->G + pixel->B;
 
            if (sum < min_sum) {
                min_sum = sum;
                min_x=x ;
                min_y=y;
                min_pixel = *pixel;
            }
        }
    }

    /*min_component and max_component*/ 
    int max_value_R =-1 , max_value_G = -1, max_value_B = -1; 
    int max_x_R = 0, max_y_R = 0, max_x_G = 0, max_y_G = 0, max_x_B = 0, max_y_B = 0;
    int min_value_R=256, min_value_G=256, min_value_B=256;
    int min_x_R = 0, min_y_R  = 0,min_x_G = 0, min_y_G = 0, min_x_B = 0, min_y_B = 0;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);

            /*component R*/ 
            if (pixel->R>max_value_R) {
                max_value_R = pixel->R;
                max_x_R =x;
                max_y_R = y;
            }
            if (pixel->R < min_value_R) {
                min_value_R = pixel->R ;
                min_x_R=x ;
                min_y_R=y ;
            }
 
            /*component G*/ 
            if (pixel->G > max_value_G) {
                max_value_G = pixel->G;
                max_x_G= x;
                max_y_G = y;
            }
            if (pixel->G < min_value_G) {
                min_value_G = pixel->G;
                min_x_G = x;
                min_y_G= y;
            }

            /*component B*/  
            if ( pixel->B > max_value_B ) {
                max_value_B= pixel->B;
                max_x_B=x;
                max_y_B=y ;
            }
            if (pixel->B < min_value_B) {
                min_value_B = pixel->B;
                min_x_B =x;
                min_y_B = y;
            }
        }
    } 

    FILE *fp = fopen("stat_report.txt", "w");

    fprintf(fp, "max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, max_pixel.R, max_pixel.G, max_pixel.B) ;
    fprintf(fp, "min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, min_pixel.R, min_pixel.G, min_pixel.B) ; 
    fprintf(fp, "max_component R (%d, %d): %d\n", max_x_R , max_y_R, max_value_R); 
    fprintf(fp, "max_component G (%d, %d): %d\n", max_x_G, max_y_G, max_value_G) ;
    fprintf(fp, "max_component B (%d, %d): %d\n", max_x_B, max_y_B, max_value_B) ;  
    fprintf(fp, "min_component R (%d, %d): %d\n", min_x_R , min_y_R, min_value_R) ; 
    fprintf(fp, "min_component G (%d, %d): %d\n", min_x_G, min_y_G, min_value_G) ;
    fprintf(fp, "min_component B (%d, %d): %d\n", min_x_B, min_y_B, min_value_B) ; 

    fclose(fp);
    free_image_data(data);
}