#include <stdio.h>
#include <zconf.h>
#include <sys/time.h>

unsigned long get_time_difference(int t1_sec, int t1_usec, int t2_sec, int t2_usec) { //функция для рассчета времени
    return t2_sec*1000000 + t2_usec - t1_sec*1000000 - t1_usec;
}

void check_xor(char *fileName, int expectedRes) {
    unsigned char checkXor = 0; //начальное значение чек суммы
    char buff; //буфер для считывания

    struct timeval tv1; //для записи времени
    struct timeval tv2; //для записи времени

    FILE *file = fopen(fileName, "r"); //открываем файл
    if (file == NULL) { //проверяем успешность открытия
        exit(1);
    }

    gettimeofday(&tv1, NULL); //замеряем время перед началом

    while (fread(&buff, 1, 1, file) != 0) { //пока не считали весь файл читаем по байту и считаем чексумму
        checkXor ^= buff;
    }

    gettimeofday(&tv2, NULL); //замеряем время после окончания

    fclose(file); //закрываем файл

    printf("Result checksum %d, expected result %d\n", checkXor, expectedRes); //выводим полученную и ожидаемую чексумму
    printf("Time %ld мс\n", get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec)); // выводим время
}

int main() {
    check_xor("../tests/test1.txt", 113); //Тест 1
    check_xor("../tests/test2.txt", 47); //Тест 2
    check_xor("../tests/test3.txt", 77); //Тест 3
    check_xor("../tests/test4.txt", 117); //Тест 4
    return 0;
}
