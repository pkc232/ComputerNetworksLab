#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;

string pipt1 = "/tmp/pipt1";
string pipt2 = "/tmp/pipt2";
string mainPipe = "/tmp/mainPipe";

set<int> registered;
char buf[100];

void s1(int pid){
	cout<<"Service 1 is given to Client "<<pid<<endl;
}

void s2(int pid){
	cout<<"Service 2 is given to "<<pid<<endl;
}

void s3(int pid){
	cout<<"Service 3 is given to "<<pid<<endl;
}



int main(int argc, char const *argv[])
{
	mkfifo(pipt1.c_str(),0666);
	mkfifo(pipt2.c_str(),0666);
	mkfifo(mainPipe.c_str(),0666);
	
	int fd[3];

	fd[0]	=	open(mainPipe.c_str(),O_RDONLY|O_NONBLOCK);
	fd[1]	=	open(pipt1.c_str(),O_RDONLY|O_NONBLOCK);
	// fd[2]	=	open(pipt1.c_str(),O_RDONLY|O_NONBLOCK);

	fd_set readfds;
	struct timeval timeout;
	int ret,sret;


	while(1){
		FD_ZERO(&readfds);	
		memset((void*)buf,0,100);

		for(int i=0;i<2;i++)
		FD_SET(fd[i],&readfds);

		timeout.tv_sec=5;
		timeout.tv_usec = 0;

		sret = select(max(fd[0],fd[1])+1,&readfds,NULL,NULL,&timeout);

		if(sret==0)
		{
			cout<<"Time out "<<sret<<endl;
			// bufr = "Time out\n";

		}

		else
		{
			

			for(int i=1;i<2;i++)
			{

			if(FD_ISSET(fd[i],&readfds)==0)
				continue;
			ret = read(fd[i],(void*)(buf),4);
			// bufr = buf;
			cout<<"ret "<<ret<<endl;
			if(ret!=-1){
				cout<<"Buffer : "<<buf<<endl;
			}
			// sleep(2);
			}

		}
		// sleep(2);

	}






	return 0;
}