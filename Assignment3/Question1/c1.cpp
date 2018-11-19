#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;


string pipt1 = "/tmp/pipt1";
string pipt2 = "/tmp/pipt2";
string mainPipe = "/tmp/mainPipe";


int main(int argc, char const *argv[])
{
	/* code */
	mkfifo(pipt1.c_str(),0666);
	mkfifo(pipt2.c_str(),0666);
	mkfifo(mainPipe.c_str(),0666);

	int fd = open(mainPipe.c_str(),O_WRONLY|O_NONBLOCK);
	char arr[100] = "c1";
	write(fd,arr,100);
	close(fd);
	string s;
	while(1){
		fd = open(pipt1.c_str(),O_WRONLY|O_NONBLOCK);
		cin>>s;
		write(fd,s.c_str(),100);
		close(fd);
	}

	return 0;
}