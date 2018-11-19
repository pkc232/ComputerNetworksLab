#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;
int fd,eof=1;
void func2(int w){
	cout<<"Reading in prog2\n";
	char arr[100];
	for(int i=0;i<2;i++){
		if(read(fd,arr,19)==0){
			eof=0;
			// return;
			break;
		}
		cout<<arr;
	}
	kill(getppid(),SIGUSR1);
}

int main(int argc, char const *argv[])
{
	// FILE* fp = fopen("input.txt","r");
	// int fd = fileno(fp);
	// dup2(fd,0);
	signal(SIGUSR2,func2);
	dup2(0,fd);
	kill(getppid(),SIGUSR1);
	while(eof);
	return 0;
}