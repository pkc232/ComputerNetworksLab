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
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(PORT);
  if(bind(sfd,(struct sockaddr *)&add,sizeof(add))<0)
  cout<<"error in binding "<<endl;
  
  if(listen(sfd,1)<0)
  cout<<"error in listening"<<endl;
  int addrlen=sizeof(add);
  int nsfd=accept(sfd,(struct sockaddr *)&add,(socklen_t*)&addrlen);  
   char buff[50];
   recv(nsfd,buff,50,0);
   char *ip=strtok(buff,"|");
   char *fname=strtok(NULL,"|");
   int rsfd=socket(AF_INET,SOCK_RAW,atoi(argv[1]));
   if(rsfd==-1)
   cout<<"socket creation error"<<endl;
   opt=1;
   if(setsockopt(rsfd,IPPROTO_IP,SO_BROADCAST,&opt,sizeof(opt))<0)
   cout<<"setsock opt error"<<endl;
  //char buff[]="hello";
  struct sockaddr_in client;
  client.sin_family=AF_INET;
  client.sin_addr.s_addr=inet_addr(ip);
  connect(rsfd,(sockaddr*)&client,sizeof(client));
  int fd=open(fname,O_RDONLY);
  int c=fork();
  if(c==0)
  {
      dup2(fd,0);
      dup2(rsfd,1);
      execvp("./s2",NULL);
  }
  while(1){}

  return 0; 
}
