#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define BROADCAST_ADDR "255.255.255.255"
#define MAX_MESSAGE_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char message[MAX_MESSAGE_SIZE] = "I am a broadcast";

    // Создать UDP сокет
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем опцию, разрешающую broadcast
    int broadcastEnable=1;
    int ret=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if(ret<0){
        perror("Error setting broadcast socket option");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Заполняем структуру
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton(BROADCAST_ADDR, &addr.sin_addr);

    // Отправляем
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error sending broadcast");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Broadcast message sent\n");

    close(sockfd);
    return 0;
}
