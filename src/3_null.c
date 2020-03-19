#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int *a = NULL; // создаем нулевой указатель
    printf("%d", *a); // пытаемся обратиться к нему и напечатать значение
    return 0;
}