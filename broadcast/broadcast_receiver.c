#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define MAX_MESSAGE_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char message[MAX_MESSAGE_SIZE];
    int addr_len;

    // Создать UDP сокет
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Адрес рассылки
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Биндимся на адрес рассылки
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Получаем сообщение
    addr_len = sizeof(addr);
    if (recvfrom(sockfd, message, MAX_MESSAGE_SIZE, 0, (struct sockaddr *)&addr, (socklen_t *)&addr_len) < 0) {
        perror("Error receiving broadcast");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Received broadcast message: '%s'\n", message);

    close(sockfd);
    return 0;
}
