#include <bits/stdc++.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>

using namespace std;


#define PORT1 8081
#define PORT2 8082
#define PORT3 8083
#define BUFFER_LEN 100


int main(int argc, char const *argv[])
{
	printf("Client program started \n");
    
    int cfd = 0, valread,ret=0,service;
    struct sockaddr_in saddr;
    char name[BUFFER_LEN],buffer[BUFFER_LEN];


    printf("Enter your name \n"); scanf("%s",name);
    while(1)
    {
        printf("Enter the service required-1 , 2  or 3.\n");
        scanf("%d",&service);
        cfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("CFD = %d \n",cfd );
        saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        saddr.sin_family = AF_INET;
        if (cfd < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }
        printf("Socket created \n");
        if(service==1)
        {
            saddr.sin_port = htons(PORT1);
        }
        else if(service==2)
        {
            saddr.sin_port = htons(PORT2);
        }
        else if(service==3)
        {
             saddr.sin_port = htons(PORT3);

        }
        ret = connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr));
        printf("Return value after connect() = %d \n",ret  );
        if ( ret < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        send(cfd , name , BUFFER_LEN , 0 );
        printf("Service %d request sent \n",service);
        valread = recv( cfd , buffer, BUFFER_LEN,0);
        printf("Server sent: %s\n",buffer );
        close(cfd);

    }
  	
    
    
    
    printf("Exiting client \n");
    return 0;
}