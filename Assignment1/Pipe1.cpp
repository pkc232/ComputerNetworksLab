#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;


int main(int argc, char const *argv[])
{
	int pfd[2];
	pipe(pfd);

	char s[100];
	char s2[100];
	cout<<"Enter the string\n";
	cin>>s;

	write(pfd[1],s,strlen(s));
	read(pfd[0],s2,strlen(s)-2);

	cout<<s2<<endl;

	return 0;
}