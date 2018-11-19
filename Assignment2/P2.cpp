#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;
int pid;
int fd;
string readingFifo="/tmp/Fifo2";
string writingFifo="/tmp/Fifo1";
void readFIFO(){
	fd = open(readingFifo.c_str(),O_RDONLY);
	char arr[100];
	read(fd,arr,100);
	pid = atoi(arr);
	cout<<pid<<endl;
	close(fd);
}

void writeFIFO(){
	fd = open(writingFifo.c_str(),O_RDONLY);
	string s="";
	int w= getpid();
	int i=0;
	while(w){
		s+=(char)((w%10)+'0');
		w/=10;
		i++;
	}
	reverse(s.begin(), s.end());
	write(fd,s.c_str(),100);
	close(fd);
}
void readLines(int w){
	cout<<"in prog 2 \n";
	char ch='a';
	int cnt=0;
	while(cnt<2){
	if(scanf("%c",&ch)<0)
		return;
	printf("%c",ch);
	if(ch=='\n')
		cnt++;
	}
	readFIFO();
	kill(pid,SIGUSR1);
	writeFIFO();
}




int main(int argc, char const *argv[])
{

	mkfifo(readingFifo.c_str(),0666);
	mkfifo(writingFifo.c_str(),0666);
	writeFIFO();
	signal(SIGUSR2,readLines);
	// writeFIFO();
	readLines(1);
	while(1);
	return 0;
}