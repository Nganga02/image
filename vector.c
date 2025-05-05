#include <stdio.h>
#include "malloc.h"
#define make_vector(v, n) ((v) = xmalloc((n)* sizeof (v)))


/*int main(void)
{
    double *x;
    make_vector(x, 100);

    for (int i = 0; i < 100; i++)
    {
        x[i] = 1.0/(1 + i);
        printf("the value of the %d th value is %f \n",i + 1, x[i]);
    }
    free_vector(x);
    printf("%d", x);
}
*/
