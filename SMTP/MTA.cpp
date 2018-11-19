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

int arrnsfd[1000];
pthread_t threads[1000];

void makeConnection(int port_no,string msg){
	int sfd;
	struct sockaddr_in serv_addr;

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

	send(sfd,msg.c_str(),100,0);

}

void* transferMsgtoMTA(void* args){
	int fd = (*((int*)(args)));
	char buf[100];

	recv(fd,buf,100,0);

	string msg(buf);
	stringstream ss;
	ss<<msg;

	int prtMTA;
	ss>>prtMTA;

	string data;
	ss>>data;

	makeConnection(prtMTA,data);

}

void* transferMsgtoMUA(void* args){
	int fd = (*((int*)(args)));
	char buf[100];

	recv(fd,buf,100,0);

	string msg(buf);
	stringstream ss;
	ss<<msg;

	int prtMUA;
	ss>>prtMUA;

	string data;
	ss>>data;

	makeConnection(prtMUA,data);

}


void *listeningSocket(void* args){
	
	int port_no = (*((int*)(args)));
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
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

	int nsfd;
	int cur=0;

	while(1){
		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		perror("\n accept ");
		else printf("\n accept successful");
		arrnsfd[cur]=nsfd;
		if(port_no>9000){
				if(pthread_create(&(threads[cur]),NULL,transferMsgtoMTA,(void*)(arrnsfd+cur))!=0)
				perror("\npthread_create ");
		}
		else
		{
			if(pthread_create(&(threads[cur]),NULL,transferMsgtoMUA,(void*)(arrnsfd+cur))!=0)
				perror("\npthread_create ");
		}
		cur++;
	}
}


int main(int argc, char const *argv[])
{
	int portForOtherMTA,portForMua;
	portForOtherMTA = atoi(argv[1]);
	portForMua = atoi(argv[2]);
	pthread_t t1,t2;

	pthread_create(&t1,NULL,listeningSocket,(void*)(&portForOtherMTA));
	pthread_create(&t2,NULL,listeningSocket,(void*)(&portForMua));

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}