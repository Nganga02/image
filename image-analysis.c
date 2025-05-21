#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


#include "image-io.h"
#include "wavelet.h"
#include "malloc.h"


#define FACTOR 0.000001


static double bisec_algo(double **a, int m, int n, double initial_t, double minimum, double maximum, double req_abs_error, double bisec_range, double norm)
/*
* This line of code has some bugs regards the return value of the function


* TODO //
* You are supposed to clean the code and make sure it's returning the right value
*/
{
    double abs_err, next_t = 0.0;

    for (int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double value = fabs(a[i][j]);
            if(value < initial_t)
            {
                abs_err += (value * value);
            }
        }
    }

    abs_err = sqrt(abs_err);

    printf("#####This is the maximum value %f\n", maximum);
    printf("#####This is the minimum value %f\n", minimum);
    printf("#####This is the absolute err %f\n", abs_err);
    printf("#####This is the required absolute err %f\n", req_abs_error);
    printf("#####This is the norm %f\n", norm);
    printf("#####This is the relative err %f\n\n", (abs_err/norm));

    if (bisec_range <= FACTOR * norm)d
    {
        return initial_t;
    }

    if((abs_err > req_abs_error) && (bisec_range > FACTOR*norm))
    {
        bisec_range = initial_t - minimum;
        next_t = (minimum + initial_t)/2;
        bisec_algo(a, m, n, next_t, minimum, initial_t, req_abs_error, bisec_range, norm);
    }
    else if((abs_err < req_abs_error) && (bisec_range > FACTOR*norm))
    {
        bisec_range = maximum - initial_t;
        next_t = (maximum + initial_t)/2;
        bisec_algo(a, m, n, next_t, initial_t, maximum, req_abs_error, bisec_range, norm);
    }
    else
    {
        return next_t;
    }
}


static int prune_matrix(double **a, int m, int n, double rel_err)
{
    double min_val, max_val = fabs(a[0][0]);
    double norm2 = 0.0;

    for (int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double value = fabs(a[i][j]);
            if(value > max_val) max_val = value;
            if(value < min_val) min_val = value;

            norm2 += (value*value);
        }
    }

    double req_abs_err2 = sqrt(norm2*rel_err*rel_err);
    norm2 = sqrt(norm2);

    /*
    * We are going to find the right t so as to achieve a relative error that corresponds to the given relative error in the function argument
    */

    double t0 = (max_val + min_val)/2;
    double range = max_val - min_val;

    double opt_t = bisec_algo(a, m, n, t0, min_val, max_val, req_abs_err2, range, norm2);
    printf("^^^^^^^^^^^^^This is the optimum t: %f\n", opt_t);
    int zero_entries = 0;

    for (int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double value = fabs(a[i][j]);
            if(value < opt_t)
            {
                a[i][j] = 0;
                zero_entries ++;
            }
        }
    }
    return zero_entries;
}


static void clip_matrix(double **a, int m, int n, int M)
{
    for (int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(a[i][j] < 0) a[i][j] = 0;
            else if(a[i][j] > M) a[i][j] = M;
            else
            {
                (int) (a[i][j] += 0.5);
            }
        }
    }

}

static void reduce_pgm_image(struct image *img, double rel_err)
{
    int m = img -> pam.height;
    int n = img -> pam.width;
    int M = img -> pam.maxval;
    int zero_count;
    haar_transform_matrix(img -> g, m, n, WT_FWD);
    zero_count = prune_matrix(img -> g, m, n, rel_err);
    printf("********** Zero counts: %d", zero_count);
    haar_transform_matrix(img -> g, m, n, WT_REV);
    clip_matrix(img -> g, m, n, M);

    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
            zero_count, m*n, m*n - zero_count);
}

static void reduce_ppm_image(struct image *img, double rel_err)
{
    int m = img ->pam.height;
    int n = img ->pam.width;
    int M = img ->pam.maxval;
    double **T;
    int zero_count;
    printf("Image dimensions: m = %d, n = %d\n", m, n);
    assert(img->r != NULL);

    haar_transform_matrix(img ->r, m, n, WT_FWD);
    haar_transform_matrix(img ->g, m, n, WT_FWD);
    haar_transform_matrix(img ->b, m, n, WT_FWD);


    make_matrix(T, m, n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double r = img->r[i][j];
            double g = img->g[i][j];
            double b = img->b[i][j];

            double ms = (r*r + g*g + b*b)/3.0;
            T[i][j] = sqrt(ms);

        }
    }


    zero_count = prune_matrix(T, m, n, rel_err);
    printf("********** Zero counts: %d", zero_count);


    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(T[i][j] == 0)
            {
                img->r[i][j] = 0;
                img->g[i][j] = 0;
                img->b[i][j] = 0;
            }

        }
    }


    haar_transform_matrix(img -> r, m, n, WT_REV);
    haar_transform_matrix(img -> g, m, n, WT_REV);
    haar_transform_matrix(img -> b, m, n, WT_REV);


    clip_matrix(img -> r, m, n, M);
    clip_matrix(img -> g, m, n, M);
    clip_matrix(img -> b, m, n, M);


    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
            zero_count, m*n, m*n - zero_count);
}

void show_usage(char *progname)
{
    fprintf(stderr, "Usage: %s rel_err infile outfile\n \t \t0.0 ≤ rel_err ≤ 1.0\n \t  \
    1. Reads a pgm/ppm image or file\n \t \
    2. Applies the Haar wavelet transform\n \t\
    3. Sets as many of the smallest wavelet coefficients to zero as possible while keeping the relative error (in the L^2 norm) just under rel_err\n \t \
    4. Reconstructs image with the truncated coefficients and writes to outfile", progname);
}

int main(int argc, char** argv)
{
    char *infile, *outfile, *endptr;
    double rel_err;


    if (argc != 4)
    {
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    rel_err = strtod(argv[1], &endptr);
    if (*endptr != '\0' || rel_err < 0.0 || rel_err > 1.0)
    {
        fprintf(stderr, "*** the rel_err argument should be "
                "between 0.0 and 1.0\n");
        return EXIT_FAILURE;
    }
    infile = argv[2];
    outfile = argv[3];

    pm_init(argv[0], 0);
    struct image *img = read_image(infile);
    struct pam *pam = &img -> pam;
    if (pam -> format == PGM_FORMAT || pam -> format == RPGM_FORMAT)
        reduce_pgm_image(img, rel_err);
    else if (pam -> format == PPM_FORMAT || pam -> format == RPPM_FORMAT)
        reduce_ppm_image(img, rel_err);
    else
    {
        fprintf(stderr, "*** file %s, line %d: shouldn’t be here\n",
                __FILE__, __LINE__);
        return EXIT_FAILURE;
    }

    write_image(outfile, img);
    free_image(img);
    return EXIT_SUCCESS;
}
