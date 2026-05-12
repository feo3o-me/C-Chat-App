#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

/* Compile with -lws2_32 */

int main(void){
    /*sin_family, socket type, protocol (0 for any)*/
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /*sin_family, port, addr */
    struct sockaddr_in address = {
        AF_INET,
        htons(2000),
        0
    };

    /* debug only
    if (sockfd) {
        printf("Socket created\n"); 
    }
    */

    /* assigns an IP addr to a socket */
    /* use only on server side */
    bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    
    /* assigns the socket as a listener to accepet connection requests */
    listen(sockfd, 2);
    int clientfd = accept(sockfd, 0, 0);

    WSAPOLLFD pollfd[2] = {{0, POLLIN, 0}, (clientfd, POLLIN, 0)};
    char buffer[256];

    WSAPoll(pollfd, 2, 10000);

    for (;;) {
        if (pollfd[0].revents & POLLIN) {
            read(0, buffer, 255);
            send(clientfd, buffer, 255, 0);
        } else if (pollfd[0].revents & POLLIN) {
            if (recv(clientfd, buffer, 255, 0)){
                return 0;
            }
        }
    }
}