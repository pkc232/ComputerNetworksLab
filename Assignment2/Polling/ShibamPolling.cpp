#include <bits/stdc++.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <cstdlib>
#include <unistd.h>
#include <poll.h>
#include <pthread.h>
using namespace std;

int main(int argc, char const *argv[])
{
	string process[]={"./p1","./p2","./p3"};
	string pipeNames[]={"/tmp/pipe1","/tmp/pipe2","/tmp/pipe3"};
	struct pollfd pfd[3];

	for(int i=0;i<3;i++)
	{
		mkfifo(pipeNames[i].c_str(),0666);
		int c=fork();
		if(c>0)
		{
			pfd[i].fd = open(pipeNames[i].c_str(),O_RDONLY);
			pfd[i].events = 0;
			pfd[i].events |= POLLIN;
			//close(pfd[i].fd);

		}
		else if(c==0)
		{
			cout<<"Child "<<i<<" created and performing exec "<<endl;
			execvp(process[i].c_str(),NULL);
		}
	}
	int timeout = 3000,completed=0;
	while(1).
		
	{
		char buffer[100];
		for(int i=0;i<3;i++) {  pfd[i].events = POLLIN;}
		poll(pfd,3,timeout);
		for(int i=0;i<3;i++)
		{
			if(pfd[i].revents & POLLIN)
			{
				int readCount = read(pfd[i].fd,buffer,100);
				if(readCount>0)
				{
					string s(buffer);
					cout<<"Process "<<process[i]<<" sent data "<<s<<endl;
					break;
				}
				
			}
			
		}
	}
	for(int i=0;i<3;i++)
	{
		close(pfd[i].fd);	
	}

	cout<<"Ending server "<<endl;
	return 0;
}