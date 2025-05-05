#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>



struct myStruct {
    int n;
    double x;
    double y;
};

int main(int argc, char **argv)
{
    char *str = "1324.25233"; // some string here
    char *endptr;

    double x;
    x = strtod(str, &endptr);
    if (*endptr != '\0')
    fprintf(stderr, "your string has trailing junk!\n");
    else
    printf("the number is %g\n", x);

}
