#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in server, client;
	int socket_desc, client_desc, port_no;
	socklen_t size_client;
	char recvBuffer[4096]; // receiving messages of atmost 4 KB each

	socket_desc = socket(AF_INET, SOCK_STREAM, 0); // creating socket at server Side
	if(socket_desc == -1) {
		perror("Error");
		exit(0);
	}

	memset((void*) &server, 0, sizeof(server)); // clearing the server structure before initialization
	port_no = atoi(argv[1]);

	// socket address structure initialization
	server.sin_family = AF_INET; // setting domain (IPv4)
	server.sin_addr.s_addr = INADDR_ANY; // permits any incoming IP (we can customize this)
	server.sin_port = htons(port_no); // setting port number form command line arguments

	if(bind(socket_desc,(struct sockaddr*) &server, sizeof(server)) != 0) { // bind the socket address structure to the socket
		perror("Error");
		exit(0);
	}

	if(listen(socket_desc, 1) != 0) { // server can serve only 1 client (we can custimize this)
		perror("Error");
		exit(0);
	}

	memset((void*) &client, 0, sizeof(client)); // clearing the client structure before initialization

    if((client_desc = accept(socket_desc, (struct sockaddr*) &client, &size_client)) < 0) { // accepting the client request
        perror("Error");
        exit(0);
    }

    printf("\nserver connected...\n");

	if(fork() >= 0) {
		while(1) { // continuously receive inputs from the client
			memset(&recvBuffer, 0, sizeof(recvBuffer)); // clearing the buffer before input

			recv(client_desc, recvBuffer, sizeof(recvBuffer), 0); // receiving the message from the client
			printf("CLIENT : %s", recvBuffer); // printing the message
		}
	} else { // error in fork
		printf("Error in fork...\n");
	}

	return 0;
}