HEADER FILES
--------------------------------------------------------------------------------------------------------------------------------
#include <bits/stdc++.h>
#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<pcap.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
using namespace std;


SEND_FD AND RECV_FD
---------------------------------------------------------------------------------------------------------------------

void handle_error(string msg) {do { perror(msg.c_str()); exit(EXIT_FAILURE); } while(0);}

// SENDING
static
void send_fd(int socket, int *fds, int n)  // send fd by socket
{
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(sizeof(fds))], dup[256];
        // memset(buf, ‘\0’, sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(n * sizeof(int));

        memcpy ((int *) CMSG_DATA(cmsg), fds, n * sizeof (int));

        if (sendmsg (socket, &msg, 0) < 0)
                handle_error ("Failed to send message");
}


int main()
{
	int rfd = open("file.txt",O_RDONLY);

	int usfd;
	struct sockaddr_un userv_addr;
  	socklen_t userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strncpy(userv_addr.sun_path, ADDRESS,sizeof (userv_addr.sun_path));

	userv_len = sizeof(userv_addr);
	//sleep(5);
	if(connect(usfd,(struct sockaddr *)&userv_addr,sizeof(struct sockaddr_un))==-1)
	perror("\n connect ");

	else printf("\nconnect succesful");
	
	int afd[1]; afd[0]=rfd;
	send_fd(usfd,afd,1);
}

//RECEIVING
static
int * recv_fd(int socket, int n) {
        int *fds = (int*)malloc (n * sizeof(int));
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(n * sizeof(int))], dup[256];
        //memset(buf, ‘\0’, sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);
        
        if (recvmsg (socket, &msg, 0) < 0)
                handle_error ("Failed to receive message");

        cmsg = CMSG_FIRSTHDR(&msg);

        memcpy (fds, (int *) CMSG_DATA(cmsg), n * sizeof(int));

        return fds;
}

int main()
{
	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	// perror("socket");
	if (usfd == -1)
                handle_error ("Failed to create socket");

    if (unlink ("/tmp/fd-pass.socket") == -1 && errno != ENOENT)
                handle_error ("Removing socket file failed");
  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strncpy(userv_addr.sun_path, "/tmp/fd-pass.socket",  sizeof(userv_addr.sun_path));
	
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	else printf("bind successful\n");
	 if (listen(usfd, 5) == -1)
                handle_error ("Failed to listen on socket");
         printf("Accepting the new connection \n");

    int nsfd = accept(usfd, NULL, NULL);
        printf("nsfd = %d \n",nsfd );
        if (nsfd == -1)
                handle_error ("Failed to accept incoming connection");

       int* afd = recv_fd (nsfd,1);
       int rfd = afd[0];      

	
	
	printf("rfd = %d \n",rfd );
	char ch;
	while(read(rfd,&ch,1)>0) 
	{
		printf("%c",ch );
	}
}

POPEN
---------------------------------------------------------------------------------------------------------------------

//P1 PIP1
int main()
{
	FILE* fp=popen("./p2","w");
	int fd=fileno(fp);
	string s;
	cin>>s;
	cout<<"Programm p1 gets input = "<<s<<endl;
	write(fd,s.c_str(),strlen(s.c_str()));
	cout<<"Programm p1 outputs it to p2 "<<endl;
}

//MAINPIPE
int main(int argc, char const *argv[])
{
	FILE* fp=popen("./p1","w");
	int fd=fileno(fp);
	cout<<"Enter the input "<<endl;
	string s;
	cin>>s;
	write(fd,s.c_str(),strlen(s.c_str()));
	return 0;
}


BYPASS SERVER
---------------------------------------------------------------------------------------------------------------------

