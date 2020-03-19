#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *data = (int*)malloc(100 * sizeof(int)); //создание массива целых на 100 элементов, с ииспользованием malloc

    data[100] = 0; // присвоение 0 сотому элементу

    return 0;
}