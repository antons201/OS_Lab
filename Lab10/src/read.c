#include <stdio.h>
#include <zconf.h>

int main() {
    FILE *file = fopen("test.txt", "r"); //открываем файл
    char buff; // создаем буффер
    int i = 1; // заводим счетчик циклов

    if (file == NULL) { // проверяем открытие
        printf("Error");
        exit(1);
    }

    while (i) { //бесконечный цикл
        fseek(file, 0, SEEK_SET); //смещаем указатель на начало файла

        while (fread(&buff, 1, 1, file) != 0) { //читаем файл
            printf("%c", buff);//печатаем прочитанное
        }

        printf(" %d\n", i);//печатаем счетчик и переводим строку
        i++;//увеличиваем счетчик

        sleep(1);//усыпляем программу
    }

    fclose(file);

    return 0;
}
