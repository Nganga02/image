#include <suitesparse/umfpack.h>
#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include "sparse.h"



/*int main(void)
{
    void *Symbolic, *Numeric;
    double **a;
    double *b, *x, *Ax;
    int *Ap, *Ai;
    int n = 5;
    int i, j, nz = 0;
    make_matrix(a, n, n);
    make_vector(b, n);
    make_vector(x, n);

    double demo_mat[5][5] =
    {
        {2, 3, 0, 0, 0},
        {3, 0, 4, 0, 6},
        {0, -1, -3, 2, 0},
        {0, 0, 1, 0, 0},
        {0, 4, 2, 0, 1}
    };

    double demo_vec[5] = {8, 45, -3, 3, 19};

    //Assigning the values of double matrix A with the given sparse matrix

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = demo_mat[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = demo_vec[i];
    }

    //Computing the non-zeroes of the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                nz++;
            }
        }
    }

    //Printing the matrix and vector
    print_matrix("%.0f ",a , n, n);
    print_vector("%.0f ", b, n, true);
    //Printing the address of the Ap, Ai and Ax pointers


    custom_sparse_pack(a, n, n, &Ap, &Ai, &Ax);


    printf("Ap =");
    print_vector("%d ", Ap, n+1, false);
    printf("Ai =");
    print_vector("%d ", Ai, nz, false);
    printf("Ax =");
    print_vector("%.0f ", Ax, nz, false);


    umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
    umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
    umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);

    print_vector("%.0f ", x, n, true);

    umfpack_di_free_symbolic(&Symbolic);
    umfpack_di_free_numeric(&Numeric);


    if (Ap) free_vector(Ap);
    if (Ai) free_vector(Ai);
    if (Ax) free_vector(Ax);
    if (b) free_vector(b);
    if (x) free_vector(x);
    if (a) free_matrix(a);

    return 0;
}
*/

