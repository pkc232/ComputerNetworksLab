#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
#define pack 20

using namespace std;
int data_len;
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
int main(int argc,char *argv[])
{
  int rsfd=socket(AF_INET,SOCK_RAW,atoi(argv[1]));
  if(rsfd==-1)
  cout<<"socket creation error"<<endl;
  int opt=1;
  if(setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,&opt,sizeof(opt))<0)
  cout<<"setsock opt error"<<endl;
  //char buff[]="hello";
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
  set_ip_hdr(ip,atoi(argv[1]));	
  strcpy(buff+pack,data);
  cout<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;
  sendto(rsfd,buff,pack+data_len+1,0,(struct sockaddr*)&client,sizeof(client));
  cout<<"done sending "<<endl;
  return 0;
}
