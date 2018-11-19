#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;
#define pack 20

int data_len;

int rsfd;
int protno1=50,protno2=51;
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

void set_ip_hdr(struct iphdr *ip,int no)
{
  	ip->version=4;
	ip->ihl=5;
	ip->tos=0;
	ip->frag_off=0;
	ip->tot_len=htons(pack+data_len);
	ip->ttl=htons(100);
	ip->id=htons(1234);
	ip->protocol=no;
	ip->saddr=inet_addr("127.0.0.7");
	ip->daddr=inet_addr("127.0.0.1");
	ip->check=0;
}

void recvPacket(){
	char buff[1024];
	struct sockaddr_in cli_addr;
	socklen_t size =sizeof(cli_addr);
	recvfrom(rsfd,buff,1024,0,(sockaddr*)&cli_addr,&size); 
	cout<<"done receiving "<<endl;
  	struct iphdr *ip;
  	ip=(struct iphdr*)buff;
  	print_ip(ip);
  	cout<<(buff+(ip->ihl)*4)<<endl; 
}
void sendpacket(int prot){
	struct sockaddr_in client;
  	client.sin_family=AF_INET;
  	client.sin_addr.s_addr=inet_addr("127.0.0.1");

  	char data[30];
  	cout<<"enter the data"<<endl;
  	fgets(data,30,stdin);
  	data[strlen(data)-1]='\0';
  	data_len=strlen(data);
	char buff[pack+data_len+1];

	struct iphdr *ip;
  	ip=(struct iphdr*)buff; 
  	set_ip_hdr(ip,prot);	
  	strcpy(buff+pack,data);
  	cout<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;
  	sendto(rsfd,buff,pack+data_len+1,0,(struct sockaddr*)&client,sizeof(client));
  	cout<<"done sending "<<endl;
}


int main(int argc, char const *argv[])
{
	rsfd = socket(AF_INET,SOCK_RAW,protno1);
	if(rsfd==-1)
	{
		perror("socket creation error");
	}
	int opt=1;
	if(setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,&opt,sizeof(opt))<0)
  		perror("setsockopt error\n");
	recvPacket();
	sendpacket(protno2);

	return 0;
}