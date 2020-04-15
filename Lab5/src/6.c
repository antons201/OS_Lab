#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <zconf.h>

void printOffset(int offset) {
    for (int i = 0; i < offset; ++i) {
        printf(" ");
    }
}

void dirTree(char * dir_name, int offset) {
    struct dirent *dt;
    struct stat st;
    DIR *dir = opendir(dir_name); // открыли директорию

    if (dir == NULL) {
        printf("Error");
        exit(1);
    } // проверка на ошибку

    while ((dt = readdir(dir)) != NULL) { // бежим по всем дирректориям
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0) {
            printOffset(offset); //выводим смещение
            printf("%s\n", dt->d_name); // выводим название файла или дирректории
            stat(dt->d_name, &st); //получаем данные о файле или дирректории
            if (dt->d_type == DT_DIR) { //если дирректория, то заходим в неё
                char path[2048];
                snprintf(path, sizeof path, "%s/%s", dir_name, dt->d_name); //склеиваем путь
                dirTree(path, offset + 2); //рекурсивно заходим в дирреткорию
            }
        }
    }
    
    closedir(dir); // закрываем дирректорию
}

void dirTreeSearch(char * dir_name, char * search_dir_name, int depth) {
    char path[2048];
    struct dirent *dt;
    struct stat st;
    DIR *dir = opendir(dir_name); // открыли директорию
    depth--; //уменьшили глубину

    if (dir == NULL) {
        printf("Error");
        exit(1);
    } // проверка на ошибку

    while ((dt = readdir(dir)) != NULL) { //бежим по дирректориям
        snprintf(path, sizeof path, "%s/%s", dir_name, dt->d_name); //склеиваем путь
        if (strcmp(dt->d_name, search_dir_name) == 0 && dt->d_type == DT_DIR) {
            dirTree(path, 0);
        } //если нашли нужную дирректорию, то вызываем печать дерева
        if (dt->d_type == DT_DIR && strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0 && depth > 0) {
            dirTreeSearch(path, search_dir_name, depth);
        } //продолжаем поиск в каждой дирректории
    }




}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        dirTree(".", 0);
    } // первый вариант
    if (argc == 2) {
        dirTreeSearch(".", argv[1], INT_MAX);
    } // второй вариант
    if (argc == 4 && strcmp(argv[1], "-d") == 0 && atoi(argv[3]) > 0) {
        dirTreeSearch(".", argv[2], atoi(argv[3]));
    } // третий вариант
    return 0;
}