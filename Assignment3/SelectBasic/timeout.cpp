#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
using namespace std;



int main(int argc, char const *argv[])
{
	int fd;
	char buf[11];
	int ret,sret;

	fd = 0;


	fd_set readfds;
	struct timeval timeout;


	while(1){
		FD_ZERO(&readfds);	
		FD_SET(fd,&readfds);

		timeout.tv_sec=5;
		timeout.tv_usec = 0;

		sret = select(8,&readfds,NULL,NULL,&timeout);

		if(sret==0)
		{
			cout<<"Time out "<<sret<<endl;
		}
		else
		{
			memset((void*)buf,0,11);

			ret = read(fd,(void*)(buf),10);
			cout<<"ret "<<ret<<endl;
			if(ret!=-1){
				cout<<"Buffer : "<<buf<<endl;
			}

		}


	}
	

	return 0;
}