#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <fcntl.h>
using namespace std;
#define PORT 8080
int *x;
void send_fd(int socket, int fds, int n)  // send fd by socket
{
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(sizeof(fds))], dup[1];
        memset(buf, '\0', sizeof(buf));
        struct iovec io ;
        io.iov_base = &dup, io.iov_len = sizeof(dup) ;

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(n * sizeof(int));

        memcpy ((int *) CMSG_DATA(cmsg), &fds, sizeof (int));

        if (sendmsg (socket, &msg, 0) < 0)
                cout<<"Failed to send message";
}

int  recv_fd(int socket) {
        int *fds = (int *)malloc ( sizeof(int));
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE( sizeof(int))], dup[1];
        memset(buf, '\0', sizeof(buf));
        struct iovec io ;
        io.iov_base = &dup; 
        io.iov_len = sizeof(dup) ;
        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);

        if (recvmsg (socket, &msg, 0) < 0)
                cout<<"Failed to receive message";

        cmsg = CMSG_FIRSTHDR(&msg);

        memcpy (fds, (int *) CMSG_DATA(cmsg),  sizeof(int));

        return fds[0];
}
int fds;
void get_connect()
{
        cout<<"hey in connect"<<endl;
        int sfd;
        struct sockaddr_un addr;

        
        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
          cout<<"error"<<endl;
        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "fd-pass.socket1", sizeof(addr.sun_path));
       // unlink ("fd-pass.socket1");
        
        if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
                cout<<"Failed to connect to socket"<<endl;
         fds= recv_fd (sfd); 


}
void do_accept(int sfds)
{
      cout<<"hey in accept"<<endl;
       ssize_t nbytes;
        char buffer[256];
        int sfd, cfd;
        struct sockaddr_un addr;

        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
               cout<< "Failed to create socket"<<endl;

        unlink ("fd-pass.socket1") ;
        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "fd-pass.socket1", sizeof(addr.sun_path));

        if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
                cout<< "Failed to bind to socket\n";

        listen(sfd,1);
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
                cout<<"Failed to accept incoming connection";
        int n=1;
        //fds = recv_fd (cfd, n);
       send_fd (cfd, sfds, 1);
}

void use(int sfd)
{
     int n;
        char buf[50];
        
       string serv="hello from client"+to_string(getpid());
      send(sfd,serv.c_str(),serv.length()+1,0);
      recv(sfd,buf,50,0);
      cout<<buf<<endl;


}
int main(int argc,char *argv[])
{
  key_t shmaccess= ftok(".",'n');
	int shmno=shmget(shmaccess,4*sizeof(int),IPC_CREAT|0666);
	//mem=(int *)shmat(shmno,NULL,0);
	x= (int*)shmat(shmno,NULL,0);
	int opt=1;
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(PORT);
  cout<<*x<<endl;  
  if(*x==1)
     {     //cout<<"connection failed!!!"<<endl;
           while(1){
           get_connect(); 
           use(fds);        
           do_accept(fds);
           sleep(2);} 
     }
     else{
            connect(sfd,(struct sockaddr *)&add,sizeof(add));
     			 *x=1;
           while(1){
           use(sfd);
           do_accept(sfd);   
           sleep(2);
           get_connect();
           //use(fds); 
          }
           }
           *x=0;
  shmdt(x);//detach shm
	shmctl(shmno,IPC_RMID,NULL);//remove shared mem*/

  return 0;
 }
