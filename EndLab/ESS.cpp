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

int totalNoOfClients=1;

int globalFD;
void *generateRandomClient(void *args){

	int r;
	int rsfd=socket(AF_INET,SOCK_RAW,50);
	struct sockaddr_in client;
  	client.sin_family=AF_INET;
  	client.sin_addr.s_addr=inet_addr("127.0.0.1");
  	if(connect(rsfd , (struct sockaddr *)&client , sizeof(client) )==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

	string s="";
  	while(1)
  	{
  	r=(rand()%totalNoOfClients);
  	r++;
  	s="";
  	s+=to_string(r);
  	cout<<"sending random number"<<s.c_str()<<endl;
	write(rsfd,s.c_str(),1024);
  	sleep(5);
  	}

}
void *serviceClient(void *args){
	char buff[100];

	while(1){
	read(globalFD,buff,100);
	if(buff[0]>='0'&&buff[0]<='9'){
		totalNoOfClients++;
	}
	printf("%s from client\n",buff);
		
	}
}

void acceptFromFirstClient(){
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=8080;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
				perror("setsockopt failed");
	}

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else printf("\n accept successful");

	globalFD=nsfd;

}

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	acceptFromFirstClient();
	pthread_t serviceClient_t,generateRandomClient_t;


	pthread_create(&serviceClient_t,NULL,serviceClient,NULL);
	pthread_create(&generateRandomClient_t,NULL,generateRandomClient,NULL);


	pthread_join(serviceClient_t,NULL);
	pthread_join(generateRandomClient_t,NULL);
	return 0;
}