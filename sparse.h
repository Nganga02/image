#ifndef H_SPARSE_H
#define H_SPARSE_H

void custom_sparse_pack(double **a, int m, int n, int **Ap, int **Ai, double **Ax);
void custom_sparse_unpack(double **a, int m, int n, int *Ap, int *A);

#endif // H_SPARSE_H
