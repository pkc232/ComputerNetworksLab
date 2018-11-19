#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
int fd;
bool finish=false;
void SingnalHandlerptoc(int signo)
{
	cout<<getpid()<<" reads\n";
	cout<<"Recieved from parent\n";
	//signal(SIGUSR1,SingnalHandlerptoc);
	char msg[100];
	if(read(fd,msg,8)==0)
		{	
			finish=true;
			return;
		}
	cout<<msg<<endl;
}
void SingnalHandlerctop(int signo)
{
	cout<<getpid()<<" reads\n";
	cout<<"Recieved from child\n";
	//signal(SIGUSR2,SingnalHandlerctop);
	char msg[100];
	if(read(fd,msg,8)==0)
		{	
			finish=true;
			return;
		}
	cout<<msg<<endl;
}
int main()
{
	int c;
	fd=open("input.txt",O_RDONLY);
	signal(SIGUSR1,SingnalHandlerctop);
	signal(SIGUSR2,SingnalHandlerptoc);
	dup2(fd,0);
	c=fork();
	if(c==0)
	{
		while(!finish)
			 {
			 	kill(getppid(),SIGUSR1);
			 	for(int i=1;i<=1000000000;i++);
			 }
	}
	else
	{
		while(!finish)
			{	kill(c,SIGUSR2);
				for(int i=1;i<=1000000000;i++);
			}
	}
	return 0;
}