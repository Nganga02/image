#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"



//Providing a non-inline definition for the linker
static int Random(int n);


static inline int Random(int n)
{
    return rand()/(RAND_MAX/n + 1);
}
static int write_pbm(char **M, int m, int n, char *outfile)
{
    FILE *file = fopen(outfile, "w");
    if(file != NULL)
    {
        printf("file is already open\n");
        fputs("P1",file);
        fputs("\n", file);
        fprintf(file, "%d %d",m,n);
        fputs("\n", file);
        for(int i = 0; i < m; i++)
        {
            printf("I am writing the %d line of the matrix\n", i+1);
            for(int j = 0; j < n; j++)
            {
                fprintf(file, "%c", M[i][j] ? 35 : 32);
            }

            fputs("\n", file);
        }


        fclose(file);
        file = NULL;
        return 1;

    }
    else
    {
        fprintf(stderr, "Couldn't open the file");
        return 0;
    }
}
static char **make_random_matrix(int m, int n, double f)
{
    char **M;
    int i, j, k;
    make_matrix(M, m, n);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            M[i][j] = 0;
        }
    }
    k = 0;
        while(k < f*m*n)
    {
        i = Random(m);
        j = Random(n);

        if(M[i][j]==0)
        {
            M[i][j] = 1;
            k++;
        }
    }
    return M;

}
static void show_usage(char *progname)
{
    //Prints the error into the stderr file which is used to print error
    fprintf(stderr, "Usage: %s m n s f outfile\n writes an mxn bitmap to a file named 'outfile'\n f: fill ratio 0.0 <= f <= 1.0\n s: integer >= 1: seeds the random integer generator", progname);

}
/*int main(int argc, char **argv)
{
    int m, n, s; //the image is of dimension mxn and the seed is s
    double f; //Fill ratio
    char **M;
    char *outfile;
    char *endptr;
    int status = EXIT_FAILURE;

    if(argc != 6)
    {
        printf("+++++++++   There are very few arguments    ++++++++++\n");
        printf("This is the value of the argument count %d\n", argc);
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    m = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || m < 1)
    {
        printf("+++++++++   I did not receive the second command line argument  +++++++++\n");
        show_usage(argv[1]);
        return status;
    }
    n = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || n < 1)
    {
        printf("+++++++++   I did not receive the third command line argument  +++++++++\n");
        show_usage(argv[2]);
        return status;
    }
    s = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || s < 1)
    {
        printf("+++++++++   I did not receive the forth command line argument  +++++++++\n");
        show_usage(argv[3]);
        return status;
    }
    f = strtod(argv[4], &endptr);
    if (*endptr != '\0' || f > 1)
    {
        printf("+++++++++   I did not receive the fifth command line argument  +++++++++\n");
        show_usage(argv[4]);
        return status;
    }
    outfile = argv[5];
    if (*outfile == NULL)
    {
        printf("+++++++++   I did not receive the fifth command line argument  +++++++++\n");
        show_usage(argv[4]);
        return status;
    }


    srand(s);
    M = make_random_matrix(m, n, f);
    if(write_pbm(M, m, n, outfile))
    {
        status = EXIT_SUCCESS;
    }
    free_matrix(M);
    return status;

}
*/
