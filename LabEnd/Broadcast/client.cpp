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

void print_ip(struct iphdr *ip)
{
  cout<<"ip header len: "<<(unsigned int)(ip->ihl)<<endl;
  cout<<"ip header version: "<<(unsigned int)(ip->version)<<endl;
  cout<<"ip header ttl:  "<<(unsigned int)(ip->ttl)<<endl;
  cout<<"type of service:  "<<(unsigned int)(ip->tos)<<endl;
  cout<<"packet id:  "<<ntohs(ip->id)<<endl;
  cout<<"ip packet len: "<<ntohs(ip->tot_len)<<endl;
  cout<<"protocol : "<<(unsigned int)ip->protocol<<endl;
  cout<<"Check:  "<<ip->check<<endl;
  cout<<"Source ip:  "<<inet_ntoa(*(in_addr*)&ip->saddr)<<endl;
  cout<<"Destination ip: "<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;
  
}


int main(int argc, char const *argv[])
{
	/* code */
	int rsfd=socket(AF_INET,SOCK_RAW,50);
  	char buff[1024];
  	memset(buff,0,sizeof(buff));
  	struct sockaddr_in cli_addr;
  	socklen_t size=sizeof(cli_addr); 

    while(1){
       char buff[1024];
  memset(buff,0,sizeof(buff));
  struct sockaddr_in cli_addr;
  socklen_t size =sizeof(cli_addr);
  recvfrom(rsfd,buff,1024,0,(sockaddr*)&cli_addr,&size); 
  cout<<"done receiving "<<endl;
    struct iphdr *ip;
    ip=(struct iphdr*)buff;
    print_ip(ip);
    cout<<(buff+(ip->ihl)*4)<<endl;
    cout<<buff<<endl; 
      }
	return 0;
}

