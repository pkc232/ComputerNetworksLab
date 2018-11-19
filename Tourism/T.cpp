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
#include <pcap.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <bits/stdc++.h>
using namespace std;

void connectToAgent(int port_no,int ti,int li){
	int sfd;
	struct sockaddr_in serv_addr;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

	string s="";
	s+=to_string(ti);
	s+=to_string(li);
	// char buff[]="11";

	cout<<"Sending to agent "<<s<<endl;
	write(sfd,s.c_str(),100);
}

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

void PassFDToX(char* ADDRESS,int nsfd){
	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");

  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, "mysocket1");
	unlink(ADDRESS);

	cout<<"The address is "<<ADDRESS<<endl;
	userv_len = sizeof(userv_addr);
	int value=1;
	if (setsockopt(usfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
				perror("setsockopt failed");
	}
	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");

	listen(usfd, 5);
	cout<<"T is listening\n";
	ucli_len=sizeof(ucli_addr);
	int nusfd;
	nusfd=accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);

	send_fd(nusfd,nsfd);

}

void getConnectedToClient(){
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=8080;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int value=1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
				perror("setsockopt failed");
	}
	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,10);

	int nsfd;

	while(1){
		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		perror("\n accept ");
		else printf("\n accept successful");

		char buf[100];
		read(nsfd,buf,100);

		string msg(buf);
		stringstream ss;
		ss<<msg;
		int ti,li;
		ss>>ti>>li;
		string s="";
		s+=to_string(ti);
		s+=to_string(li);
		connectToAgent(8080+ti,ti,li);
		PassFDToX((char*)s.c_str(),nsfd);
	}

}

int main(int argc, char const *argv[])
{
	getConnectedToClient();
	return 0;
}