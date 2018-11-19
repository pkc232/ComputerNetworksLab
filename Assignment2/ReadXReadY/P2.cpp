#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
using namespace std;

string pip1 = "/tmp/pip1";
string pip2 = "/tmp/pip2";

int X,Y;

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


void signalHandler(int w){
	sleep(1);
	cout<<"in program 2\n";
	int fd = open(pip2.c_str(),O_RDONLY);
	char arr[100];
	read(fd,arr,100);
	close(fd);

	string s(arr);
	stringstream ss;
	ss<<s;
	ss>>X>>Y;
	printf("%d X %d Y \n",X,Y);
	X = Y+1;

	string ns="";
	ns+=itos(X);
	ns+=" ";
	ns+=itos(Y);
	kill(getppid(),SIGUSR1);
	fd = open(pip1.c_str(),O_WRONLY);

	write(fd,ns.c_str(),100);

	close(fd);

}

int main(){
	mkfifo(pip1.c_str(),0666);
	mkfifo(pip2.c_str(),0666);

	cout<<"Program 2\n";

	signal(SIGUSR2,signalHandler);

	string s="";
	s+="1 0";
	kill(getppid(),SIGUSR1);
	int fd = open(pip1.c_str(),O_WRONLY);
	cout<<"String hai "<<s<<endl;
	write(fd,s.c_str(),100);
	close(fd);
	while(1);

}
