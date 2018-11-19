#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#define noOfFD 3
using namespace std;



string pipS5 = "/tmp/pips5";



int main(int argc, char const *argv[])
{
	mkfifo(pipS5.c_str(),0666);

	int fd = open(pipS5.c_str(),O_RDONLY);

	char arr[100];
	read(fd,arr,100);

	string temp(arr);
	stringstream ss;
	ss<<temp;
	string pid,pipeName;
	ss>>pid>>pipeName;

	cout<<temp<<endl;
	return 0;
}