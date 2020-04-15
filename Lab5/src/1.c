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
    int file;
    char buffer[buffer_size];
    struct timeval tv1;
    struct timeval tv2;

    //создаем файл
    gettimeofday(&tv1, NULL);
    file = creat("file.txt", S_IREAD|S_IWRITE);
    if (file == -1) {
        printf("Error");
        exit(1);
    }
    gettimeofday(&tv2, NULL);
    printf("Вермя на creat: %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    //записываем в файл
    gettimeofday(&tv1, NULL);
    write(file, buffer, buffer_size);
    gettimeofday(&tv2, NULL);
    printf("Вермя на write: %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    //очищаем файл
    gettimeofday(&tv1, NULL);
    ftruncate(file, 0);
    gettimeofday(&tv2, NULL);
    printf("Вермя на ftruncate: %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    //закрываем файл
    gettimeofday(&tv1, NULL);
    close(file);
    gettimeofday(&tv2, NULL);
    printf("Вермя на fclose: %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));

    //удаляем файл
    gettimeofday(&tv1, NULL);
    remove("file.txt");
    gettimeofday(&tv2, NULL);
    printf("Вермя на remove: %ld микросекунд\n",
           get_time_difference(tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec));
    return 0;
}
