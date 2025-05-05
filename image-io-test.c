/*#include <stdio.h>
#include "image-io.h"

#include <unistd.h> // Linux / macOS




int main(int argc, char **argv)
{

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Running from directory: %s\n", cwd);
    printf("initializing\n\n");
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        fprintf(stderr, "Reads PGM or PPM from infile, "
                "writes identical image to outfile\n");
        return EXIT_FAILURE;
    }
    printf("initializaing pm_init\n\n");
    pm_init(argv[0], 0);
    printf("finished initializaing pm_init\n\n");
    printf("this is the filename %s\n\n", argv[1]);
    struct image *img = read_image(argv[1]);
    fprintf(stderr, "image is %dx%d, depth=%d, maxval=%d\n",
            img -> pam.height, img -> pam.width,
            img -> pam.depth, (int)img -> pam.maxval);
    write_image(argv[2], img);
    free_image(img);
    return EXIT_SUCCESS;
}*/
