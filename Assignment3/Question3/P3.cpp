#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;

string sendpid = "/tmp/pidd";



int main(int argc, char const *argv[])
{
	
	mkfifo(sendpid.c_str(),0666);
	char buf[100];
	sleep(2);
	int fd = open(sendpid.c_str(),O_RDONLY);
	read(fd,buf,100);


	int pid = atoi(buf);
	cout<<pid<<endl;

	while(1){
			sleep(3);
			kill(pid,SIGUSR1);
	}

	return 0;
}