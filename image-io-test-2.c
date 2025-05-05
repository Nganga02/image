#include <stdio.h>
#include "image-io.h"
/*
* This code is to convert a ppm to a pgm using everaging method
* We are implementing this through taking the average value of the pixels rgb values for every pixel in the image
*
*/



/*int main(int argc, char **argv)
{


    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        fprintf(stderr, "Reads PGM or PPM from infile, "
                "writes identical image to outfile\n");
        return EXIT_FAILURE;
    }
    pm_init(argv[0], 0);
    printf("this is the filename %s\n\n", argv[1]);
    struct image *img = read_image(argv[1]);
    fprintf(stderr, "image is %dx%d, depth=%d, maxval=%d\n",
            img -> pam.height, img -> pam.width,
            img -> pam.depth, (int)img -> pam.maxval);

    printf("Width: %d\n", img->pam.width);
    printf("Height: %d\n", img->pam.height);



    for(int i = 0; i < img->pam.height; i++){
        double width = (double) img->pam.width-1;
        double height = (double) img->pam.height-1;

        int j = 0.5 + i*(width/height);
        img->r[i][j] = 0;
        img->g[i][j] = 0;
        img->b[i][j] = 0;

        j = width - i*(width/height);
        img->r[i][j] = 0;
        img->g[i][j] = 0;
        img->b[i][j] = 0;

    }

    write_image(argv[2], img);

    free_image(img);
    return EXIT_SUCCESS;
}
*/


