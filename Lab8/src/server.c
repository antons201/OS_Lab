
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <zconf.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

char* readFile(char* filename) {
    int fd;
    char* buffer;
    struct stat st;
    fd = open(filename, O_RDONLY); //открываем файл

    stat(filename, &st);
    buffer = (char*)malloc(st.st_size*sizeof(char)); //выделяем память под содержимое файла
    if (fd < 0) { //проверка на ошибку
        fprintf (stderr, "Cannot open file\n");
        exit (1);
    }
    read (fd, buffer, st.st_size); //читаем файл

    return buffer; //возвращаем содержимое файла
}

void print(int signum) {
    printf("SIGSEGV(check signal)\n");
    exit(0);
}


int main() {
    signal(SIGSEGV, print); //ловим сигнал
    int sockfd, len;
    int bytes_read;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    char buff[MAX];
    int n;
    fd_set readset, allset;
    FD_ZERO(&allset); //очищает множество allset
    FD_SET(sockfd, &allset); //добавляет дескриптор sockfd в множество allset
    struct timeval timeout; // устанавливаем время ожидания
    timeout.tv_sec = 150;
    timeout.tv_usec = 0;
    // бесконечный цикл
    for (;;) {
        readset = allset;

        if (select(FD_SETSIZE, &readset, NULL, NULL, &timeout) <= 0) { //используем select для отслеживания нескольких соккетов
            perror("select");
            exit(3);
        }

        for (int i = 0; i < FD_SETSIZE; ++i) { //бежим по всем соккетам
            if (FD_ISSET(i, &readset)) { // Определяем тип события и выполняем соответствующие действия
                if (i == sockfd) { // Поступил новый запрос на соединение, используем accept
                    // Accept the data packet from client and verification
                    int sock = accept(sockfd, (SA *) &cli, &len);
                    if (sock < 0) {
                        printf("server acccept failed...\n");
                        exit(0);
                    } else
                        printf("server acccept the client...\n");

                    fcntl(sock, F_SETFL, O_NONBLOCK); //делаем соккет неблокирующимся

                    FD_SET(sock, &allset);
                } else {
                    // Поступили данные от клиента, читаем их
                    bytes_read = recv(i, buff, 1024, 0);

                    if (bytes_read <= 0) {
                        // Соединение разорвано, удаляем сокет из множества
                        close(i);
                        FD_CLR(i, &allset);
                        continue;
                    }

                    char* readBuff = readFile(buff); // вызываем функцию чтения данных из файла

                    // Отправляем данные обратно клиенту
                    if (send(i, readBuff, strlen(readBuff)*sizeof(char), 0) < 0) {
                        perror("send");
                        exit(4);
                    };
                    free(readBuff); //освобождаем память
                }
            }
        }
    }
}
