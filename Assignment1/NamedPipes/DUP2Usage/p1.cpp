#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
	FILE* fp = popen("./p2e","w");
	int fd = fileno(fp);
	char arr[100];
	cin>>arr;
	write(fd,arr,100);
	pclose(fp);
	return 0;
}
