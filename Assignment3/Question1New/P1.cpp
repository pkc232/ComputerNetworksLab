#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;


string mainPipe = "/tmp/mainPipe";
string pipt1 = "/tmp/pipt1";
string pipt2 = "/tmp/pipt2";

int main(int argc, char const *argv[])
{
	mkfifo(pipt1.c_str(),0666);
	mkfifo(pipt2.c_str(),0666);
	mkfifo(mainPipe.c_str(),0666);

	int fdm = open(mainPipe.c_str(),O_WRONLY|O_NONBLOCK);
	int fdt1 = open(pipt1.c_str(),O_WRONLY|O_NONBLOCK);
	int fdt2 = open(pipt2.c_str(),O_WRONLY|O_NONBLOCK);


	write(fdm,argv[1],100);

	while(1){
		string s;
		getline(cin,s);
		if(s[0]=='1')
		write(fdt1,s.c_str(),100);
		else
		write(fdt2,s.c_str(),100);
	}

	return 0;
}