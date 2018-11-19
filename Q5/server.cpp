#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

unsigned short csum(unsigned short *ptr,int nbytes) 
{
    register long sum;
    unsigned short oddbyte;
    register short answer;
 
    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }
 
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
     
    return(answer);
}

void itoa(char* buf,int val)
{
	int i=0;
	do
	{
		buf[i++] = val%10+'0';
		val /= 10;
	}while(val);
	for(int j=0;j<i/2;j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i-j-1];
		buf[i-j-1] = tmp;
	}
}

int main()
{
	int rsfd = socket(AF_INET,SOCK_RAW,50);
	struct sockaddr_in client;
	socklen_t socklen = sizeof(struct sockaddr_in);
	char* buf = (char*)malloc(10000);
	int recv_bytes;
	
	recv_bytes = recvfrom(rsfd,buf,10000,0,(struct sockaddr*)&client,&socklen);
	cout<<recv_bytes<<endl;
	
	cout<<"Received bytes: "<<recv_bytes<<endl;
	buf = (char*)(buf+sizeof(struct iphdr));
	cout<<"buf: "<<buf<<endl;
	cout<<"pid: "<<getpid()<<endl;
	char* rbuf = (char*)malloc(10000);
	
	int one = 1;
	setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,&one,sizeof(one));
	
	struct iphdr* ip = (struct iphdr*)rbuf;
	ip->saddr = inet_addr("127.0.0.1");
	ip->daddr = inet_addr("127.0.0.1");
	ip->protocol = 51;
	ip->tot_len = sizeof(struct iphdr)+5;
    ip->check = csum ((unsigned short *) rbuf, ip->tot_len);
	ip->ihl = 5;
	ip->ttl = 255;
	ip->version = 4;
	ip->tos = 0;
	ip->id = htonl(12345);
	itoa((char*)(rbuf+sizeof(struct iphdr)),getpid());
	struct sockaddr_in nclient;
	nclient.sin_family = AF_INET;
	nclient.sin_addr.s_addr = inet_addr("127.0.0.1");
	int len = sizeof(struct iphdr)+5;
	sleep(1);
	int sent_bytes = sendto(rsfd,rbuf,len,0,(struct sockaddr*)&nclient,sizeof(nclient));
	cout<<sent_bytes<<endl;
	return 0;
}
