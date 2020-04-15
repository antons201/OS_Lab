#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Ошибка");
        exit(1);
    }
    int n = atoi(argv[1]);
    int count = 1;
    struct stat st;
    char* file_name = argv[2];
    int file = open(file_name, S_IREAD|S_IWRITE);
    stat(file_name, &st); // получаем данные о файле
    int size = st.st_size;
    char text[size];
    read(file, text, size); // читаем файл
    for (int i = 0; i < size; ++i) {
        if (text[i] == '\n') {
            count++;
        }
    } // счиатем количество строк
    if (count <= n) {
        printf("%s", text); // если строк в файле меньше, чем требуется, выводим всё
    } else { // иначе бежим по файлу и отсчитываем нужное количество строк
        for (int i = 0; i < size; ++i) {
            if (text[i] == '\n') // нашли строку
                count--;
            if (count == n) { // нашли необходимое количество строк
                for (int j = i + 1; j < size; ++j)
                    printf("%c", text[j]);
                break;
            }
        }
    }
    printf("\n");
    close(file);
    return 0;
}
