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


using namespace std;


void createRawSocket(){
	int rsfd=socket(AF_INET,SOCK_RAW,50);
	struct sockaddr_in client;
  	client.sin_family=AF_INET;
  	client.sin_addr.s_addr=inet_addr("127.0.0.1");
  	char buff[]="hello";
  	while(1)
  	{
	sendto(rsfd,buff,1024,0,(struct sockaddr*)&client,sizeof(client));
  	sleep(2);
  	}
}


int main(int argc, char const *argv[])
{
	createRawSocket();
	return 0;
}