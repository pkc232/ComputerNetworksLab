#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int main(int argc, char const *argv[])
{

	printf("ENterd the second read\n");
	int file_desc = open("inputFile.txt",O_RDONLY);
	
	dup2(file_desc,0);
	dup2(file_desc,1);
	char s[100];
	int cnt=2;
	while(cnt--){
	char ch=' ';
	int p=0;
	while(ch!='\n'&&(p++)<3){
	read(file_desc,&ch,1);
	printf("%c", ch);
	}
	// printf("\n");
	}	
	return 0;
}