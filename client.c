#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>

int main(){
	/* Socker File Descriptor */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	/* sin_family, sin_port, sin_addr */
	/* local host */
	struct sockaddr_in address = {
        AF_INET, 
        htons(2000), 
        0
    };

    connect(sockfd, (struct sockaddr *)&address, sizeof(address));

	char buffer[256];
	/* fd, events, revents*/
	struct pollfd pollfds[2] = {{0, POLLIN, 0}, {sockfd, POLLIN, 0}}; /* POLLIN = Listen to input events*/
	poll(pollfds, 2, 50000);

	for (;;) { /* loops forever */
		if (pollfds[0].revents & POLLIN) {
		read(0, buffer, 255);
		send(sockfd, buffer, 255, 0);
		} else if (pollfds[1].revents & POLLIN) {
			if (recv(sockfd, buffer, 255, 0) == 0) {
                return 0;
            }
			printf("%s\n", buffer);
		}
	}

	return 0;
}