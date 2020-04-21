#include <stdio.h>
#include <zconf.h>
#include <stdint.h>
#include <sys/time.h>
#include "crc8.h"

void check_csum(char *fileNameTest, char *fileNameCsum) {
    unsigned long readSize; //размер считанного блока
    int n = 4096; // размер блока
    unsigned char buff[n]; //будер для считывания
    unsigned char crc; //чексумма
    unsigned char expectedCrc; //ожидаемая чексумма

    FILE *ReadFileTest = fopen(fileNameTest, "r"); //открываем файл
    if (ReadFileTest == NULL) { //проверяем успешность открытия
        exit(1);
    }

    FILE *ReadFileCsum = fopen(fileNameCsum, "r"); //открываем файл
    if (ReadFileCsum == NULL) { //проверяем успешность открытия
        exit(1);
    }

    while ((readSize = fread(&buff, 1, n, ReadFileTest)) != 0) { //читаем блоками пока не кончится файл
        crc = crc8(buff, readSize); //считаем чексумму
        if (fscanf(ReadFileCsum, "%c", &expectedCrc) == 0) { //считываем с файла ожидаемую чексумму и проверяем её существование
            printf("Error: The number of csum is less than necessary, %s.",fileNameTest);
            exit(1);
        }
        if (expectedCrc != crc) { //проверяем, что суммы совпадают
            printf("Error: Expected crc != crc, %s.",fileNameTest);
            exit(1);
        }
    }

    if (fscanf(ReadFileCsum, "%c", &expectedCrc) != EOF) { //проверяем, что в файле не осталось сумму
        printf("Error: The number of csum more than necessary, %s.",fileNameTest);
        exit(1);
    }

    fclose(ReadFileTest); //закрываем файл
    fclose(ReadFileCsum); // закрываем файл
}

int main() {
    check_csum("../tests/test1.txt", "../tests/CsumTest1.txt"); //Тест 1
    check_csum("../tests/test2.txt", "../tests/CsumTest2.txt"); //Тест 2
    check_csum("../tests/test3.txt", "../tests/CsumTest3.txt"); //Тест 3
    check_csum("../tests/test4.txt", "../tests/CsumTest4.txt"); //Тест 4
    return 0;
}
