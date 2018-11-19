#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <netinet/if_ether.h>

int sock;

#define PACKET_LEN sizeof(struct ether_header) + sizeof(struct ether_arp)

void close_sock()
{
   close(sock);
   exit(0);
}

int main(int argc, char ** argv)
{
   char packet[PACKET_LEN];
   struct sockaddr_ll device;
   struct ether_header * eth = (struct ether_header *) packet;
   struct ether_arp * arp = (struct ether_arp *) (packet + sizeof(struct ether_header));
   
   if (argc < 4) 
   {
      puts("Usage: ./a.out <interface> <source ip address> <source mac address>");
    exit(1);
   }

   sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
   if (sock < 0)
     perror("socket"), exit(1);

   signal(SIGINT, close_sock);


  //Source Hardware Address : ARP Packet
   sscanf(argv[3], "%x:%x:%x:%x:%x:%x",  (unsigned int *) &arp->arp_sha[0],
      (unsigned int *) &arp->arp_sha[1],
      (unsigned int *) &arp->arp_sha[2],
      (unsigned int *) &arp->arp_sha[3],
      (unsigned int *) &arp->arp_sha[4],
      (unsigned int *) &arp->arp_sha[5]);

   //Source Protocol Address : ARP Packet
   sscanf(argv[2], "%d.%d.%d.%d", (int *) &arp->arp_spa[0],
                           (int *) &arp->arp_spa[1],
                           (int *) &arp->arp_spa[2],
                           (int *) &arp->arp_spa[3]);

   //Ethernet Packet
   memset(eth->ether_dhost, 0xff, ETH_ALEN);   //destination address : broadcast address
   memcpy(eth->ether_shost, arp->arp_sha, ETH_ALEN); //source address
   eth->ether_type = htons(ETH_P_ARP);    //type

   //ARP Packet
   arp->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);  //Format of hardware address
   arp->ea_hdr.ar_pro = htons(ETH_P_IP);   //Format of protocol address.
   arp->ea_hdr.ar_hln = ETH_ALEN;    //Length of hardware address.
   arp->ea_hdr.ar_pln = 4;      //Length of protocol address.
   arp->ea_hdr.ar_op = htons(ARPOP_REPLY);  //ARP operation : REPLY
   memset(arp->arp_tha, 0xff, ETH_ALEN);   //Target hardware address.
   memset(arp->arp_tpa, 0x00, 4);    //Target protocol address.

   memset(&device, 0, sizeof(device));
   device.sll_ifindex = if_nametoindex(argv[1]);  //Interface number 
   device.sll_family = AF_PACKET;     
   memcpy(device.sll_addr, arp->arp_sha, ETH_ALEN); //Physical layer address
   device.sll_halen = htons(ETH_ALEN);    //Length of address

   printf("Press Ctrl+C to stop \n");
   while (1) {
     printf("Broadcasting on %s: %s is at %s\n", argv[1], argv[2], argv[3]);
     sendto(sock, packet, PACKET_LEN, 0, (struct sockaddr *) &device, sizeof(device));
     sleep(2);
   }
   return 0;
}

