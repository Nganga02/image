#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "wavelet.h"
static void test_vector(int n)
{
    double *v;

    make_vector(v, n);
    for (int i = 0; i < n; i++)
        v[i] = 1.0/(1+i);

    printf("original vector:\n");
    print_vector("%8.4f ", v, n);

    haar_transform_vector(v, n, WT_FWD);
    printf("transformed vector:\n");
    print_vector("%8.4f ", v, n);

    haar_transform_vector(v, n, WT_REV);
    printf("reconstructed vector:\n");
    print_vector("%8.4f ", v, n);

    free_vector(v);

}
static void test_matrix(int m, int n)
{
    double **a;
    int i, j;

    make_matrix(a, m, n);

    for(i=0; i < m; i++ ){
        for(j = 0; j < n; j++){
            a[i][j] = 1.0/(1+i+j);
        }
    }

    printf("original matrix:\n");
    print_matrix("%8.4f ", a, m, n);

    haar_transform_matrix(a, m, n, WT_FWD);
    printf("transformed matrix:\n");
    print_matrix("%8.4f ", a, m, n);

    haar_transform_matrix(a, m, n, WT_REV);
    printf("reconstructed matrix:\n");
    print_matrix("%8.4f ", a, m, n);


    if (a) free_matrix(a);
}
/*int main(void)
{
    test_vector(8); // test an 8-vector
    test_matrix(4,8); // test a 4×8 matrix
    return 0;
}
*/
