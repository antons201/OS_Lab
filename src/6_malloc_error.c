#include <stdio.h>
#include <stdlib.h>

int main ()
{
    void *p = malloc(128); //динамическое выделение памяти(128 байт)

    printf ("Address of p is %p\n", p); // печать адреса, который вернул malloc


    return 0;
}