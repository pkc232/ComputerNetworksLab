#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;


int main(int argc, char const *argv[])
{
	cout<<"In the second prog\n";
	char ch='a';
	int cnt=0;
	while(cnt<2){
	if(scanf("%c",&ch)<0)
		return 0;
	printf("%c",ch);
	if(ch=='\n'){
		cnt++;
	}
	}

	int c = fork();

	if(c==0){
		execvp("./p1e",NULL);
	}


	return 0;
}