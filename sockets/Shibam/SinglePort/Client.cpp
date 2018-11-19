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


#define PORT 8080
#define BUFFER_LEN 100


int main(int argc, char const *argv[])
{
	printf("Client program started \n");
    struct sockaddr_in caddr;
    int cfd = 0, valread,ret=0;
    struct sockaddr_in saddr;
    char msg[10];
    char buffer[1024] = {0};
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("CFD = %d \n",cfd );
    if (cfd < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  	printf("Socket created \n");
    //memset(&saddr, '0', sizeof(saddr));
  

  	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
      
    // //Convert IPv4 and IPv6 addresses from text to binary form
    // if(inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr)<=0) 
    // {
    //     printf("\nInvalid address/ Address not supported \n");
    //     return -1;
    // }
  	ret = connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr));
  	printf("Return value after connect() = %d \n",ret  );
    if ( ret < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Enter service number \n");
    scanf("%s",msg);
    send(cfd , msg , BUFFER_LEN , 0 );
    printf("Service number sent \n");
    valread = recv( cfd , buffer, BUFFER_LEN,0);
    printf("Server sent: %s\n",buffer );
    printf("Exiting client \n");
    return 0;
}