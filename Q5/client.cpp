#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

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
        sum+=oddbyte;recvfrom(rsfd,buf,1
    }
 
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
     
    return(answer);
}

int main()
{
	int rsfd = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	if(rsfd<0)
	{
		cout<<"Socket error!"<<endl;
		return 1;
	}
	struct sockaddr_in server,client;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int one = 1;
	setsockopt(rsfd,IPPROTO_IP, ,&one,sizeof(one));
	
	struct iphdr* ip;
	char* buf = (char*)malloc(10000);
	strcpy((char*)(buf+sizeof(struct iphdr)),"Client");
	ip = (struct iphdr*)buf;
	ip->saddr = inet_addr("127.0.0.1");
	ip->daddr = inet_addr("127.0.0.1");
	ip->protocol = 50;
	ip->tot_len = sizeof(struct iphdr)+7;
    ip->check = csum ((unsigned short *) buf, ip->tot_len);
	ip->ihl = 5;
	ip->ttl = 255;
	ip->version = 4;
	ip->tos = 0;
	ip->id = htonl(56789);
	int len = sizeof(struct iphdr)+7;
	int sent_bytes = sendto(rsfd,buf,len,0,(struct sockaddr*)&server,sizeof(server));
	cout<<"Sent bytes: "<<sent_bytes<<endl;
	int nsfd = socket(AF_INET,SOCK_RAW,51);
	one = 0;
	while(true)
	{
		struct sockaddr_in client;
		char* rbuf = (char*)malloc(10000);
		strcpy(rbuf,"");
		socklen_t socklen = sizeof(struct sockaddr_in);
		while(true)
		{
			cout<<"before"<<endl;
			int recv_bytes = recvfrom(nsfd,rbuf,10000,0,(struct sockaddr*)&client,&socklen);
			cout<<"rb: "<<recv_bytes<<endl;
			if(recv_bytes>0)
				break;
		}
		char* data= (char*)(rbuf+sizeof(struct iphdr));
		cout<<data<<endl;
		int port = atoi(data);
		cout<<"Server's port: "<<port<<endl;
	}
	
	return 0;
}
