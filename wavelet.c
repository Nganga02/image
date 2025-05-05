
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavelet.h"
#define SQRT1_2 0.70710678119


static void haar_transform_vector_forward(double *v, int n)
{
    double h = sqrt(n);
    int i, d;
    for (i = 0; i < n; i++)
        v[i] /= h;
    for (d = 1; d < n; d *= 2)
        for (i = 0; i < n; i += 2*d)
        {
            double x = SQRT1_2 * (v[i] + v[i+d]);
            double y = SQRT1_2 * (v[i] - v[i+d]);
            v[i] = x;
            v[i+d] = y;
        }
}

//If we accomplish this algorithm we will feel great
static void haar_transform_vector_reverse(double *v, int n)
{
    double h = sqrt(n);
    int i, d;
    for (i = 0; i < n; i++)
        v[i] *= h;


    //We are to perform the haar_transform reverse
    for (d = n/2; d > 0; d /= 2)
        for (i = 0; i < n; i += 2*d)
        {
            double x = SQRT1_2 * (v[i] + v[i+d]);
            double y = SQRT1_2 * (v[i] - v[i+d]);
            v[i] = x;
            v[i+d] = y;
        }
}
static void haar_transform_matrix_forward(double **a, int m, int n)
{
    int i,j,d;
    double h = sqrt(m);
    for (i = 0; i < m; i++)
        haar_transform_vector(a[i], n, WT_FWD);
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < m; i++)
            a[i][j] /= h;
        for (d = 1; d < m; d*=2)
            for (i = 0; i < m; i += 2*d)
            {
                double x = SQRT1_2 * (a[i][j] + a[i+d][j]);
                double y = SQRT1_2 * (a[i][j] - a[i+d][j]);
                a[i][j] = x;
                a[i+d][j] = y;
            }
    }
}
static void haar_transform_matrix_reverse(double **a, int m, int n)
{
    int i,j,d;
    double h = sqrt(m);
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < m; i++)
            a[i][j] *= h;
        for (d = m/2; d > 0; d/=2)
            for (i = 0; i < m; i += 2*d)
            {
                double x = SQRT1_2 * (a[i][j] + a[i+d][j]);
                double y = SQRT1_2 * (a[i][j] - a[i+d][j]);
                a[i][j] = x;
                a[i+d][j] = y;
            }
    }
    for (i=0; i < m; i++)
        haar_transform_vector(a[i], n, WT_REV);
}
void haar_transform_vector(double *v, int n, int dir)
{
    if (dir == WT_FWD)
        haar_transform_vector_forward(v, n);
    else if (dir == WT_REV)
        haar_transform_vector_reverse(v, n);
    else   // shouldn’t be here!
    {
        fprintf(stderr, "*** error in haar_transform_vector(): "
                "the third argument should be one of "
                "WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}
void haar_transform_matrix(double **a, int m, int n, int dir)
{
    if((m % 2 != 0) || (n % 2 != 0))
    {
        fprintf(stderr, "****** the dimension should have lengths should be factors of 2");
        exit(EXIT_FAILURE);
    }
    if (dir == WT_FWD)
        haar_transform_matrix_forward(a, m, n);
    else if (dir == WT_REV)
        haar_transform_matrix_reverse(a, m, n);
    else   // shouldn’t be here!
    {
        fprintf(stderr, "*** error in haar_transform_matrix(): "
                "the third argument should be one of "
                "WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}
