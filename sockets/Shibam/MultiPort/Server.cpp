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

#define PORT1 8081
#define PORT2 8082
#define PORT3 8083
#define MAX_PENDING_REQUESTS 10
#define BUFFER_LEN 100
#define MAX_SERVICES 10




int main(int argc, char const *argv[])
{
	printf("Beginning server program \n");
	int sfd1,sfd2,sfd3,ret,nsfd1,nsfd2,nsfd3,sret,service;
	pid_t childPid1=0,childPid2=0,childPid3=0;


	struct sockaddr_in saddr1,saddr2,saddr3,newaddr;
	saddr1.sin_family = AF_INET;	saddr2.sin_family = AF_INET;	saddr3.sin_family = AF_INET;
    saddr1.sin_addr.s_addr = inet_addr("127.0.0.1"); 	saddr2.sin_addr.s_addr = inet_addr("127.0.0.1"); 	saddr3.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    saddr1.sin_port = htons( PORT1 );  saddr2.sin_port = htons( PORT2 );	saddr3.sin_port = htons( PORT3 ); //converts unsigned long int form host byte order to network byte order
	

	sfd1 = socket(AF_INET,SOCK_STREAM,0);	sfd2 = socket(AF_INET,SOCK_STREAM,0);	sfd3 = socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0 || sfd2<0 || sfd3<0)
	{
		printf("Error in creting socket \n"); exit(0);
	}
	printf("Server: Created 3 Sockets \n");

	// Forcefully attaching socket to the port 8080
    ret =  bind(sfd1, (struct sockaddr *)&saddr1, sizeof(saddr1));	ret =  bind(sfd2, (struct sockaddr *)&saddr2, sizeof(saddr2));	ret =  bind(sfd3, (struct sockaddr *)&saddr3, sizeof(saddr3));
    if (ret<0)
    {
        printf("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server: Binded\n");

    ret = listen(sfd1,MAX_PENDING_REQUESTS);	ret = listen(sfd2,MAX_PENDING_REQUESTS);	ret = listen(sfd3,MAX_PENDING_REQUESTS);
    if(ret<0){
    	printf("listen failed\n ");
    	exit(EXIT_FAILURE);
    }

    fd_set readfds;
	struct timeval timeout;

    
    while(1)
    {
    	FD_ZERO(&readfds);
    	FD_SET(sfd1,&readfds); FD_SET(sfd2,&readfds); FD_SET(sfd3,&readfds);
    	printf("Server: Listening \n");
    	timeout.tv_sec = 10; timeout.tv_usec = 0;
		printf("Selecting the readfds \n");
		sret = select(MAX_SERVICES,&readfds,NULL,NULL,&timeout);

		if(sret==0)
		{
			printf("sret = %d \n",sret );
			printf("Timeout \n");
		}
		else
		{
			printf("Number of bits set = %d \n",sret );
			if(FD_ISSET(sfd1,&readfds))
			{
				printf("Request came for service 1 \n");
				nsfd1 = accept(sfd1, (struct sockaddr *)&newaddr, (socklen_t*)&(newaddr));
				printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			if (nsfd1<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}
				service = 1;
				printf("Forking new process \n");
				childPid1 = fork(); 
				if(childPid1==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd1);
				}
				
			}
			if(FD_ISSET(sfd2,&readfds))
			{
				printf("Request came for service 2 \n");
				nsfd2 = accept(sfd2, (struct sockaddr *)&newaddr, (socklen_t*)&(newaddr));
				printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			if (nsfd2<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}
				service = 2;
				printf("Forking new process \n");
				childPid2 = fork(); 
				if(childPid2==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd2);
				}
				
			}
			if(FD_ISSET(sfd3,&readfds))
			{
				printf("Request came for service 1 \n");
				nsfd3 = accept(sfd3, (struct sockaddr *)&newaddr, (socklen_t*)&(newaddr));
				printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			if (nsfd3<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}
				service = 3;
				printf("Forking new process \n");
				childPid3 = fork(); 
				if(childPid3==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd3);
				}
				
			}


		}
	}
	if(childPid1==0 || childPid2==0 || childPid3==0)
	{
		char buffer[BUFFER_LEN];
		printf("Servicing in child process \n");
		int server_id = getpid(),nsfd;
		
		if(service ==1)
		{
			nsfd = nsfd1;
			int valread = recv( nsfd1 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 1 \n"); exit(EXIT_FAILURE);
    		}
    	}
    	else if(service == 2)
    	{
    		nsfd = nsfd2;
    		int valread = recv( nsfd2 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 2\n"); exit(EXIT_FAILURE);
    		}

    	}
    	else if(service ==3 )
    	{
    		nsfd = nsfd3;
    		int valread = recv( nsfd3 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 3\n"); exit(EXIT_FAILURE);
    		}
    	}

    	printf("Server %d giving service %d to client %s  \n",server_id,service,buffer );
    	stringstream ss; string sserv; ss<<service; ss>>sserv;
    	string msg = "Server gave service "+sserv+ " to client ";
    	send(nsfd , msg.c_str() ,BUFFER_LEN , 0 );
    	close(nsfd);
	}
    
    printf("Child Server exiting \n");
    
    
	return 0;
}