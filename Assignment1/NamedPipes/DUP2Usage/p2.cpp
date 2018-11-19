#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main(int argc, char const *argv[])
{
	char x[100];
	cin>>x;
	strcat(x,"2");
	FILE* fp = popen("./p3e","w");
	int fd = fileno(fp);
	write(fd,x,100);
	pclose(fp);

	return 0;
}