//GROUP1
int main(int argc,char* argv[])
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr,saddr,caddr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(argv[1]));
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	int c=connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	printf("%d\n",c);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(atoi(argv[2]));
	saddr.sin_addr.s_addr=INADDR_ANY;
	write(sfd,(struct sockaddr*)&saddr,sizeof(saddr)+1);
	int sfd1=socket(AF_INET,SOCK_STREAM,0);
	bind(sfd1,(struct sockaddr*)&saddr,sizeof(saddr));
	listen(sfd1,5);
	while(1)
	{
		socklen_t size;
		int nsfd=accept(sfd1,(struct sockaddr*)&caddr,&size);
		char buffer[30];
		read(nsfd,buffer,11);
		printf("%s\n",buffer);
	}
}
//BYPASS
int main(int argc,char* argv[])
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr,caddr,saddr,saddr1;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=htons(atoi(argv[1]));
	bind(sfd,(struct sockaddr* )&addr,sizeof(addr));
	listen(sfd,5);
	int sfd1=socket(AF_INET,SOCK_DGRAM,0);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(atoi(argv[2]));
	inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr);
	socklen_t size;
	while(1)
	{
		int nsfd=accept(sfd,(struct sockaddr* )&addr,&size);
		write(1,"before read",12);
		int c=read(nsfd,(struct sockaddr* )&saddr1,sizeof(saddr));
		printf("%d\n",c);
		write(1,"after read",11);
		sendto(sfd1,(struct sockaddr*)&saddr1,sizeof(saddr1),0,(struct sockaddr* )&saddr,sizeof(saddr));
		write(1,"after send",11);
	}
}
//GROUP2
int main(int argc,char* argv[])
{
	struct sockaddr_in addr,saddr,caddr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(argv[1]));
	addr.sin_addr.s_addr=INADDR_ANY;
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	socklen_t size;size_t s=sizeof(addr);
	recvfrom(sfd,(struct sockaddr*)&saddr,s,0,(struct sockaddr*)&caddr,&size);
	int sfd1=socket(AF_INET,SOCK_STREAM,0);
	connect(sfd1,(struct sockaddr*)&saddr,sizeof(saddr));
	write(sfd1,"serviced 1",11);
	while(1);
}

SIGNALLING
---------------------------------------------------------------------------------------------------------------------

//PROCESS 1
void sighandler(int sig)
{
	cout<<"\np1 is writing : \n";
	int n=0; char ch;
	while(n<5)
	{
		if(read(fd,&ch,1)==0) { eof=0; break; }
		if(ch=='\n') { n++; }
		cout<<ch;
	}
	kill(c,SIGUSR1);
}

int main()
{
	signal(SIGUSR2,sighandler);
	eof=1;
	fd=open("file2.txt",O_RDONLY);


	dup2(fd,0);
	int p = getpid(); cout<<"Process id of p1 = "<<p<<endl;
	c = fork();
	if(c>0)
	{
		while(eof) { ; }
	}
	else
	{
		execvp("./process2",NULL);
	}
	return 0;

}

//PROCESS 2
void sighandler(int sig)
{
	cout<<"\np2 is writing : \n";
	int n=0; char ch;
	while(n<5)
	{
		if(read(fd,&ch,1)==0) { eof=0; break; }
		if(ch=='\n') { n++; }
		cout<<ch;
	}
	kill(getppid(),SIGUSR2);
}

int main()
{
	signal(SIGUSR1,sighandler);
	eof=1; //fd=dup(0);
	dup2(0,fd);
	int p = getppid(); cout<<"Process id of p1 from p2 = "<<p<<endl;
	kill(getppid(),SIGUSR2);
	while(eof) { ; }
	return 0;

}


POLLING
---------------------------------------------------------------------------------------------------------------------

int fd1,fd2;

   char buf[1024];

   int i;

   struct pollfd pfds[2];

   fd1 = open("file1.txt", O_RDONLY);
   fd2 = open("file2.txt",O_RDONLY);


   while (1) {

       pfds[0].fd = fd1;

       pfds[0].events = POLLIN;


       pfds[1].fd = fd2;

       pfds[1].events = POLLIN;


       poll(pfds, 2, 1000);

       if (pfds[0].revents & POLLIN) {

          i = read(fd1, buf, 1024);

          if (!i) {

              printf("stdin closed \n ");

              return 0;

          }

          write(1, buf, i);

       }


       if (pfds[1].revents & POLLIN) {

          i = read(fd2, buf, 1024);

          if (!i) {

              printf(" file closed\n ");

              return 0;

          }

          write(1, buf, i);

       }

    }

