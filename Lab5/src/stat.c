#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* file_name = "file1.txt";
    struct stat st;

    stat(file_name, &st);
    printf("Размер файла %ld\n число блоков %ld\n размер блока %ld\n число ссылок %ld\n ",
           st.st_size, st.st_blocks, st.st_blksize, st.st_nlink);
    return 0;
}
