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

void connectToServer(int ti,int li){
	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=8080;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

	string s="";
	s+=to_string(ti);
	s+=" ";
	s+=to_string(li);
	write(sfd,s.c_str(),100);

	char buf[100];
	
	read(sfd,buf,100);

	printf("%s\n",buf);
}

int main(int argc, char const *argv[])
{
	if(argc<2){
		cout<<"Chutiye ti li daal\n";
	}
	connectToServer(atoi(argv[1]),atoi(argv[2]));
	return 0;
}