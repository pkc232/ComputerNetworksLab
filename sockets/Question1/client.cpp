#include <bits/stdc++.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <arpa/inet.h> 		//for htonl(PORT) host to network
#include <unistd.h>
#include <pthread.h>


using namespace std;

#define PORT 8080
#define buff_len 100


int main(int argc, char const *argv[])
{
	printf("In Client prog\n");

	struct sockaddr_in caddr;
	int cfd =0 ,valread,ret=0;

	struct socaddr_in saddr;

	char msg[100];
	char buffer[1024]={0};

	cfd = socket(AF_INET,SOCK_STREAM,0);

	printf("A Socket created for client with cfd: %d\n",cfd);



	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);

	ret = connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr));

	printf("Return value after connect %d\n",ret);

	printf("ENter service number \n");
	scanf("%s",msg);

	send(cfd,msg,buff_len,0);

	valread = read(cfd,buffer,1024);

	printf("%s\n",buffer);


	return 0;
}
