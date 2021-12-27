#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa
#include <unistd.h> // for close(sock)

int main(int argc, char const *argv[])
{
/*
	int socket(int domain, int type, int protocol);
	
	- AF_INET : Address Family, as opposed to "PF_INET", Protocol Family
	
	- SOCK_STREAM : type of the socket, connection socket here
	as opposed to datagram socket i.e. TCP vs UDP (SOCK_DGRAM)

	- protocol "0" : (from manpages)
		
		The protocol specifies a particular protocol to be used with the socket. 
		Normally only a single protocol exists 
		to support a particular socket type within a given protocol family, 
		in which case protocol can be specified as 0.
*/

	// create a socket
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	printf("Created socket %d\n", sock);
	
	// address for the socket
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9999); // network byte order conversion for port
	// address could be INADDR_ANY, same as connecting to 0.0.0.0
	// server_address.sin_addr.s_addr = INADDR_ANY;

	inet_aton("192.168.0.183", &server_address.sin_addr);

	printf("Server IP:\t%s\n", inet_ntoa(server_address.sin_addr));

	int connection_status = connect(sock, // socket 
		(struct sockaddr *) &server_address, // argument is a pointer to a struct sockaddr, cast to it
		sizeof(server_address)); // size of the server_address struct

	if (connection_status != 0)
	{
	    printf("[ERROR] Call to connect() failed ! CODE = %d\n", connection_status);
	} else {
	    printf("[SUCCESS] Call to connect() was successful ! Awesome ! :)\n");
	}

	char server_response[256];
	recv(sock, 						// socket 
		&server_response,			// buffer address
		sizeof(server_response),	// buffer size
		0);	// flags

	printf("The server sent the data: %s\n", server_response);

	printf("Closing the socket :)\n");
	close(sock);

	printf("Exiting... bye :)\n");
	return 0;
}
