#include <bits/stdc++.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080
#define MAX_PENDING_REQUESTS 10



int main(int argc, char const *argv[])
{
	printf("IN p1\n");
	int sfd;
	dup2(sfd,0);
	struct sockaddr_in infoSfd;
	socklen_t slen,clilen;
	slen = sizeof(infoSfd);
	getsockname(sfd,(struct sockaddr*)&infoSfd,&slen);

	printf("Connection from %s,port %d\n",inet_ntoa(infoSfd.sin_addr),ntohs(infoSfd.sin_port));
	return 0;
}