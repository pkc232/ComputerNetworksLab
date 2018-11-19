#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void p2c(int w){
	cout<<"Received from parent\n";
}

void c2p(int w){
	cout<<"Received from child\n";
}

void breakThis(int w){
	cout<<"We wont break so easily "<<w<<endl;
}

int main(){
	pid_t t= fork();

	if(t>0){
		signal(SIGINT,c2p);
		while(1)
			kill(t,SIGINT);
	}		
	else
	{
		signal(SIGINT,p2c);
		while(1)
			kill(getppid(),SIGINT);
	}
	
	// signal(SIGINT,breakThis);
	// while(1);
}