#include <stdio.h>
#include <zconf.h>
#include <stdint.h>
#include <sys/time.h>
#include "crc8.h"

void create_csum(char *fileNameIn, char *fileNameOut) {
    unsigned long readSize; //размер считанного блока
    int n = 4096; // размер блока
    unsigned char buff[n]; //будер для считывания
    unsigned char crc; //чексумма

    FILE *ReadFile = fopen(fileNameIn, "r"); //открываем файл
    if (ReadFile == NULL) { //проверяем успешность открытия
        exit(1);
    }

    FILE *WriteFile = fopen(fileNameOut, "w"); //открываем файл
    if (WriteFile == NULL) { //проверяем успешность открытия
        exit(1);
    }

    while ((readSize = fread(&buff, 1, n, ReadFile)) != 0) { //считаем блоками пока не кончистя файл
        crc = crc8(buff, readSize); //вычисляем чексумму
        fprintf(WriteFile, "%c", crc); //записываем в файл
    }

    fclose(ReadFile); //закрываем файл
    fclose(WriteFile); //закрываем файл
}

int main() {
    create_csum("../tests/test1.txt", "../tests/CsumTest1.txt"); //Тест 1
    create_csum("../tests/test2.txt", "../tests/CsumTest2.txt"); //Тест 2
    create_csum("../tests/test3.txt", "../tests/CsumTest3.txt"); //Тест 3
    create_csum("../tests/test4.txt", "../tests/CsumTest4.txt"); //Тест 4
    return 0;
}
