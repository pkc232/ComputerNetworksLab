#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;


string XFIFO="/tmp/FifoX";
string YFIFO="/tmp/FifoY";
int fd;
int x,y;

string itos(int w){
	int i=0;
	string s="";
	while(w){
		s+=(char)(w%10+'0');
		w/=10;
		i++;
	}
	reverse(s.begin(), s.end());
	return s;
}

void writeX(){
	fd = open(XFIFO.c_str(),O_WRONLY);
	string s=itos(x);
	write(fd,s.c_str(),100);
	close(fd);
}

void writeY(){
	fd = open(YFIFO.c_str(),O_WRONLY);
	string s=itos(y);
	write(fd,s.c_str(),100);
	close(fd);
}

void readY(){
	fd = open(YFIFO.c_str(),O_RDONLY);
	char arr[100];
	read(fd,arr,100);
	close(fd);
	y=atoi(arr);
}

void readX(){
	fd = open(XFIFO.c_str(),O_RDONLY);
	char arr[100];
	read(fd,arr,100);
	close(fd);
	x=atoi(arr);
}

void incrY(int w){
	readX();
	cout<<"X read "<<x<<endl;
	y=x+1;
	writeY();
	kill(getppid(),SIGUSR1);
}


int main(int argc, char const *argv[])
{
	cout<<"YahaanY1\n";
	mkfifo(XFIFO.c_str(),0666);
	mkfifo(YFIFO.c_str(),0666);
	signal(SIGUSR2,incrY);
	readX();
	cout<<"Y ne padh liya\n";
	cout<<"YahaanY2\n";
	while(1);



	return 0;
}