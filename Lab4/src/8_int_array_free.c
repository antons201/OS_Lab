#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *data = (int*)malloc(100 * sizeof(int)); //создание массива целых на 100 элементов, с ииспользованием malloc

    free(data); // освобождаем массив

    printf("Value data[1]: %d \n", data[1]); // печать 1 элемента массива

    return 0;
}