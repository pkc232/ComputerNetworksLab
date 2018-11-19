#include <bits/stdc++.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include<unistd.h>
#include<pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>		/* For inet_ntoa() and ntohs()*/

using namespace std;

#define PORT 8080
#define MAX_PENDING_REQUESTS 10
#define BUFFER_LEN 100



struct clientInfo {
    int nsfd;
    int service_no;
};


void* serviceHandler(void* param){
    printf("Inside thread \n");
    char buffer[BUFFER_LEN];
    struct clientInfo cinfo = *(struct clientInfo*)param;
    int valread = recv(cinfo.nsfd , buffer, BUFFER_LEN,0);
    if(valread<0)
    {
        printf("Error in reading \n"); exit(EXIT_FAILURE);
    }
    int service = atoi(buffer); string sserv(buffer);
    cinfo.service_no = service;
    printf("Service %d given \n",service);
    string msg = "Service " +sserv+ " given ";
    printf("Sending message to client \n");
    send(cinfo.nsfd , msg.c_str() ,BUFFER_LEN , 0 );
    printf("Thread exiting \n");
    pthread_exit(0);
}



int main(int argc, char const *argv[])
{
	printf("Beginning server program \n");
	int sfd,ret,nsfd;
	pid_t childPid;


	struct sockaddr_in saddr,newaddr;
	saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons( PORT );   //converts unsigned long int form host byte order to network byte order
	

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

    while(1)
    {
    	printf("Server: Listening \n");
    nsfd = accept(sfd, (struct sockaddr *)&newaddr, (socklen_t*)&(newaddr));
    printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    if (nsfd<0)
    {
       	printf("Error in accepting \n");
        exit(EXIT_FAILURE);
    }
    
    printf("Forking new thread \n");
    struct clientInfo cinfo; cinfo.nsfd = nsfd;
    pthread_t thread;
    pthread_create(&thread,NULL,serviceHandler,(struct clientInfo*)(&cinfo));



    
    }
    return 0;
}