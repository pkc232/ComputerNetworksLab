#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;
// sem_t doneReading;

int main(int argc, char const *argv[])
{
	
	// sem_init(&doneReading,0,0);

	int file_desc = open("inputFile.txt",O_RDONLY);
	char s[100];
	int c = fork();
	char* fp[]={"./frd2",NULL};


	if(c>0){
		int cnt=5;
		while(cnt--){
		char ch=' ';
		while(ch!='\n'){
		read(file_desc,&ch,1);
		printf("%c", ch);
		}
		// printf("\n");
		}
		dup2(0,file_desc);
		dup2(1,file_desc);
		// sem_post(&doneReading);

	}
	else
	{
		// sem_wait(&doneReading);
		printf("in child now\n");
		execvp(fp[0],fp);
	}

	return 0;
}