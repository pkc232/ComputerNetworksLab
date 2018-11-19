#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;


int main(int argc, char const *argv[])
{
	int pfd[2];
	int c;
	
	char s[100];
	cin>>s;


	pipe(pfd);

	c=fork();

	if(c>0){
		close(pfd[0]);
		write(pfd[1],s,strlen(s));
		cout<<"Wrote in parent "<<s<<endl;
	}
	else
	{
		close(pfd[1]);
		char s2[100];
		read(pfd[0],s2,strlen(s));
		cout<<"Reading in child "<<s2<<endl;
	}
}