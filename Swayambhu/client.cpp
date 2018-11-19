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
string serv_ip = "127.0.0.1";
int serv_ports[] = {5031, 5042, 5053};

int main() {
	// printf("Enter client ID: \n");
	// string cname;
	// cin>>cname;
	
	int serv_no;
	printf("Enter service required(1, 2, 3): \n");
	scanf("%d", &serv_no);
	if (serv_no != 1 and serv_no != 2 and serv_no != 3) {
		printf("Invalid service!\n");
		exit(-1);
	}

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no = serv_ports[serv_no - 1];

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket Failed!");
		exit(-1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(serv_ip.c_str());
	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) <0) {
		perror("Connect Failed!");
		exit(-1);
	}

	int x, y;
	printf("Enter the values(x, y):\n");
	scanf("%d %d", &x, &y);
	string sx = to_string(x);
	string sy = to_string(y);
	sx += " ";
	sx += sy;
	if (send(sfd, sx.c_str(), 1024, 0) == -1) {
		perror("Write Failed!");
		exit(-1);
	}

	char buf[1024];
	if (recv(sfd, buf, 1024, 0) == -1) {
		perror("Recv Failed!");
		exit(-1);
	}
	printf("%s\n", buf);
	return 0;

}