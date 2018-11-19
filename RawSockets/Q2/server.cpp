#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
#define len 1024
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
int main(int argc,char *argv[])
{
  int rsfd=socket(AF_INET,SOCK_RAW,atoi(argv[1]));
   
  char buff[len];
  struct sockaddr_in cli_addr;
  socklen_t size=sizeof(cli_addr); 
  recvfrom(rsfd,buff,len,0,(sockaddr*)&cli_addr,&size); 
  cout<<"done receiving "<<endl;
  struct iphdr *ip;
  ip=(struct iphdr*)buff;
  print_ip(ip);
  cout<<(buff+(ip->ihl)*4)<<endl; 
  return 0;
}
