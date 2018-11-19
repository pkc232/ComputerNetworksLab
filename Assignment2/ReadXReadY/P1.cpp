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
int childpid;

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
	cout<<"in program 1\n";
	int fd = open(pip1.c_str(),O_RDONLY);

	char arr[100];
	read(fd,arr,100);
	close(fd);

	string s(arr);
	stringstream ss;
	ss<<s;
	ss>>X>>Y;
	printf("%d X %d Y \n",X,Y);
	Y = X+1;

	string ns="";
	ns+=itos(X);
	ns+=" ";
	ns+=itos(Y);

	kill(childpid,SIGUSR2);
	fd = open(pip2.c_str(),O_WRONLY);

	write(fd,ns.c_str(),100);

	close(fd);
	
}

int main(){
	mkfifo(pip1.c_str(),0666);
	mkfifo(pip2.c_str(),0666);

	signal(SIGUSR1,signalHandler);
	cout<<"Program 1 \n";
	 childpid=fork();
	// sleep(5);

	if(childpid>0){
		// int fd = open(pip1.c_str(),O_RDONLY);
		cout<<"Bas\n";
		// close(fd);
		while(1);
	}
	else
	{
		execvp("./p2",NULL);
	}



}
