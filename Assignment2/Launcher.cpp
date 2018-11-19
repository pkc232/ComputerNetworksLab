#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;


int main(int argc, char const *argv[])
{
	FILE* fp = fopen("input.txt","r");
	int fd = fileno(fp);

	dup2(fd,0);
	while(1);

	// int c=fork();
	// if(c>0)
	// {
	// 	int w= fork();
	// 	if(w==0)
	// 		execvp("./p1",NULL);
	// }
	// else
	// 	execvp("./p2",NULL);

	return 0;
}