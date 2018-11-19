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

struct sockaddr_in source,dest;

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
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



void receivePackets(){
	int i;
    char *dev; 
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr;
    const u_char *packet;
    struct pcap_pkthdr hdr;     /* pcap.h                    */
    struct ether_header *eptr;  /* net/ethernet.h            */
    struct bpf_program fp;      /* hold compiled program     */
    bpf_u_int32 maskp;          /* subnet mask               */
    bpf_u_int32 netp;           /* ip                        */
    char protocol[]="tcp";
    // dev = pcap_lookupdev(errbuf);
    string s="lo";
    dev=(char*)s.c_str();
    if(dev == NULL)
    { printf("%s\n",errbuf); exit(1); }

	 pcap_lookupnet(dev,&netp,&maskp,errbuf);
    /* open device for reading */
    descr = pcap_open_live(dev,BUFSIZ,0,-1,errbuf);
    if(descr == NULL)
    { printf("pcap_open_live(): %s\n",errbuf); exit(1); }

	 if(pcap_compile(descr,&fp,protocol,0,netp) == -1)
    { fprintf(stderr,"Error calling pcap_compile\n"); exit(1); }

    /* set the compiled program as the filter */
    if(pcap_setfilter(descr,&fp) == -1)
    { fprintf(stderr,"Error setting filter\n"); exit(1); }

    /* allright here we call pcap_loop(..) and pass in our callback function */
    /* int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)*/
    /* If you are wondering what the user argument is all about, so am I!!   */
    pcap_loop(descr,-1,process_packet,NULL);

    fprintf(stdout,"\nDone processing packets... wheew!\n");
    

}

int main(int argc, char const *argv[])
{
	receivePackets();
	
	return 0;
}