#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int fd,eof,c;

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