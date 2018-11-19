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

int HaveFD=0;
int globalFD;
int currClientNumber;

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


 int recv_fd(int socket)
 {
  int sent_fd, available_ancillary_element_buffer_space;
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];

  /* start clean */
  memset(&socket_message, 0, sizeof(struct msghdr));
  memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));

  /* setup a place to fill in message contents */
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = CMSG_SPACE(sizeof(int));

  if(recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC) < 0)
   return -1;

  if(message_buffer[0] != 'F')
  {
   /* this did not originate from the above function */
   return -1;
  }

  if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
  {
   /* we did not provide enough space for the ancillary element array */
   return -1;
  }

  /* iterate ancillary elements */
   for(control_message = CMSG_FIRSTHDR(&socket_message);
       control_message != NULL;
       control_message = CMSG_NXTHDR(&socket_message, control_message))
  {
   if( (control_message->cmsg_level == SOL_SOCKET) &&
       (control_message->cmsg_type == SCM_RIGHTS) )
   {
    sent_fd = *((int *) CMSG_DATA(control_message));
    return sent_fd;
   }
  }

  return -1;
 }


int ConnectToESS(int port_no){
	int sfd;
	struct sockaddr_in serv_addr;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

	write(sfd,"hello",100);
	return sfd;
}


void PassFDToClient(int clientNo,int fdToPass){

	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	// perror("socket");
	// printf("Galti\n");
  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;


  	string add="";
  	add+="socket";
  	add+=to_string(clientNo);
  	cout<<"Sending to "<<add.c_str()<<endl;
	strcpy(userv_addr.sun_path,add.c_str());
	unlink(add.c_str());
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");

	listen(usfd, 5);

	ucli_len=sizeof(ucli_addr);

	int nusfd;
	nusfd=accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);

	cout<<"Wee are over here\n";
	cout<<"Sending fd "<<fdToPass<<endl;
	send_fd(nusfd,fdToPass);
}


int recvFDFromClient(int myNumber){
	int usfd;
	struct sockaddr_un userv_addr;
  	socklen_t userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;


  	string add="";
  	add+="socket";
  	add+=to_string(myNumber);
   	strcpy(userv_addr.sun_path, add.c_str());

	userv_len = sizeof(userv_addr);

	if(connect(usfd,(struct sockaddr *)&userv_addr,userv_len)==-1)
	;// perror("\n unix connect ");
	else
	 printf("\nconnect succesful");



	int fd=recv_fd(usfd);

	if(fd==-1){
		// printf("No fd received\n");
	}
	return fd;
}

void sendInfoToAllClients(int myNumber){
	int rsfd=socket(AF_INET,SOCK_RAW,52);
	struct sockaddr_in client;
  	client.sin_family=AF_INET;
  	client.sin_addr.s_addr=inet_addr("127.0.0.1");
  	if(connect(rsfd , (struct sockaddr *)&client , sizeof(client) )==-1)
	;// perror("\n connect : ");
	else
	printf("\nconnect succesful");
  	string s="";
  	s+=to_string(myNumber);
  	char buff[1024];
  	strcpy(buff,(char*)s.c_str());
  	{
	write(rsfd,buff,1024);
  	}
}

int getNotifiedAboutClient(){
	int rsfd=socket(AF_INET,SOCK_RAW,52);
	if(rsfd==-1)
		return rsfd;
  	char buff[1024];
  	memset(buff,0,sizeof(buff));
  	struct sockaddr_in cli_addr;
  	socklen_t size=sizeof(cli_addr);
  	read(rsfd,buff,1024); 
  	cout<<"done receiving "<<endl;
  	 struct iphdr *ip;
    ip=(struct iphdr*)buff;
    // print_ip(ip);
    cout<<"Client Number "<<(buff+(ip->ihl)*4)<<" joined\n";
    int clientNo = atoi((buff+(ip->ihl)*4));
    return clientNo;
}

void *listenToOtherClients(void *args){
	while(1){
	int clientJoined=getNotifiedAboutClient();
	if(clientJoined!=-1){
		cout<<"Client joined is "<<clientJoined<<endl;
		string s="";
		s+=to_string(clientJoined);
		write(globalFD,s.c_str(),100);
	}
	}
}

void *getRAWwithESS(void *args){
	int rsfd=socket(AF_INET,SOCK_RAW,50);
  	char buff[1024];
  	memset(buff,0,sizeof(buff));
  	struct sockaddr_in cli_addr;
  	socklen_t size=sizeof(cli_addr); 
  	while(1){
  		cout<<"Waiting to read\n";
  	  	read(rsfd,buff,1024); 
  	  	// cout<<"In buffer "<<buff<<endl;
  	  	// char* p =(buff+(ip->ihl)*4);
  	  	// if(buff[0]>='0'&&buff[0]<='9')
  	  	{
  	  	  		cout<<"done receiving "<<endl;
  	  	  	   	struct iphdr *ip;
  	  	  	    ip=(struct iphdr*)buff;
  	  	  	    // print_ip(ip);
  	  	  	    int clientNoTOConnect=atoi((buff+(ip->ihl)*4));
  	  	  	    cout<<"server wants to connect with "<<clientNoTOConnect<<endl;
  	  	  	    if(clientNoTOConnect!=currClientNumber){
  	  	  	      	HaveFD=0;
  	  	  	      	PassFDToClient(clientNoTOConnect,globalFD);
  	  	  	 }
  	  	}
  	}
}

void *takeServiceFromESS(void *args){
	while(1){

		if(HaveFD){
				char buf[100];
				cout<<"What shall i send to server?\n";
				cin>>buf;
				write(globalFD,buf,100);
		}
	}
}

void *waitFORFD(void *args){
		int fd=-1;
		while(1){
			if(!HaveFD){
				cout<<"waiting for fd\n";
			fd=recvFDFromClient(currClientNumber);
				if(fd!=-1)
				{
					HaveFD=1;
					cout<<"I received fd\n";
				}
			}
			sleep(2);
		}
}
int main(int argc, char const *argv[])
{

	if(argc<2){
		printf("Add client number too\n");
	}
	int cliNo=atoi(argv[1]);
	currClientNumber=cliNo;
	if(cliNo==1){
		globalFD=ConnectToESS(8080);
		HaveFD=1;
	}
	else
	{
		sendInfoToAllClients(cliNo);
	}
	
	pthread_t takeService_t,listenToClients_t,listenToESSRAW_t,waitforFD_t;
	pthread_create(&takeService_t,NULL,takeServiceFromESS,NULL);
	pthread_create(&listenToClients_t,NULL,listenToOtherClients,NULL);
	pthread_create(&listenToESSRAW_t,NULL,getRAWwithESS,NULL);
	pthread_create(&waitforFD_t,NULL,waitFORFD,NULL);

	pthread_join(takeService_t,NULL);
	pthread_join(listenToClients_t,NULL);
	pthread_join(listenToESSRAW_t,NULL);
	pthread_join(waitforFD_t,NULL);
	return 0;
}