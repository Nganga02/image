#include <stdio.h>
#include <stdlib.h>
#include "fetch_line.h"
#define BUFLEN 50


/*int main(void){
    char buf[BUFLEN];
    char *s;
    int lineno = 0;
    FILE *file = fopen("profile.txt", "r" );
    if (file != NULL)
    {
        while((s = fetch_line(buf, BUFLEN, file, &lineno))!= NULL)
        {
            printf("hello world");
            printf("trimmed line %3d: %s\n", lineno, s);
        }
        fclose(file);

    }else
    {
        perror("Unable to open file");
    }
    return 0;
}
*/
