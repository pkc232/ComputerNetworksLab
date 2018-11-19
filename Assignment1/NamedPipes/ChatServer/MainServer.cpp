#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 

using namespace std;

int main(int argc, char const *argv[])
{
	int fd1,fd2,fd3,fd4;

	char* myfifo1 = "/tmp/myfifo1";
	char* myfifo2 = "/tmp/myfifo2";
	char* myfifo3 = "/tmp/myfifo3";
	char* myfifo4 = "/tmp/myfifo4";

	mkfifo(myfifo1,0666);
	mkfifo(myfifo2,0666);
	mkfifo(myfifo3,0666);
	mkfifo(myfifo4,0666);



	while(1){
	fd1 = open(myfifo1,O_RDONLY);
	int p;
	char arr1[100];
	read(fd1,arr1,100);
	close(fd1);


	fd2 = open(myfifo2,O_WRONLY);
	write(fd2,arr1,100);
	close(fd2);


	fd3 = open(myfifo3,O_WRONLY);
	write(fd3,arr1,100);
	close(fd3);


	fd4 = open(myfifo4,O_WRONLY);
	write(fd4,arr1,100);
	close(fd4);
	}

	return 0;
}