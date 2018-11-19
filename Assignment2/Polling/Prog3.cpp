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


int main(){
	mkfifo("/tmp/pipe3",0666);
	int fd=open("/tmp/pipe3",O_WRONLY);

	char arr[100];
	cin>>arr;

	write(fd,arr,100);
	
		
}