MULTIPORT SERVER
---------------------------------------------------------------------------------------------------------------------

#define PORT1 8081
#define PORT2 8082
#define PORT3 8083
#define MAX_PENDING_REQUESTS 10
#define BUFFER_LEN 100
#define MAX_SERVICES 10




int main(int argc, char const *argv[])
{
	printf("Beginning server program \n");
	int sfd1,sfd2,sfd3,ret,nsfd1,nsfd2,nsfd3,sret,service;
	pid_t childPid1=0,childPid2=0,childPid3=0;

	socklen_t addrlen;
	struct sockaddr_in saddr1,saddr2,saddr3,newaddr, peeraddr;
	saddr1.sin_family = AF_INET;	saddr2.sin_family = AF_INET;	saddr3.sin_family = AF_INET;
    saddr1.sin_addr.s_addr = inet_addr("127.0.0.1"); 	saddr2.sin_addr.s_addr = inet_addr("127.0.0.1"); 	saddr3.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    saddr1.sin_port = htons( PORT1 );  saddr2.sin_port = htons( PORT2 );	saddr3.sin_port = htons( PORT3 ); //converts unsigned long int form host byte order to network byte order
	

	sfd1 = socket(AF_INET,SOCK_STREAM,0);	sfd2 = socket(AF_INET,SOCK_STREAM,0);	sfd3 = socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0 || sfd2<0 || sfd3<0)
	{
		printf("Error in creting socket \n"); exit(0);
	}
	printf("Server: Created 3 Sockets \n");

	// Forcefully attaching socket to the port 8080
    ret =  bind(sfd1, (struct sockaddr *)&saddr1, sizeof(saddr1));	ret =  bind(sfd2, (struct sockaddr *)&saddr2, sizeof(saddr2));	ret =  bind(sfd3, (struct sockaddr *)&saddr3, sizeof(saddr3));
    if (ret<0)
    {
        printf("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server: Binded\n");

    ret = listen(sfd1,MAX_PENDING_REQUESTS);	ret = listen(sfd2,MAX_PENDING_REQUESTS);	ret = listen(sfd3,MAX_PENDING_REQUESTS);
    if(ret<0){
    	printf("listen failed\n ");
    	exit(EXIT_FAILURE);
    }

    fd_set readfds;
	struct timeval timeout;

    
    while(1)
    {
    	FD_ZERO(&readfds);
    	FD_SET(sfd1,&readfds); FD_SET(sfd2,&readfds); FD_SET(sfd3,&readfds);
    	printf("Server: Listening \n");
    	timeout.tv_sec = 10; timeout.tv_usec = 0;
		printf("Selecting the readfds \n");
		sret = select(MAX_SERVICES,&readfds,NULL,NULL,&timeout);

		if(sret==0)
		{
			printf("sret = %d \n",sret );
			printf("Timeout \n");
		}
		else
		{
			printf("Number of bits set = %d \n",sret );
			if(FD_ISSET(sfd1,&readfds))
			{
				printf("Request came for service 1 \n");
				addrlen = sizeof newaddr;
				nsfd1 = accept(sfd1, (struct sockaddr *)&newaddr, &addrlen);
				if (nsfd1<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}

				//printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohl(newaddr.sin_port) );
    			addrlen = sizeof newaddr;
    			 int ret = getpeername(nsfd1,(struct sockaddr*)&newaddr, &addrlen);
    			 printf("Using getpeername() IP : %s : %d\n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			printf("ret = %d \n",ret );
    			if(ret<0)
    			{
    				printf("Error in getpeername \n"); exit(0);
    			}
				service = 1;
				printf("Forking new process \n");
				childPid1 = fork(); 
				if(childPid1==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd1);
				}
				
			}
			if(FD_ISSET(sfd2,&readfds))
			{
				printf("Request came for service 2 \n");
				nsfd2 = accept(sfd2, (struct sockaddr *)&newaddr,&addrlen);
				printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			if (nsfd2<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}
				service = 2;
				printf("Forking new process \n");
				childPid2 = fork(); 
				if(childPid2==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd2);
				}
				
			}
			if(FD_ISSET(sfd3,&readfds))
			{
				printf("Request came for service 3 \n");
				nsfd3 = accept(sfd3, (struct sockaddr *)&newaddr, &addrlen);
				printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    			if (nsfd3<0)
    			{
       				printf("Error in accepting \n");
       				 exit(EXIT_FAILURE);
    			}
				service = 3;
				printf("Forking new process \n");
				childPid3 = fork(); 
				if(childPid3==0) {
					printf("Inside child process. \n");
					close(sfd1); close(sfd2); close(sfd3);
					break;
				}
				else
				{
					printf("Inside parent process \n");
					close(nsfd3);
				}
				
			}


		}
	}
	if(childPid1==0 || childPid2==0 || childPid3==0)
	{
		char buffer[BUFFER_LEN];
		printf("Servicing in child process \n");
		int server_id = getpid(),nsfd;
		
		if(service ==1)
		{
			nsfd = nsfd1;
			int valread = recv( nsfd1 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 1 \n"); exit(EXIT_FAILURE);
    		}
    	}
    	else if(service == 2)
    	{
    		nsfd = nsfd2;
    		int valread = recv( nsfd2 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 2\n"); exit(EXIT_FAILURE);
    		}

    	}
    	else if(service ==3 )
    	{
    		nsfd = nsfd3;
    		int valread = recv( nsfd3 , buffer, BUFFER_LEN,0);
    		if(valread<0)
    		{
    			printf("Error in reading 3\n"); exit(EXIT_FAILURE);
    		}
    	}

    	printf("Server %d giving service %d to client %s  \n",server_id,service,buffer );
    	stringstream ss; string sserv; ss<<service; ss>>sserv;
    	string msg = "Server gave service "+sserv+ " to client ";
    	send(nsfd , msg.c_str() ,BUFFER_LEN , 0 );
    	close(nsfd);
	}
    
    printf("Child Server exiting \n");
    
    
	return 0;
}

