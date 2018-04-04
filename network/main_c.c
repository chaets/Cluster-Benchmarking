#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>


#define BUFF_SIZE 64000
#define ERROR -1

int main(int argc, char const *argv[])
{
	
	int sockfd, rc;
	char buffer[BUFF_SIZE];
	struct addrinfo hints, *res;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	rc = getaddrinfo("localhost", "11155", &hints, &res);
	printf("RC %d\n", rc);
		if (rc != 0) 
		{
			printf("Could not get address information!\n");
			return ERROR;
		}
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0) 
		{
			printf("Could not create socket!\n");
			return ERROR;
		}

	rc = connect(sockfd, res->ai_addr, res->ai_addrlen);

		if (rc < 0) 
		{
			printf("Could not connect to server!\n");
			return ERROR;
		}
	strcpy(buffer, "Can you hear me?");
	rc = send(sockfd, &buffer[0], BUFF_SIZE, 0);
		if (rc < 0) 
		{
			printf("Could not send package!\n");
		}
	memset(buffer, 0, BUFF_SIZE);

	rc = recv(sockfd, &buffer[0], BUFF_SIZE, 0);

		if (rc == 0) 
		{
			printf("Connection closed at receive!\n");
			 return 0;
		}
		if (rc < 0) 
		{
			printf("Could not receive package!\n");
			 return 0;
		}
	printf("%s", buffer);
	freeaddrinfo(res);
	close(sockfd);
	/* code */
		return 0;
}