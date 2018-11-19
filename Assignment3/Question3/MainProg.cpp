#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#define noOfFD 1
using namespace std;


string pip = "/tmp/pip";
string sendpid = "/tmp/pidd";


char buf[100];
string bufr;


string itos(int w){
	int i=0;
	string s="";
	while(w){
		s+=(char)(w%10+'0');
		w/=10;
		i++;
	}
	reverse(s.begin(), s.end());
	return s;
}


void signalHandler(int w){
	int fd = open(pip.c_str(),O_WRONLY);
	write(fd,bufr.c_str(),100);
	close(fd);
}


int main(int argc, char const *argv[])
{

	mkfifo(pip.c_str(),0666);
	mkfifo(sendpid.c_str(),0666);

	int curpid = getpid();
	cout<<"Curpid "<<curpid<<endl;
	string curp = itos(curpid);

	int tfd = open(sendpid.c_str(),O_WRONLY);
	write(tfd,curp.c_str(),100);
	close(tfd);

	signal(SIGUSR1,signalHandler);

	int fd[3];
	
	
	fd[0] = 0;
	fd[1]=open("input.txt",O_RDONLY);
	fd[2]= open("input2.txt",O_RDONLY);
	
	int ret,sret;

	int stdfd=0;
	fd_set readfds;
	struct timeval timeout;

	while(1){
		FD_ZERO(&readfds);	
		memset((void*)buf,0,100);

		for(int i=0;i<noOfFD;i++)
		FD_SET(fd[i],&readfds);

		timeout.tv_sec=5;
		timeout.tv_usec = 0;

		sret = select(8,&readfds,NULL,NULL,&timeout);

		if(sret==0)
		{
			cout<<"Time out "<<sret<<endl;
			bufr = "Time out\n";

		}
		else
		{
			

			for(int i=0;i<noOfFD;i++)
			{

			if(FD_ISSET(fd[i],&readfds)==0)
				continue;	
			ret = read(fd[i],(void*)(buf),4);
			bufr = buf;
			cout<<"ret "<<ret<<endl;
			if(ret!=-1){
				cout<<"Buffer : "<<buf<<endl;
			}
			sleep(2);
			}

		}
		sleep(2);


	}
	

	return 0;
}