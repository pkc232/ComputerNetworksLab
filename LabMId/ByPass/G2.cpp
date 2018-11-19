#include <bits/stdc++.h>
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

#define port_no 8082

int sfd;
struct sockaddr_in serv_addr,cli_addr;
int nsfd;
int portToConnect;


void acceptConnection(){
	socklen_t cli_len;
	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");
	listen(sfd,10);
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else printf("\n accept successful");
}

void connectToGroup1(){
	char buf[100];
	read(nsfd,buf,100);
	portToConnect = atoi(buf);
	cout<<"Port received in G2 is "<<portToConnect<<endl;
	int sfd;
	struct sockaddr_in serv_addr;
	bzero(&serv_addr,sizeof(serv_addr));
	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portToConnect);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	char msg[100]="hello"; 
	write(sfd,msg,100);
}

int main(int argc, char const *argv[])
{
	acceptConnection();
	connectToGroup1();
	return 0;
}