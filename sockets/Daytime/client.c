#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define MAXLINE 100

int main(int argc, char const *argv[])
{
	int sockfd,n;

	char recvline[MAXLINE];

	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = ;

	
	

	return 0;
}
