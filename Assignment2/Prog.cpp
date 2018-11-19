#include <bits/stdc++.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
using namespace std;
ifstream fin;
int childpid,parentpid;
void parFunc(int w){
	cout<<"In parent function\n";
	string s;
	for(int i=0;i<2;i++){
		if(cin.eof())
			return;
		getline(cin,s);
		cout<<s<<endl;
	}
	
	// while(1);
}

void childFunc(int w){
	cout<<"In child function\n";
	string s;
	for(int i=0;i<2;i++){
		if(cin.eof())
			return;
		getline(cin,s);
		cout<<s<<endl;
	}
	
	// while(1);
}


int main(int argc, char const *argv[])
{
	FILE* fp = fopen("input.txt","r");
	int fd= fileno(fp);
	dup2(fd,0);
	signal(SIGUSR1,parFunc);
	signal(SIGUSR2,childFunc);
	parentpid=getpid();
	childpid=fork();
	if(childpid>0)
	{
		while(1){
			kill(parentpid,SIGUSR1);
			for(int i=1;i<=1000000000;i++);
		}
		// while(1);
	}
	else
		{
			while(1){
				kill(childpid,SIGUSR2);
				for(int i=1;i<=1000000000;i++);
			}
		}
	// else
	// {
	// 	childFunc(1);
	// }
	// wait(NULL);
	// // while(1);
	return 0;
}