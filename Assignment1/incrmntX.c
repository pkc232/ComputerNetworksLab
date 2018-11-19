#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXSIZE 27

int main(int argc, char const *argv[])
{
	char c;
	int shmid;
	key_t key;
	char *shm,*s;

	key=1234;

	if((shmid=shmget(key,MAXSIZE,IPC_CREAT|0666))<0)
	{
		printf("shmget error\n");
		return 0;
	}
	if()

	return 0;
}