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
#include <arpa/inet.h>
using namespace std; 

#define MIN_IP_PACKET_LEN 20
#define BUFFER_LEN  100

int rsfd,ret;

void print_ip_header(struct iphdr* iph)
{
    unsigned short iphdrlen;
         
    
    iphdrlen =iph->ihl*4;
    struct sockaddr_in saddr,daddr,source,dest;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    FILE* logfile = stdout; 
    fprintf(logfile,"\n");
    fprintf(logfile,"IP Header\n");
    fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
    fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
    fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
    fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
    fprintf(logfile,"   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}

int main(int argc, char const *argv[])
{
    if(argc<2)
    {
        printf("Enter the protocol number as the commandline argument \n"); return 1;
    }
    rsfd = socket(AF_INET,SOCK_RAW,atoi(argv[1]));
    if(rsfd<0)
    {
        printf("Socket creation failed \n"); perror("socket\n"); return 1;
    }
    char buffer[BUFFER_LEN];
    // while(1)
    {
        char reply[]="Message received by server ";
        struct sockaddr_in cli_addr;
        socklen_t size=sizeof(cli_addr); 
        printf("Receiving message \n");
        recvfrom(rsfd,buffer,1024,0,(sockaddr*)&cli_addr,&size); 
        printf("Buffer received : %s \n",buffer );
        printf("Server sending : %s \n",reply );
        sendto(rsfd,reply,BUFFER_LEN,0,(struct sockaddr*)&cli_addr,size);
        struct iphdr *ip=(struct iphdr*)buffer;
        print_ip_header(ip);
        int iphdrlen = (ip->ihl)*4;
        char* msg = buffer+iphdrlen;
        printf("Message : %s \n",msg );
    }
    return 0;
}