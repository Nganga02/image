#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"

/*int main(void)
{

    int m = 4, n = 5;

    //Ensuring that the matrix is of the correct form
    double **matrix;
    matrix = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }

    // Example matrix
    double mat[4][5] =
    {
        {0, 7, 0, 0, 1},
        {0, 4, 0, 3, 0},
        {6, 6, 5, 1, 4},
        {5, 5, 0, 0, 0}
    };

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = mat[i][j];
        }
    }

    int **A_mat = sparse_pack(matrix, m, n);

    printf("Ap = [");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", A_mat[0][i]);
    }
    printf("]\n");

    printf("Ai = [");
    for (int i = 0; i < 11; i++)
    {
        printf("%d ", A_mat[1][i]);
    }
    printf("]\n");

    printf("Ax = [");
    for (int i = 0; i < 11; i++)
    {
        printf("%d ", A_mat[2][i]);
    }
    printf("]\n");

    // Free allocated memory
    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(A_mat[0]);
    free(A_mat[1]);
    free(A_mat[2]);
    free(A_mat);

    return 0;

}
*/
