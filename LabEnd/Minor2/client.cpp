#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;



int main(int argc, char const *argv[])
{
		int rsfd=socket(AF_INET,SOCK_RAW,50);
  	char buff[1024];
  	memset(buff,0,sizeof(buff));
  	struct sockaddr_in cli_addr;
  	socklen_t size=sizeof(cli_addr); 

 // while(1)
  	{
    char buff[1024];
  	memset(buff,0,sizeof(buff));
  	struct sockaddr_in cli_addr;
  	socklen_t size =sizeof(cli_addr);
  	// recvfrom(rsfd,buff,1024,0,(sockaddr*)&cli_addr,&size);
  	while(1){
  		cout<<"Waiting to read\n";
  	  	read(rsfd,buff,1024); 
  	  	cout<<"done receiving "<<endl;
  	    struct iphdr *ip;
  	    ip=(struct iphdr*)buff;
  	    // print_ip(ip);
  	    cout<<(buff+(ip->ihl)*4)<<endl;
  	    cout<<buff<<endl;
  	} 
  }
	return 0;
}