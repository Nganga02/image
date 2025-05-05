#include <stdio.h>
#include <stdlib.h>
#include <time.h>



inline int Random(int n)
{
    return (rand()/(RAND_MAX/n + 1));
}

//Providing a non-inline definition for the linker
int Random(int n);


/*int main(void)
{
    int result = Random(5);
    printf("this are the results: %d", result);
    return 0;
}*/
