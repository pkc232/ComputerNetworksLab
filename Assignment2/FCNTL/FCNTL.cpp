#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;


int main(int argc, char const *argv[])
{
	FILE* fp =fopen("input.txt","r");
	int fd1 = fileno(fp);
	cout<<"Current FD is "<<fd1endl;

	return 0;
}
