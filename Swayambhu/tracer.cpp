#include <pcap.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <bits/stdc++.h> //sabka baap 
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

using namespace std;
#define PORT 8055
int cfd;
struct sockaddr_in saddr, source, dest;
bool traced[10000];

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) {
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	int iphdrlen = 4*iph->ihl;
	struct tcphdr *tcph = (struct tcphdr*)(buffer+sizeof(struct ethhdr)+iphdrlen);
	memset(&source, 0, sizeof(source)); source.sin_addr.s_addr = iph->saddr; source.sin_port = tcph->source; 
	memset(&dest, 0, sizeof(dest)); dest.sin_addr.s_addr = iph->daddr; dest.sin_port = tcph->dest;

	printf("Source %s:%d\n", inet_ntoa(source.sin_addr), ntohs(source.sin_port));
	printf("Destination %s:%d\n", inet_ntoa(dest.sin_addr), ntohs(dest.sin_port));
	int port = ntohs(dest.sin_port);
	cout<<port<<endl;
	if (port > 1024 and port < 9999 and !traced[port] and port != 8055) {
		string sport = to_string(port);
		printf("Tracer sending port %s to Swayambhu\n", sport.c_str());
		if (send(cfd, sport.c_str(), 1024, 0) == -1) {
			perror("send failed");
			exit(-1);
		}
		traced[port] = true;
	}
}


int main() {
	printf("======>>> Tracer initiating...\n");
	memset(traced, false, sizeof traced);
	char errbuf[PCAP_ERRBUF_SIZE];
	char device[] = "lo";
	char protocol[] = "tcp";
	pcap_t *handle;
	struct bpf_program fp;		/*To hold compiled program*/
	bpf_u_int32 pMask, pNet;	/*Subnet Mask and IP Address*/

	if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket failed");
		exit(-1);
	}
	socklen_t slen = sizeof saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(PORT);

	if (connect(cfd, (struct sockaddr *)&saddr, slen) == -1) {
		perror("Connect failed");
		exit(-1);
	}
	printf("Tracer->Swayambhu connection established.\n");

	int promiscous_mode = 0;
	pcap_lookupnet(device, &pNet, &pMask, errbuf);
	handle = pcap_open_live(device, BUFSIZ, promiscous_mode, -1, errbuf);

	if (pcap_compile(handle, &fp, protocol, 0, pNet) == -1) {
		perror("pcap_compile() failed");
		exit(-1);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		perror("setfilter failed");
		exit(-1);
	}

	pcap_loop(handle, 0, process_packet, NULL);
	printf("========>>> Tracer terminating...\n");
	return 0;
}

