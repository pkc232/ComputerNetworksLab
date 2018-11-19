#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#define PORT 8080
using namespace std;
int *x;

int main(int argc,char *argv[])
{
  int opt=1;
  
  key_t shmaccess= ftok(".",'n');
	
  int shmno=shmget(shmaccess,4*sizeof(int),IPC_CREAT|0666);
	//mem=(int *)shmat(shmno,NULL,0);
	x= (int*)shmat(shmno,NULL,0);
	*x=0;
  cout<<"hello from server!!"<<endl;  
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
  add.sin_port = htons(PORT);  
  int addrlen=sizeof(add);
  if(bind(sfd,(struct sockaddr *)&add,sizeof(add))<0)
  cout<<"error in binding "<<endl;
  
  if(listen(sfd,1)<0)
  cout<<"error in listening"<<endl;
   //cout<<"done \n"; 
     int nsfd=accept(sfd,(struct sockaddr *)&add,(socklen_t*)&addrlen);  
     if(nsfd<0)
     cout<<"error in accepting "<<endl;
     while(1){
     char buf[50],buff[]="hii from server";
     
     int len=recv(nsfd,buf,50,0);
     cout<<buf<<endl;
     send(nsfd,buff,strlen(buff)+1,0);
     }
  return 0;
}
