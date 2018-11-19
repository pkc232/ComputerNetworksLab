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


using namespace std;


ssize_t write_fd(int fd,void *ptr,size_t nbytes,int sendfd){
	struct msghdr msg;
	struct iovec iov[1];

#ifdef HAVE_MSGHDR_MSG_CONTROL
	union{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	}control_un;

	struct cmsghdr *cmptr;
	
}

int main(int argc, char const *argv[])
{
	int fd = open(argv[2],atoi(argv[3]));
	write_fd(atoi(argv[1]),"",1,fd);
	return 0;
}