#include <bits/stdc++.h>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pcap.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

using namespace std;
#define PORT 5042

string serv_ip = "127.0.0.1";

int main(int argc, char const *argv[]) {
	if (argc > 1) {
		char buf[1024];
		int nsfd = atoi(argv[1]);
		if (recv(nsfd, buf, 1024, 0) == -1) {
			perror("Read failed!");
			exit(-1);
		}
		string msg(buf);
		int x, y;
		stringstream ss;
		ss<<msg; ss>>x; ss>>y;
		x = x-y;
		string tmp = to_string(x);
		
		printf("Sending data: %s\n", tmp.c_str());
		if (send(nsfd, tmp.c_str(), 1024, 0) == -1) {
			perror("Write failed!");
			exit(-1);
		}
		return 0;
	}


	int sfd, nsfd;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t cli_len = (socklen_t)sizeof(cli_addr);

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket Failed!");
		exit(-1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(serv_ip.c_str());

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}
	
	if (bind(sfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("Bind Failed!");
		exit(-1);
	}
	if (listen(sfd,10) == -1) {
		perror("Listen Failed!");
		exit(-1);
	}
	if ((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len)) == -1) {
		perror("Accept Failed!");
		exit(-1);
	}

	char buf[1024];
	if (recv(nsfd, buf, 1024, 0) == -1) {
		perror("Recv failed!");
		exit(-1);
	}
	string msg(buf);
	int x, y;
	stringstream ss;
	ss<<msg; ss>>x; ss>>y;
	x = x-y;
	string tmp = to_string(x);
	
	printf("Sending data: %s\n", tmp.c_str());
	if (send(nsfd, tmp.c_str(), 1024, 0) == -1) {
		perror("send failed!");
		exit(-1);
	}

	return 0;
}