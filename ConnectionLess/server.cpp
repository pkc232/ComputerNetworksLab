
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>


using namespace std;
#define port_no 8080


void acceptData(){
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;

	if((sfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");
	
	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	cli_len = sizeof(cli_addr);
	char buffer[100];
	recvfrom(sfd , buffer , 100 , 0 , ( struct sockaddr * ) &cli_addr , & cli_len );
	// fgets( buffer , 256 , stdin );
	// sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &cli_addr ,  cli_len);
	printf("%s\n",buffer);
}


int main(int argc, char const *argv[])
{
	acceptData();

	return 0;
}