#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main(int argc, char const *argv[])
{
	cout<<"The main program\n";
	FILE* fp = fopen("input.txt","r");
	int fd = fileno(fp);
	dup2(fd,0);

	int c= fork();

	if(c==0){
		execvp("./p1e",NULL);
	}		
	wait(NULL);
	return 0;
}