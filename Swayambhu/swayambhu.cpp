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
#include <sys/wait.h>

using namespace std;
#define PORT 8055
int tsfd;
struct sockaddr_in tr_addr;
socklen_t addrlen;
fd_set readfds;
std::vector<int> ports, servfd;
std::vector<struct sockaddr_in> addrs;
std::vector<string> process;

void *acceptPorts(void *data) {
	char newport[1024];
	ports.clear(), servfd.clear();
	while (true) {
		printf("=========>>> Swayambhu Worker Thread...\n");
		if (recv(tsfd, newport, 1024, 0) == -1) {
			perror("read failed");
			continue;
		}
		printf("Port received from Tracer: %s\n", newport);
		int pt = atoi(newport);
		sleep(2);
		if (pt > 1024 and pt < 9999) {
			int ret;
			printf("Swayambhu binding to new port...\n");
			int fd = socket(AF_INET, SOCK_STREAM, 0);
			struct sockaddr_in taddr;
			taddr.sin_family = AF_INET;
			taddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			taddr.sin_port = htons(pt);
			
			string serv = "./s";
			int id = pt%10;
			string sid = to_string(id);
			serv += sid;

			int value = 1;
			printf("Process name for port %d : %s\n", pt, serv.c_str());

			if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
				perror("setsockopt failed");
			}
			if (bind(fd, (struct sockaddr*)&taddr, (socklen_t)sizeof(taddr)) == -1) {
				perror("Bind failed");
				exit(-1);
			}

			printf("Swayambhu bound to port: %d\n", pt);
			ports.push_back(pt);
			servfd.push_back(fd);
			process.push_back(serv);
			addrs.push_back(taddr);
		}
	}
}

int main() {
	printf("========>>> Swayambhu Initializing...\n");
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	tr_addr.sin_family = AF_INET;
	tr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	tr_addr.sin_port = htons(PORT);
	if (bind(sfd, (struct sockaddr*)&tr_addr, (socklen_t)sizeof(tr_addr)) == -1) {
		perror("bind failed");
		exit(-1);
	}
	if (listen(sfd, 10) == -1) {
		perror("Listen failed");
		exit(-1);
	}
	if ((tsfd = accept(sfd, (struct sockaddr*)&tr_addr, &addrlen)) == -1) {
		perror("accept failed");
		exit(-1);
	}

	pthread_t worker;
	pthread_create(&worker, NULL, acceptPorts, NULL);
	
	struct timeval timeout;
	while (true) {
		FD_ZERO(&readfds);
		int size = servfd.size();
		if (size > 0) {
			printf("Number of ports = %d\n", size);
			for (int i = 0; i < size; i++) {
				if (listen(servfd[i], 50) == -1) {
					perror("listen failed");
					exit(-1);
				}
				FD_SET(servfd[i], &readfds);
			}
			printf("-------------->>> Swayambhu listening...\n");
			timeout.tv_sec = 10; timeout.tv_usec = 0;
			int _max = INT_MIN;
			for (int i = 0; i < size; i++)
				_max = max(_max, servfd[i]);
			_max++;
			int sret = select(_max, &readfds, NULL, NULL, &timeout);
			if (sret == 0)
				printf("Timeout\n");
			else {
				for (int i = 0; i < size; i++) {
					if (FD_ISSET(servfd[i], &readfds)) {
						printf("Incoming request on PORT: %d\n", ports[i]);
						struct sockaddr_in newaddr;
						socklen_t addrlen = sizeof newaddr;
						int nsfd; 
						if ((nsfd = accept(servfd[i], (struct sockaddr*)&newaddr, &addrlen)) == -1) {
							perror("accept failed");
							exit(-1);
						}
						printf("nsfd = %d\n",nsfd );
						printf("Connected to client at %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));

						string snfsd ; stringstream ss; ss<<nsfd; ss>>snfsd;
						char proc[10];	strcpy(proc, process[i].c_str());
						char nsf[10]; 	strcpy(nsf, snfsd.c_str());
						printf("In swayambhu int=%d: str=%s\n", nsfd, nsf);
						char *ars[] = {proc, nsf, NULL};
						int cpid = fork();
						if (cpid == 0)
							execvp(ars[0], ars);
					}
				}
			}
		}
	}
	return 0;
}