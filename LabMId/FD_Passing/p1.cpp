#include <bits/stdc++.h>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

using namespace std;
#define PORT 8080
#define MAX_PENDING_REQUESTS 10

#define SV_SOCK_PATH "/tmp/boom"
#define BUF_SIZE 100
#define BACKLOG 5

void handle_error(char* msg) {do { perror(msg); exit(EXIT_FAILURE); } while(0);}


int send_fd(int socket, int fd_to_send)
 {
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  /* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
  int available_ancillary_element_buffer_space;

  /* at least one vector of one byte must be sent */
  message_buffer[0] = 'F';
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;

  /* initialize socket message */
  memset(&socket_message, 0, sizeof(struct msghdr));
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
  memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = available_ancillary_element_buffer_space;

  /* initialize a single ancillary data element for fd passing */
  control_message = CMSG_FIRSTHDR(&socket_message);
  control_message->cmsg_level = SOL_SOCKET;
  control_message->cmsg_type = SCM_RIGHTS;
  control_message->cmsg_len = CMSG_LEN(sizeof(int));
  *((int *) CMSG_DATA(control_message)) = fd_to_send;

  return sendmsg(socket, &socket_message, 0);
 }
 
#define path "/tmp/boom"


int main(int argc, char const *argv[])
{
	
	struct sockaddr_un addr;
  int sfd, cfd;
  ssize_t numRead;
  char buf[BUF_SIZE];

  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if(sfd!=0){
    printf("socket success\n");
  }
  else{
    printf("socket unsuccessful\n");
  }


  printf("socket declared\n");

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

  if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un))!=0){
    printf("bind unsuccessful\n");
  }
  else{
    printf("bind successful\n");
  }


  if (listen(sfd, BACKLOG) != 0){
  printf("listen failed\n");
  }
  else{
     printf("listen succeeded\n");
  }

  socklen_t csize; 

while(1){

    cfd = accept(sfd, (struct sockaddr *)&addr,&csize);

    if (cfd < 0) {
      printf("accept failed: %s\n", strerror(errno));
    }
    else{
      printf("accept succeeded: %d\n", cfd);
    }

     while ((read(cfd, buf, BUF_SIZE)) > 0)
      write(1, buf, numRead); 
 }



	return 0;
}