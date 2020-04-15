#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char * dir_name;
    struct dirent *dt;
    struct stat st;
    int l_flag = 0;

    if (argc > 3 || (argc == 3  && strcmp(argv[1], "-l") != 0)) {
        printf("Error");
        exit(1);
    } // проверка на ошибки

    if (argc == 2 && strcmp(argv[1], "-l") != 0) {
        l_flag = 1;
        dir_name = argv[1];
    } else if (argc == 3) {
        dir_name = argv[2];
        l_flag = 1;
    } else if (argc == 1){
        dir_name = "./";
    } else {
        dir_name = "./";
        l_flag = 1;
    } // рассматриваем разные случаи

    DIR *dir = opendir(dir_name); //открываем дирректорию

    if (dir == NULL) {
        printf("Error");
        exit(1);
    } //проверка на ошибку

    while ((dt = readdir(dir)) != NULL) {
        printf("%s ", dt->d_name); // печатаем дирректорию
        stat(dt->d_name, &st); //получаем информацию о файле
        if (l_flag) { // если флаг, то печатаем доп.информацию
            printf("Размер файла %ld, число блоков %ld, размер блока %ld, число ссылок %ld\n ",
                   st.st_size, st.st_blocks, st.st_blksize, st.st_nlink);
        }
    }

    closedir(dir);
    return 0;
}