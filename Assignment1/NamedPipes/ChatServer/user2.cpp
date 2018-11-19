#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 

using namespace std;


int main(int argc, char const *argv[]){
	
	int fd;
	char* myfifo = "/tmp/myfifo2";
	int x;
	while(1){
	mkfifo(myfifo,0666);
	fd = open(myfifo,O_RDONLY);
	char arr[100];
	read(fd,arr,100);
	cout<<arr<<endl;
	close(fd);		
	}




}