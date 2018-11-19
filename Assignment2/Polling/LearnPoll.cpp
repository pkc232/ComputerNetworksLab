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
	string pipeNames[]={"/tmp/pipe1","/tmp/pipe2","/tmp/pipe3"};
	
	for(int i=0;i<3;i++)
	mkfifo(pipeNames[i].c_str(),0666);

	struct pollfd pfd[3];

	for(int i=0;i<3;i++){
		pfd[i].fd=open(pipeNames[i].c_str(),O_RDONLY);
		pfd[i].events=0;
		pfd[i].events|=POLLIN;
	}

	int timeout=3000;
	while(1){
		for(int i=0;i<3;i++){
		// pfd[i].fd=open(pipeNames[i].c_str(),O_RDONLY);
		pfd[i].events=0;
		pfd[i].events|=POLLIN;
	}
		int x = poll(pfd,3,-1);
		cout<<"X hai "<<x<<endl;
		for(int i=0;i<3;i++){
			if(pfd[i].revents & POLLIN){
				cout<<" program "<<i<<" chala\n";
			}
			else
			{
				cout<<" program "<<i<<" nhi chala\n";	
			}
		}
		sleep(1); 
	}
	for(int i=0;i<3;i++)
	{
		close(pfd[i].fd);	
	}




	return 0;
}