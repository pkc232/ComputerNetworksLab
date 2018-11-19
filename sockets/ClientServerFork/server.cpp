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


using namespace std;

int main(int argc, char const *argv[])
{
	int listenfd,connfd;socklen_t lencli;

	struct sockaddr_in servaddr,cliaddr;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	if(listenfd<0)
	{
		cout<<"Socket not created\n";
		return 0;
	}

	printf("Server created socket %d\n",listenfd);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	int bndret = bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	if(bndret<0)
	{
		cout<<"Bind failed\n";
		return 0;
	}

	printf("Binding done %d\n",bndret);

	int listret = listen(listenfd,MAX_PENDING_REQUESTS);

	if(listret<0)
	{
		printf("Listen failed\n");
	}

	printf("SOcket ready to listen %d\n",listret);

	while(1){
		lencli = sizeof(cliaddr);

		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&lencli);


		printf("Connection from %s,port %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		
		int pid = fork();
		if(pid==0){
		close(listenfd);
		printf("Child with pid %d\n",getpid());
		char buf[100];
		read(connfd,buf,100);
		printf("%s\n",buf);
		close(connfd);
		exit(0);
		}
		close(connfd);
				
	}




	return 0;
}