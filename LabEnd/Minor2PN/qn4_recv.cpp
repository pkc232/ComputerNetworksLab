#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>
using namespace std;
#define PORT 8000
int main(int argc,char *argv[])
{
  int opt=1;
   int rsfd=socket(AF_INET,SOCK_RAW,atoi(argv[1]));
   if(rsfd==-1)
   cout<<"socket creation error"<<endl;
   //char buff[]="hello";
  struct sockaddr_in client;
  client.sin_family=AF_INET;
  client.sin_addr.s_addr=inet_addr("127.0.0.1");
  while(1)
  {
     char msg[50];
     recv(rsfd,msg,50,0);
     struct iphdr *ip;
     ip=(struct iphdr*)msg;
     cout<<(msg+ip->ihl*4)<<endl;
  }
  return 0; 
}
