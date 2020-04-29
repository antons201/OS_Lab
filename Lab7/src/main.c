#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define UPPER 0
#define LOW 1

void change(char* str, int countChange, int typeChange) { //функция смены регистра
    while (countChange >= 8) { //пока в строке больше восьми символов
        if (typeChange == UPPER) // если меняем регистр с нижнего на верхний
            *((uint64_t *)str) &= 0b1101111111011111110111111101111111011111110111111101111111011111; //обнуляем бит на каждой позиции, кратной 6
        if (typeChange == LOW) //если меняем регистр с верхнего на нижний
            *((uint64_t *)str) |= 0b0010000000100000001000000010000000100000001000000010000000100000; //устанавливаем бит на каждой позиции, кратной 6
        countChange -= 8; //уменьшаем счетчик букв, которые необходимо изменить
        str += 8; //сдвигаем указатель
    }
    while (countChange >= 4) { //пока в строке больше четырёх символов
        if (typeChange == UPPER) // если меняем регистр с нижнего на верхний
            *((uint32_t *)str) &= 0b11011111110111111101111111011111; //обнуляем бит на каждой позиции, кратной 6
        if (typeChange == LOW) //если меняем регистр с верхнего на нижний
            *((uint32_t *)str) |= 0b00100000001000000010000000100000; //устанавливаем бит на каждой позиции, кратной 6
        countChange -= 4; //уменьшаем счетчик букв, которые необходимо изменить
        str += 4;//сдвигаем указатель
    }

    while (countChange >= 1) { //пока в строке больше одного символа
        if (typeChange == UPPER) // если меняем регистр с нижнего на верхний
            *str &= 0b11011111; //обнуляем бит на 6 позиции
        if (typeChange == LOW) //если меняем регистр с верхнего на нижний
            *str |= 0b00100000; //устанавливаем бит на 6 позиции
        countChange--; //уменьшаем счетчик букв, которые необходимо изменить
        str++;//сдвигаем указатель
    }
}

void readStr(char* str, char* strExpected) { //функция для чтения строки и вызова функции смены регистра
    unsigned int len = strlen(str); //изначальная длина строки
    int countUpper = 0; //счетчик заглавных букв
    int countLow = 0; //счетчик строчных букв
    while (*str != '\0') { //пока не конец строки
        if (*str >= 'a' && *str <= 'z') { //если строчная буква
            countLow++; //увеличиваем счетчик
            if (countUpper != 0) { //если счетчик заглавных букв не равен нулю
                change(str-countUpper, countUpper, LOW); //вызываем функцию смены регистра для последовательности заглавных букв
                countUpper = 0; //обнуляем счетчик заглавных букв
            }
        } else if (*str >= 'A' && *str <= 'Z') { // если заглавная буква
            countUpper++; //увеличиваем счетчик
            if (countLow != 0) { //если счетчик строчных букв не равен нулю
                change(str-countLow, countLow, UPPER); //вызываем функцию смены регистра для последовательности строчных букв
                countLow = 0; //обнуляем счетчик строчных букв
            }
        } else { //если не буква
            countUpper ? change(str-countUpper, countUpper, LOW) : change(str-countLow, countLow, UPPER); /*
            вызываем функцию смены регистра для последовательности строчных или заглавных букв*/
            countUpper = countLow = 0; //обнуляем счетчики
        }

        str++; //увеличиваем указатель
    }
    countUpper ? change(str-countUpper, countUpper, LOW) : change(str-countLow, countLow, UPPER);/*
    вызываем функцию смены регистра для последовательности оставшихся строчных или заглавных букв*/
    str-= len; // возвращаем указатель на начало строки
    if (strcmp(str, strExpected) == 0) { //проверка на совпадение исходной и ожидаемой строк
        printf("True %s == %s\n", str, strExpected); //печатаем если совпало
    } else {
        printf("False %s != %s\n", str, strExpected); //печатаем если не совпало
    }
}

int main() {
    char str1[] = "ABCDhhE0FGHHH 45, qqqqqqqq8hQ"; //строка для теста 1
    char str2[] = "aaaaaAAAAAAA0SSSSSqqqqqq"; //строка для теста 2
    char str3[] = "jdGfGgu845iguYjf849ifR934idfgj93K4340GпGж"; //строка для теста 3
    readStr(str1, "abcdHHe0fghhh 45, QQQQQQQQ8Hq"); //тест 1
    readStr(str2, "AAAAAaaaaaaa0sssssQQQQQQ"); //тест 2
    readStr(str3, "JDgFgGU845IGUyJF849IFr934IDFGJ93k4340gпgж"); //тест 3
    return 0;
}
