#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h> 

using namespace std;
string toBesent;
void* readBuffer(void* args){
	char* fifo = (char*)(args);
	
	while(1){
	int fd = open(fifo,O_RDONLY);

	char arr[100];

	read(fd,arr,100);

	printf("%s\n",arr);
		
	}
}

void* writeMessage(void* args){
	char* fifo = (char*)args;

	while(1){
		int fd = open(fifo,O_WRONLY);
		char arr[100];
		cin>>arr;
		string temp(arr);
		string nw=toBesent;
		nw+=" ";
		nw+=arr;
		write(fd,nw.c_str(),100);
	}
}


int main(int argc, char const *argv[]){

	string s=""; 
	int fd;
	char* mainFifo = "/tmp/mainFifo";
	mkfifo(mainFifo,0666);

	cout<<"Enter the name of your pipe\n";
	cin>>s;

	string fifname="/tmp/";
	fifname+=s;

	toBesent=fifname;

	fd = open(mainFifo,O_WRONLY);


	write(fd,fifname.c_str(),100);

	close(fd);

	const char* myfifo = fifname.c_str();
	mkfifo(myfifo,0666);

	pthread_t reader,writer;
	pthread_create(&reader,NULL,readBuffer,(void*)(myfifo));
	pthread_create(&writer,NULL,writeMessage,(void*)(mainFifo));

	pthread_join(reader,NULL);
	pthread_join(writer,NULL);
}