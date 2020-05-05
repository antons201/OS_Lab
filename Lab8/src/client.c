
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <zconf.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // зачищаем буффер
    memset(&buff, 0, sizeof(buff));
    printf("Enter the filename : "); //просим ввести строку
    int n = 0;
    while ((buff[n++] = getchar()) != '\n') //читаем строку
        ;
    buff[n-1] = 0;

    if (send(sockfd, buff, sizeof(buff), 0) < 0) {
        perror("send");
        exit(4);
    }; // отправляем на сервер имя файла
    memset(&buff, 0, sizeof(buff));
    if (recv(sockfd, buff, MAX, 0) < 0) {
        perror("recv");
        exit(5);
    }; //получаем с сервера имя файла

    printf("%s", buff); //печатаем содержимое файла

    // close the socket
    close(sockfd);
}