CRC
---------------------------------------------------------------------------------------------------------------------


string modulo_2_divide(string sendm,string key){
		int m = sendm.length();
		int r = key.length();
		int i=0;
		string rem ,div="";
		rem=sendm.substr(0,r);
		while(i <= m-r){
			cout<<rem<<"\n";
			if(rem[0]=='0'){
				div+='0';
				if(i != m-r){
					for(int j=1;j<r;j++) rem[j-1]=rem[j];
					rem[r-1]=sendm[i+r];
				}
				
			}
			else{
				div+='1';
				for(int j=0;j<r;j++){
					if(rem[j]=='0' && key[j]=='1') rem[j]='1';
					else if(rem[j]=='1' && key[j]=='1') rem[j]='0';
				}
				if(i != m-r){
					for(int j=1;j<r;j++) rem[j-1]=rem[j];
		   			rem[r-1]=sendm[i+r];
				}
				
			}

			i++;
		}
		cout<<"Divident : "<<div<<"\n";
		return rem.substr(1,r-1);
}

int main(){
	string sendm;   //sender message
	string recvm;   //receiver message
	string key;     //key or polynomial

	cout<<"Enter sender message : ";
	cin>>sendm;
	cout<<"Enter key : ";
	cin>>key;

	int k = key.length();
	int m = sendm.length();
	int r=k-1;
	for(int i=0;i<r;i++) sendm+="0";

	string crc = modulo_2_divide(sendm,key);
	cout<<"CRC : "<<crc<<"\n";

	cout<<"Enter receiver message : ";
	cin>>recvm;

	recvm+=crc;
	crc = modulo_2_divide(recvm,key);
	cout<<"Remainder of receiver : "<<crc<<"\n";
}


SHARED MEMORY
---------------------------------------------------------------------------------------------------------------------


