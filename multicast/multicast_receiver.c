#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define MULTICAST_ADDR "239.0.0.1"
#define MAX_MESSAGE_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char message[MAX_MESSAGE_SIZE];
    struct ip_mreq mreq;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Включаем опцию переиспользования адреса
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEADDR error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Заполняем структуру адреса рассылки
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Биндим сокет на адрес рассылки
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Заполняем и устанавливаем структуру группы Multicast рассылки
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) < 0) {
        perror("Setting IP_ADD_MEMBERSHIP error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Получаем сообщение
    if (recv(sockfd, message, MAX_MESSAGE_SIZE, 0) < 0) {
        perror("Error receiving multicast");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Received multicast message: '%s'\n", message);

    close(sockfd);
    return 0;
}
