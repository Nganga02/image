#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include <suitesparse/umfpack.h>


//Implementation of the sparse_pack method in C

/*
We are using a double pointer to the functions since we want to pass by reference not value
*/
void custom_sparse_pack(double **a, int m, int n, int **Ap, int **Ai, double **Ax)
{

    /*
    Remember the the size of Ap is always 1 + the number of columns in the matrix
    */
    int k = 0; //To count the number of non-zeros in the matrix

    /*
    We are calculating the cumulative value of non-zeroes in the matrix
    */
    for(int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (a[i][j] != 0)
            {
                k++;
            }
        }

    }
    //printf("This is the size of the pointer: %zu", sizeof(*Ap));
    make_vector(*Ap, n+1);
    make_vector(*Ax, k);
    make_vector(*Ai, k);
    int x = 0;
    int p = 0;

    //The first element is always 0
    (*Ap)[0] = 0;
    /*
    Assigning the value of Ap, Ax, Ai from the matrix
    */

    for(int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (a[i][j] != 0)
            {
                (*Ax)[x] = a[i][j];
                (*Ai)[x] = i;
                x++;
            }
        }
        (*Ap)[j+1] = x;
    }


    Ai = NULL;
    Ap = NULL;
    Ax = NULL;
}


void custom_sparse_unpack(double **a, int m, int n, int *Ap, int *Ai, int *Ax)
{
    int i, j, k;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i][j] = 0.0;

    for (j = 0; j < n; j++)
        for (k = Ap[j]; k < Ap[j+1]; k++)
        {
            i = Ai[k];
            a[i][j] = Ax[k];
        }
}