key_t Key=ftok(".",1234);
	int shmid=shmget(Key,sizeof(int), 0644 | IPC_CREAT),i,j=0,initial_value=1,l=1,status=0;
	int* p = (int *) shmat (shmid, NULL, 0);
	sem_t* sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644,initial_value); 
	sem_unlink ("pSem");
	pid_t cpid,wpid;
	*p=5;
	for(i=1;i<=3;i++)
	{
		cpid=fork();
		if(cpid<0) printf("Error forking \n");
		else if(cpid==0) break;
		printf("Pid of Process %d = %d\n",i,cpid );
	}
	if(cpid!=0)
	{
		while (wait(&status) > 0);
		printf("All child processes have terminated \n");
		shmdt(p);
		shmctl (shmid, IPC_RMID, 0);
		//sem_destroy(sem);
		sem_close(sem);

	}
	else{
		printf("Child %d has started execution \n",i );
		while(j++<3)
		{
			sem_wait(sem);
			printf("Child %d has read value %d in iteration %d \n",i,*p,j);
			*p+=i;
			printf("Child %d has written value %d in iteration %d\n",i,*p,j);
			sem_post(sem);
			sleep(1);
		}
		printf("Child %d has finished execution.\n",i );
		exit(0);
	}
	return 0;

EXCLUSIVE SUPER SERVER
---------------------------------------------------------------------------------------------------------------------
//SERVER
char buffer[BUFFER_LEN];

void handle_error(char* msg) {do { perror(msg); exit(EXIT_FAILURE); } while(0);}

int main(int argc, char const *argv[])
{
	printf("Beginning server program \n");
	int sfd,ret,nsfd;

	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		printf("Error in creting socket \n"); exit(0);
	}
	printf("Server: Created Socket \n");
	;
    
	struct sockaddr_in saddr,newaddr;
	saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons( PORT ); 

	// Forcefully attaching socket to the port 8080
    ret =  bind(sfd, (struct sockaddr *)&saddr, 
                                 sizeof(saddr));
    if (ret<0)
    {
        printf("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server: Binded\n");

    ret = listen(sfd,MAX_PENDING_REQUESTS);
    if(ret<0){
    	printf("listen failed\n ");
    	exit(EXIT_FAILURE);
    }
	printf("Server: Listening \n");
	socklen_t len=sizeof newaddr;
    nsfd = accept(sfd, (struct sockaddr *)&newaddr, &len);
    printf("Connection accepted from %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
    if (nsfd<0)
    {
       	printf("Error in accepting \n");
        exit(EXIT_FAILURE);
    }
    printf("ESS serving through socket %d \n",nsfd );
    while(1)
    {
    	recv(nsfd,buffer,BUFFER_LEN,0);
    	string S(buffer);
    	printf("Server received : %s \n",S.c_str() );
    	for(int i=0;i<S.length(); i++) S[i]=toupper(S[i]);
    	printf("Server sending : %s \n",S.c_str() );
    	send(nsfd , S.c_str() ,BUFFER_LEN , 0 );
    }
	return 0;
}

//CLIENT
void signalHandler1(int sig)
{
		printf("Signal received from previous process in circle. Now I will receive the connected socekt \n");
		ssize_t nbytes;
        char buffer[256];
        int sfd, cfd2, *fds;
        struct sockaddr_un addr;

        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
                handle_error ("Failed to create socket");

        if (unlink ("/tmp/fd-pass.socket") == -1 && errno != ENOENT)
                handle_error ("Removing socket file failed");

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "/tmp/fd-pass.socket",  sizeof(addr.sun_path));

        if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
                handle_error ("Failed to bind to socket");
        printf("Listening for new connection from previous process \n");
        if (listen(sfd, 5) == -1)
                handle_error ("Failed to listen on socket");
         printf("Accepting the new connection \n");
        cfd2 = accept(sfd, NULL, NULL);
        printf("CFD2 = %d \n",cfd2 );
        if (cfd2 == -1)
                handle_error ("Failed to accept incoming connection");

        fds = recv_fd (cfd2, 1);
        cfd = fds[0];
        isAvailable = true;
}

