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
    char message[MAX_MESSAGE_SIZE] = "I am a Multicast";

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Заполняем адрес рассылки
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton(MULTICAST_ADDR, &addr.sin_addr);

    // Отправляем 
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error sending multicast");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Multicast message sent\n");

    close(sockfd);
    return 0;
}
