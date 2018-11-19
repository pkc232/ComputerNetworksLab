#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define pb push_back
 
using namespace std;

void createPipe(){
	
}


int main(){
	int n;
	cout<<"Enter the number of users\n";
	cin>>n;


	int fd;

	char* mainFifo = "/tmp/mainFifo";
	mkfifo(mainFifo,0666);

	std::vector<string> usernames;


	while(n--){
	fd = open(mainFifo,O_RDONLY);
	
	char arr[100];
	read(fd,arr,100);
	string s(arr);
	cout<<"Creating pipe for user "<<s<<endl;
	sleep(1);
	mkfifo(arr,0666);
	usernames.pb(s);
	close(fd);
	}


	while(1){
		fd=open(mainFifo,O_RDONLY);
		char arr[100];

		read(fd,arr,100);

		cout<<"Read msg "<<arr<<endl;
		string temp(arr);
		stringstream ss;

		string username;
		ss<<temp;
		ss>>username;
		for(int i=0;i<usernames.size();i++){
			if(usernames[i]!=username){
				int nfd=open(usernames[i].c_str(),O_WRONLY);
				write(nfd,arr,100);
				close(nfd);
			}
		}
	}
}