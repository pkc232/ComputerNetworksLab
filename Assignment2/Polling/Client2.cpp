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
	char pipeName[]="/tmp/pipe2";
	int fd = open(pipeName,O_WRONLY);

	int i=0;
	cout<<"INside client 2\n";
	char buffer[100]="Inside client 2 buffer ";
	while(i++<2){
		cout<<"Hello 2\n";
		write(fd,buffer,100);
		sleep(1);
	}
	close(fd);
	return 0;
}