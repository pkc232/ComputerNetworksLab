#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;


int main(int argc, char const *argv[])
{
	int c=0;
	cout<<"Statement 1\n";

	char* fp[]={"g++ Dwaala.cpp",NULL};

	c= fork();

	if(c>0){
		cout<<"Statement 2\n";
		wait();
		cout<<"Statement 4\n";
	}
	else
	{
		cout<<"This is statement 3\n";
		execvp(fp[0],fp);
	}
	return 0;
}


