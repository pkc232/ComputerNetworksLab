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
#include <pcap.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <bits/stdc++.h>

using namespace std;

void createX(char *buff){
	int pid=fork();
	if(pid==0){
		char *arr[]={"x",buff,NULL};
		execvp("./x",arr);
	}
}

void acceptConnectionFromT(int port_no){
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	// int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int value=1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
				perror("setsockopt failed");
	}
	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");
	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept from T");
	else printf("\n accept successful");

	char buf[100];
	read(nsfd,buf,100);
	cout<<"buffer from T "<<buf<<endl;
	createX(buf);
}

int main(int argc, char const *argv[])
{
	/* code */

	int port_no=atoi(argv[1]);
	acceptConnectionFromT(port_no);
	return 0;
}