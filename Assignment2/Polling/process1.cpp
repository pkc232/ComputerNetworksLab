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