#include <bits/stdc++.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <cstdlib>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>		/* For inet_ntoa() and ntohs()*/



using namespace std;

#define PORT 8080
#define MAX_PENDING_REQUESTS 10
#define BUFFER_LEN 100


char buffer[BUFFER_LEN];


int main(int argc, char const *argv[])
{
	printf("Beginning server program \n");

	int sfd,ret,nsfd;


	pid_t childpid;

	struct sockaddr_in saddr,newaddr;

	saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("192.168.0.104");
    saddr.sin_port = htons( PORT );

    sfd = socket(AF_INET,SOCK_STREAM,0);

    	if(sfd<0)
	{
		printf("Error in creting socket \n"); exit(0);
	}
	printf("Server: Created Socket \n");

    ret =  bind(sfd, (struct sockaddr *)&saddr, 
                                 sizeof(saddr));

    if (ret<0)
    {
        printf("bind failed \n");
        exit(EXIT_FAILURE);
    }


    printf("Server: Binded\n");


    ret = listen(sfd,MAX_PENDING_REQUESTS);
    if(ret<0){
    	printf("listen failed\n ");
    	exit(EXIT_FAILURE);
    }

    while(1){

    printf("Server: Listening \n");
    nsfd = accept(sfd, (struct sockaddr *)&newaddr, (socklen_t*)&(newaddr));
    printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );

    if (nsfd<0)
    {
       	printf("Error in accepting \n");
        exit(EXIT_FAILURE);
    }

    printf("Forking new process \n");
    childPid = fork();

    if(childPid==0){
    	printf("Inside child process. \n");
    	close(sfd);
    	break;
    }
    else
    {
    	printf("Inisde parent process\n");
    }

        int valread = recv( nsfd , buffer, BUFFER_LEN,0);
    if(valread<0)
    {
    	printf("Error in reading \n"); exit(EXIT_FAILURE);
    }
    int service = atoi(buffer); int server_id = getpid();  string sserv(buffer);
    printf("Server %d giving service %d  to client %d \n",server_id,service,nsfd );
    string msg = "Service " +sserv+ " given ";
    send(nsfd , msg.c_str() ,BUFFER_LEN , 0 );


	}
	return 0;
}