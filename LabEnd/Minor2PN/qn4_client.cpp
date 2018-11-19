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
  //int opt=1;
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr =INADDR_ANY;
  add.sin_port = htons(PORT);
  int addrlen=sizeof(add);
  connect(sfd,(struct sockaddr *)&add,addrlen);  
  char buff[]="127.0.0.1|a1.txt";

  send(sfd,buff,strlen(buff)+1,0);
  //connect(rsfd,(sockaddr*)&client,sizeof(client));
  sleep(5);
  while(1)
  {
     char msg[50];
     recv(rsfd,msg,50,0);
     struct iphdr *ip;
     ip=(iphdr *)&msg;
     cout<<(msg+ip->ihl*4)<<endl;
  }
  return 0; 
}
