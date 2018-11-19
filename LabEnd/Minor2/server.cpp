#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

void connectToClient(){
	int rsfd=socket(AF_INET,SOCK_RAW,50);
	struct sockaddr_in client;
  	client.sin_family=AF_INET;
  	client.sin_addr.s_addr=inet_addr("127.0.0.1");
  	if(connect(rsfd , (struct sockaddr *)&client , sizeof(client) )==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

  	char buff[]="hello";
  	while(1)
  	{
	write(rsfd,buff,1024);
  	sleep(2);
  	}

  	int pid=fork();

  	if(pid==0){
  		printf("performing dup2\n");
  		dup2(rsfd,1);

  		execvp("./s2",NULL);
  	}
  	else
  	{
  		while(1);
  	}
}

int main(int argc, char const *argv[])
{
	
	connectToClient();

	return 0;
}