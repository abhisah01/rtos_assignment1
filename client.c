#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in server;
    int socket_desc, port_no;
    char sendBuffer[4096]; // sending messages of atmost 4 KB each

    socket_desc = socket(AF_INET, SOCK_STREAM, 0); // creating the socket at client side
    if(socket_desc == -1) {
        perror("Error");
        exit(0);
    }

    memset(&server, 0, sizeof(server)); // clearing the server structure before initialization
    port_no = atoi(argv[2]);

    server.sin_family = AF_INET; // setting domain (IPv4)
    server.sin_port = htons(port_no); // setting port number from command line arguments

    if(inet_pton(AF_INET, argv[1], &server.sin_addr) <= 0) {
        printf("Invalid IP");
        exit(0);
    }

    if(connect(socket_desc, (struct sockaddr*) &server, sizeof(server)) != 0) { // connecting the client to the server
        perror("Error");
        exit(0);
    }

	if(fork() >= 0) {
		while(1) { // continuously sending inputs to the server
			memset(&sendBuffer, 0, sizeof(sendBuffer)); // clearing the buffer before input

			fgets(sendBuffer, 4096, stdin); // reading the message from the screen,i.e.,  STDIN
			send(socket_desc, sendBuffer, strlen(sendBuffer) + 1, 0); // sending the message to the server
		}
	} else { // error in fork
		printf("Error in fork...\n");
	}

	return 0;
}