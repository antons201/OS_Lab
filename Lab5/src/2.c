#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

unsigned long get_time_difference(int t1_sec, int t1_usec, int t2_sec, int t2_usec) {
    return t2_sec*1000000 + t2_usec - t1_sec*1000000 - t1_usec;
}


int main() {
    int buffer_size = 300*1024;
    int file1;
    FILE * file2;
    struct timeval tv1;
    struct timeval tv2;
    char* buf = "s";

    //создание, запись и удаление с помощью POSIX
    gettimeofday(&tv1, NULL);
    file1 = creat("file1.txt", S_IREAD|S_IWRITE);
    for (int i = 0; i < buffer_size; ++i) {
        write(file1, buf, 1);
    }
    close(file1);
    gettimeofday(&tv2, NULL);
    printf("Вермя на работу с файлом(POSIX): %ld милесекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    //создание, запись и удаление с помощью stdio
    gettimeofday(&tv1, NULL);
    file2 = fopen("file2.txt", "w");
    for (int i = 0; i < buffer_size; ++i) {
        fwrite(buf, 1, 1, file2);
    }
    fclose(file2);
    gettimeofday(&tv2, NULL);
    printf("Вермя на работу с файлом(библиотека): %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    return 0;
}

