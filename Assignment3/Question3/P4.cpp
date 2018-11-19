#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
using namespace std;


string pip = "/tmp/pip";


int main(int argc, char const *argv[])
{
	while(1){

	string s;
	cin>>s;
	int fd = open(pip.c_str(),O_RDONLY);
	char buf[100];
	read(fd,buf,100);
	cout<<"In P4 "<<buf<<endl;
	close(fd);		
	}
	return 0;
}

