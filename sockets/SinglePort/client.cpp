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


using namespace std;


#define port 8080
#define BUFFER_LEN 100


int main(int argc, char const *argv[])
{
	printf("Client program started\n");

	struct sockaddr_in caddr,saddr;
	int cfd = 0,valread,ret=0;

	char msg[100];
	char buffer[1024]={0};

	cfd = socket(AF_INET,SOCK_STREAM,0);

	printf("CFD=%d\n",cfd);

	if(cfd<0)
	{
		printf("SOcket creation error \n");
		return -1;
	}

	printf("Socket Created\n");


	saddr.sin_addr.sin_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);


	ret = connect(cfd,(struct socaddr *)&saddr,sizeof(saddr));
	printf(" Return value after connect() = %d\n",ret);

	if(ret<0)
	{
		printf("COnnection failed \n");
		return -1;
	}

	printf("Enter service number \n");
	scanf("%s",msg);
	send(cfd,msg,BUFFER_LEN,0);

	printf("Service nuumber sent\n");

	valread = recv(cfd,buffer,BUFFER_LEN)

	printf("Server sent :%s\n",buffer);
	printf("Exiting client\n");
	
	return 0;
} 