#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 64
#define ERROR -1

void server();
void client();

int server()
{
	int sockfd, newfd, rc;
char buffer[BUFF_SIZE];
struct addrinfo hints, *res;

socklen_t addrlen;

struct sockaddr_storage clt;


hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;

rc = getaddrinfo(NULL, "11155", &hints, &res);
if (rc != 0) {
	printf("Could not get address information!\n");
	return ERROR;
}

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
if (sockfd < 0) {
	printf("Could not create socket!\n");
	return ERROR;
}

if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
	printf("Could not bind socked!");
	close(sockfd);
	return ERROR;
}

if (listen(sockfd, 10) == -1) {
	printf("Could not listen to socket!");
	close(sockfd);
	return ERROR;
}

newfd = accept(sockfd, (struct sockaddr *) &clt, &addrlen);
if (newfd < 0) {
	printf("Could not accept client!\n");
	close(sockfd);
	return ERROR;
}

memset(buffer, 0, BUFF_SIZE);
rc = recv(newfd, &buffer[0], BUFF_SIZE, 0);
if (rc == 0) {
	printf("Connection closed at receive!\n");
	break;
}

if (rc < 0) {
	printf("Could not receive package!\n");
	break;
}

printf("%s", buffer);
strcpy(buffer, "Absolutely!");
rc = send(newfd, &buffer[0], BUFF_SIZE, 0);

if (rc < 0) {
	printf("Could not send package!\n");
}

freeaddrinfo(res);
close(newfd);
close(sockfd);

}

	void client()
	{

		int sockfd, rc;
		char buffer[BUFF_SIZE];
		struct addrinfo hints, *res;
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		rc = getaddrinfo("<server-ip>", "11155", &hints, &res);
		if (rc != 0) 
		{
			printf("Could not get address information!\n");
			return ERROR;
		}
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0) {
			printf("Could not create socket!\n");
			return ERROR;
		}
		rc = connect(sockfd, res->ai_addr, res->ai_addrlen);
		if (rc < 0) {
			printf("Could not connect to server!\n");
			return ERROR;
		}
		Strcpy(buffer, "Can you hear me?");
		rc = send(sockfd, &buffer[0], BUFF_SIZE, 0);
		if (rc < 0) {
			printf("Could not send package!\n");
		}
		Sockets TCP example (client)
		memset(buffer, 0, BUFF_SIZE);
		rc = recv(sockfd, &buffer[0], BUFF_SIZE, 0);
		if (rc == 0) {
			printf("Connection closed at receive!\n");
			break;
		}
		if (rc < 0) {
			printf("Could not receive package!\n");
			break;
		}
		printf("%s", buffer);
		freeaddrinfo(res);
		close(sockfd);

	}
int main(int argc, char const *argv[])
{
	server();
	client();
	return 0;
}