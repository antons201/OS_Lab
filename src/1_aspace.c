#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5; //локальная переменная целочисленного типа
    void *p = malloc(128); //динамическое выделение памяти(128 байт)
    void *p2 = malloc(256); //динамическое выделение памяти(256 байт)
    int newLocal = 25; //локальная переменная целочисленного типа
    int s = 5;

    printf ("Address of main is %p\n", main); // печать адреса первой инструкции машинного языка
    printf ("Address of global is %p\n", &global); // печать адреса глобальной переменной
    printf ("Address of local is %p\n", &local); //печать адреса локальной переменной
    printf ("Address of p is %p\n", p); // печать адреса, который вернул malloc
    printf ("Address of p2 is %p\n", p2); // печать адреса, который вернул второй malloc
    printf ("Address of newLocal is %p\n", &newLocal); // печать адреса второй локальной переменной

    return 0;
}