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
		0};

	bind(sockfd, (struct sockaddr *)&address, sizeof(address));

	/* How many terminals the socket can listen */
	listen(sockfd, 10);
	int clientfd = accept(sockfd, 0, 0);
	/* fd, events, revents*/
	struct pollfd pollfds[2] = {{0, POLLIN, 0}, {clientfd, POLLIN, 0}}; /* POLLIN = Listen to input events*/
	char buffer[256];
	poll(pollfds, 2, 100000);

	for (;;) { /* loops forever */
		if (pollfds[0].revents & POLLIN) {
		read(0, buffer, 255);
		send(clientfd, buffer, 255, 0);
		} else if (pollfds[1].revents & POLLIN) {
			if (recv(clientfd, buffer, 255, 0) == 0) {
				return 0;
			}
			printf("%s\n", buffer);
		}
	}

	return 0;
}