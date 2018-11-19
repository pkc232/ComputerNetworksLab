#include <bits/stdc++.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>



using namespace std;

int my_open(const char*,int);


ssize_t read_fd(int fd,void *ptr,size_t nbytes,int *recvfd){
	struct msghdr msg;
	struct iovec iov[1];
	ssize_t n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
	union{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	}control_un;

	struct cmsghdr *cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);

// #else
// 	int newfd;

// 	msg.msg_accrights = (caddr_t)&newfd;
	// msg.msg_accrightslen = sizeof(int);

#endif 
	msg.msg_name = NULL;
	msg.msg_namelen =0;

	iov[0].iov_base =ptr;
	iov[0].iov_len = nbytes;

	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	recvmsg(fd,&msg,0);

#ifdef HAVE_MSGHDR_MSG_CONTROL
	if((cmptr = CMSG_FIRSTHDR(&msg))&&cmptr->cmsg_len==CMSG_LEN(sizeof(int)))
	{
		*recvfd = *((int*)CMSG_DATA(cmptr));
	}
	else
		*recvfd = -1;
// #else 
// 	if(msg.msg_accrightslen == sizeof(int))
// 		*recvfd = newfd;
// 	else
// 		*recvfd = -1;
#endif
	return (n);
}


int main(int argc, char const *argv[])
{
	int fd,n;

	char buff[100];

	fd = my_open("./sample.txt",O_RDONLY);

	read(fd,buff,100);

	printf("Read %s\n",buff);

	return 0;
}


int my_open(const char* pathname,int mode){
	int fd,usfd[2],status;

	pid_t childpid;

	char c,argsockfd[10],argmode[10];
	socketpair(AF_LOCAL,SOCK_STREAM,0,usfd);

	if((childpid==fork())==0){
		close(usfd[0]);
		snprintf(argsockfd,sizeof(argsockfd),"%d",usfd[1]);
		snprintf(argmode,sizeof(argmode),"%d",mode);
		execl("./p2","p2",argsockfd,pathname,argmode,(char*)NULL);

	}

	close(usfd[1]);

	waitpid(childpid,&status,0);
	read_fd(usfd[0],&c,1,&fd);

	close(usfd[0]);
	return fd;

}

