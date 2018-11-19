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
	//printf("################# s2 started #####################\n");
	sleep(10);
	for(int i=0;i<5;i++)
	write(1,"Hello",1024);
	return 0;
}