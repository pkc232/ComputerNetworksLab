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

#define PORT 8080
#define MAX_PENDING_REQUESTS 10


using namespace std;


int main(int argc, char const *argv[])
{
	int sockfd,n;

	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	servaddr.sin_addr.s_addr = inet_addr("172.30.102.117");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	int cret = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	if(cret<0){
		perror("COnnection not established\n");
		return 0;
	}
	cout<<"Connection established by "<<cret<<endl;
	char arr[100];
	cin>>arr;
	write(sockfd,arr,100);
	read(sockfd,arr,100);
	cout<<arr<<endl;
	return 0;
}