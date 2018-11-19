#include <bits/stdc++.h>
#include <stdio.h> //For standard things
#include <stdlib.h>    //malloc
#include <unistd.h>
#include <string.h>    //memset
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
using namespace std; 

#define MIN_IP_PACKET_LEN 20
#define BUFFER_LEN  100

int rsfd,ret,protocol_used,msglen=0;

void create_ip_header(struct iphdr* ip)
{
	ip->version=4;
	ip->ihl=5;
	ip->tos=0;
	ip->frag_off=0;
	ip->tot_len=htons(BUFFER_LEN);
	ip->ttl=htons(64);
	ip->id=htons(1234);
	ip->protocol=protocol_used;
	ip->saddr=inet_addr("127.0.0.3");
	ip->daddr=inet_addr("127.0.0.5");
	ip->check=0;

}

int main(int argc, char const *argv[])
{
	if(argc<2)
    {
        printf("Enter the protocol number as the commandline argument \n"); return 1;
    }
    protocol_used = atoi(argv[1]);
    rsfd = socket(AF_INET,SOCK_RAW,protocol_used);
    if(rsfd<0)
    {
        printf("Socket creation failed \n"); perror("socket\n"); return 1;
    }
    int optval = 1;
    ret = setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,&optval,sizeof(optval));
    if(ret<0)
    {
        printf("Error is setsockopt \n"); return 1;
    }
	struct sockaddr_in server,naddr;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    // while(1)
    {
    	char buffer[BUFFER_LEN];
    	socklen_t size=sizeof(naddr);
    	char msg[BUFFER_LEN];
    	printf("Enter the message : ");
    	scanf("%s",msg);
    	msglen = strlen(msg);
    	char packet[BUFFER_LEN];
    	struct iphdr* iph = (struct iphdr*)packet;
    	create_ip_header(iph);
    	printf("Message to be sent : %s \n",msg );
    	//strcat(packet,msg);
    	strcpy(packet+MIN_IP_PACKET_LEN,msg);
    	printf("Sending packet : %s \n",packet );
    	printf("Sending packet from IP : %s to IP : %s \n",inet_ntoa(*(in_addr*)&iph->saddr),inet_ntoa(*(in_addr*)&iph->daddr));
    	struct timeval stv,etv; struct timezone tz;
        gettimeofday(&stv,&tz);
        sendto(rsfd,packet,BUFFER_LEN,0,(struct sockaddr*)&server,sizeof(server));
    	recvfrom(rsfd,buffer,BUFFER_LEN,0,(struct sockaddr*)&naddr,&size);
        gettimeofday(&etv,&tz);
        printf("Message received form server at IP : %s\n",inet_ntoa(naddr.sin_addr));
        printf("Message : %s \n",buffer );
        int delay = etv.tv_usec-stv.tv_usec;
        printf("Time delay = %d microseconds \n",delay );
        
    }
    

	return 0;
}