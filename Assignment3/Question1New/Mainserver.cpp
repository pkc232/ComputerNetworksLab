#include <bits/stdc++.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#define noOfFD 3
using namespace std;



string mainPipe = "/tmp/mainPipe";
string pipt1 = "/tmp/pipt1";
string pipt2 = "/tmp/pipt2";


string pipS5 = "/tmp/pips5";
char bufID[100],bufST1[100],bufST2[100];

set<int> registered;
string bufr;


string itos(int w){
	int i=0;
	string s="";
	while(w){
		s+=(char)(w%10+'0');
		w/=10;
		i++;
	}
	reverse(s.begin(), s.end());
	return s;
}

void service1(int pid){
	cout<<"Service 1 given to "<<pid<<endl;
}

void service2(int pid){
	cout<<"Service 2 given to "<<pid<<endl;
}

void service3(int pid){
	cout<<"Service 3 given to "<<pid<<endl;
}

void service5(int pid){
	string msg="";
	string pidd = itos(pid);
	string pipeName = "/tmp/Pipe";
	pipeName+=pidd;
	
	msg+=pidd;
	msg+=" ";
	msg+=pipeName;
	mkfifo(pipeName.c_str(),0666);
	int fd = open(pipS5.c_str(),O_WRONLY);
	write(fd,msg.c_str(),100);

}


int main(int argc, char const *argv[])
{
	mkfifo(pipt1.c_str(),0666);
	mkfifo(pipt2.c_str(),0666);
	mkfifo(mainPipe.c_str(),0666);
	mkfifo(pipS5.c_str(),0666);


	int fdm = open(mainPipe.c_str(),O_RDONLY|O_NONBLOCK);
	int fdt1 = open(pipt1.c_str(),O_RDONLY|O_NONBLOCK);
	int fdt2 = open(pipt2.c_str(),O_RDONLY|O_NONBLOCK);


	fd_set readfds;
	struct timeval timeout;
	int ret,sret;


	while(1){
		FD_ZERO(&readfds);	
		memset((void*)bufID,0,100);
		memset((void*)bufST1,0,100);
		memset((void*)bufST2,0,100);

		FD_SET(fdm,&readfds);
		FD_SET(fdt1,&readfds);
		FD_SET(fdt2,&readfds);

		timeout.tv_sec=5;
		timeout.tv_usec = 0;

		sret = select(max(fdm,max(fdt1,fdt2))+1,&readfds,NULL,NULL,&timeout);
		cout<<sret<<endl;

		if(sret==0)
		{
			cout<<"Time out "<<sret<<endl;
			bufr = "Time out\n";
		}
		else
		{
			if(FD_ISSET(fdm,&readfds)){
				ret = read(fdm,bufID,100);
				cout<<"ret "<<ret<<endl;
				if(ret>0){
				cout<<"Buffer : "<<bufID<<endl;
				int num = atoi(bufID);
				registered.insert(num);				
				}
			}
			if(FD_ISSET(fdt1,&readfds))
			{
				ret = read(fdt1,bufST1,100);
				string s(bufST1);
				stringstream ss;
				ss<<s;
				int type,pid,sid;
				ss>>type>>pid>>sid;

				if(registered.find(pid)==registered.end())
				{
					cout<<"Wrong Process ID Not registered\n";
					continue;
				}
				switch(sid){
					case 1 : {service1(pid);break;}
					case 2 : {service2(pid);break;}
					case 3 : {service3(pid);break;}
					default : {cout<<"Wrong service requested\n";}
				}
			}

			if(FD_ISSET(fdt2,&readfds)){
				ret = read(fdt2,bufST2,100);
				string s(bufST2);
				stringstream ss;
				ss<<s;
				int type,pid,sid;
				ss>>type>>pid>>sid;

				if(registered.find(pid)==registered.end())
				{
					cout<<"Wrong Process ID Not registered\n";
					continue;
				}
				switch(sid){
					case 5 : {service5(pid);break;}
					default : {cout<<"Wrong service requested\n";}
				}
			}	
		}	
	}


	return 0;
}


