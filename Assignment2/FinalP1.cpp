#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;
int fd,eof=1,c;
void func1(int w){
	cout<<"Reading in prog1\n";
	char arr[100];
	for(int i=0;i<2;i++){
		char c;
		if(read(fd,&c,1)==0){
			
			while()
			eof=0;

			// return;
			break;
		}
		cout<<arr;
	}
	kill(c,SIGUSR2);
}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,func1);
	FILE* fp = fopen("input.txt","r");
	fd = fileno(fp);
	dup2(fd,0);
	


	c = fork();
	if(c==0){
		execvp("./fp2",NULL);
	}
	while(eof);
	return 0;
}

