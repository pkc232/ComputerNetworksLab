#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


int main(int argc, char const *argv[])
{

	int fd =  open("normFile.txt", O_WRONLY);


	//write(fd,"\nIs it writing this?\n",100);

	close(fd);

	fd = open("normFile.txt",O_RDONLY);

	int cnt=10;
	char ch;

	int fd2 = open("testFile.txt",O_WRONLY);
	dup2(1,fd2);

	while(cnt--){
		read(fd,&ch,1);
		printf("%c",ch);
	}
	close(fd);


	return 0;
}