void signalHandler2(int sig)
{
	int rfd = open(fifoName,O_RDONLY);
	char process[100];
	sleep(1);
	read(rfd,process,BUFFER_LEN);

	close(rfd);
	printf("Process ID of the new process entering the circle = %s \n",process );
	int temp = atoi(process);
	stringstream ss; string s;
	ss<<nextProcess; ss>>s;
	int wfd = open(fifoName,O_WRONLY);
	printf("Process ID of the next process of %d is %d \n",myPid,nextProcess );
	write(wfd,s.c_str(),BUFFER_LEN);
	nextProcess = temp;
	printf("So now for process %d nextProcess = %d \n",myPid,nextProcess );
}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,signalHandler1);
	signal(SIGUSR2,signalHandler2);
	printf("Client program started \n");
	myPid = getpid();
	
	printf("My Process ID = %d \n",myPid);

	printf("Enter process ID of the last Process in the circle \n");
	scanf("%d",&lastProcess);
	printf("Lastprocess = %d My PID = %d \n",lastProcess,myPid );
   	if(lastProcess == myPid)
   	{
   		
   		printf("I am the first client process. I will establish connection with server \n");
   		int ret;
   		nextProcess = lastProcess;
	   	struct sockaddr_in saddr;
	    
	    cfd = socket(AF_INET, SOCK_STREAM, 0);
	    printf("CFD = %d \n",cfd );
	    if (cfd < 0)
	    {
	        printf("\n Socket creation error \n");
	        return -1;
	    }
	  	printf("Socket created \n");

	  	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	    saddr.sin_family = AF_INET;
	    saddr.sin_port = htons(PORT);

	    ret = connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr));
	  	printf("Return value after connect() = %d \n",ret  );
	    if ( ret < 0)
	    {
	        printf("\nConnection Failed \n");
	        return -1;
	    }
		ret=mkfifo(fifoName,0666);
		if(ret<0)
		{
			printf("Error in creating named pipe 'mainFIFO' .\n");
			exit(0);
		}
	    isAvailable = true;
   	}
   	else
   	{
   		char process[100];
   		isAvailable = false;
   		kill(lastProcess,SIGUSR2);
   		int wfd = open(fifoName,O_WRONLY);
   		stringstream ss1; string s1;
   		ss1<<myPid; ss1>>s1;
   		printf("Writing my Process ID = %s \n",s1.c_str() );
   		write(wfd,s1.c_str(),BUFFER_LEN);
   		close(wfd);
   		int rfd = open(fifoName,O_RDONLY);
   		read(rfd,process,BUFFER_LEN);
   		printf("Reading  Process ID of nextProcess = %s \n",process );
   		nextProcess = atoi(process);
   		printf("MY PID = %d nextProcess = %d \n",myPid,nextProcess );
   		close(rfd);
   	}
   	while(1)
	    {
	    	while(isAvailable)
	    	{
	    		char r;
	    		printf("Do you want to continue ? \n");
	    		cin>>r;
		    	if(r=='n' || r=='N')
		    	{
		    		printf("Process %d wants to transfer cfd to process %d \n",myPid,nextProcess );
		    			
		    			kill(nextProcess,SIGUSR1);
		    			sleep(5);
		    			int sfd, fds[1];
			        struct sockaddr_un addr;

			        
			        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
			        if (sfd == -1)
			               handle_error("Failed to create socket");
			        printf("Sfd got for UNIX = %d \n",sfd );
			        memset(&addr, 0, sizeof(struct sockaddr_un));
			        addr.sun_family = AF_UNIX;
			        strncpy(addr.sun_path, "/tmp/fd-pass.socket", sizeof(addr.sun_path) );

			        fds[0] = cfd;
			        if (fds[0] < 0)
			                handle_error("Failed to open file 1 reading \n");
			        else
			                fprintf (stdout, "Opened fd %d in parent\n", fds[0]);

			
			        if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
			               handle_error("Failed to connect to socket \n");

			        send_fd (sfd, fds, 1);
			        isAvailable = false;
			        break;

	    		}
	    		printf("Enter a string to be capitalized \n");
	    		scanf("%s",buf);
	    		printf("Client sending : %s \n",buf);
	    		send(cfd,buf,BUFFER_LEN,0);
	    		recv(cfd,buf,BUFFER_LEN,0);
	    		printf("Client received : %s \n",buf );

	    	}
	    	while(!isAvailable);
	    }
    
	return 0;
}