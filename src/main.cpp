#include <iostream>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#define BUFFER_SIZE 4096
using namespace std;


void *p;
void usage(char *);
void IP(), ARP();


int main(int argc, char **argv){
    if(argc != 2){
        usage(argv[0]);

        return EXIT_SUCCESS;
    }

    int fileDescriptor = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(fileDescriptor == -1){
        printf("ERROR: %s\n", strerror(errno));

        return EXIT_FAILURE;
    }

    int interfaceIndex = if_nametoindex(argv[1]);

    struct sockaddr_ll address = {
        .sll_family = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex = interfaceIndex,
        .sll_pkttype = PACKET_HOST
    };

    int value = bind(fileDescriptor, (const struct sockaddr *) &address, sizeof(address));
    if(value == -1){
        printf("ERROR: %s\n", strerror(errno));

        return EXIT_FAILURE;
    }

    unsigned char *buffer = new unsigned char[BUFFER_SIZE]{};
    for(;;){
        value = read(fileDescriptor, buffer, BUFFER_SIZE);

        struct ethhdr ethernet = * (struct ethhdr *) buffer;
        ethernet.h_proto = ntohs(ethernet.h_proto);

        printf("Ethernet\n");

        printf("\tDestination: ");
        for(int i=0; i<ETH_ALEN; ++i){
            printf("%.2hhX", ethernet.h_dest[i]);

            if(i == ETH_ALEN-1) printf("\n");
            else printf(":");
        }

        printf("\tSource: ");
        for(int i=0; i<ETH_ALEN; ++i){
            printf("%.2hhX", ethernet.h_source[i]);

            if(i == ETH_ALEN-1) printf("\n");
            else printf(":");
        }

        printf("\tType: %.4hX\n", ethernet.h_proto);

        p = buffer + sizeof(ethhdr);

        switch(ethernet.h_proto){
            case ETH_P_IP:
                IP();

                break;

            case ETH_P_ARP:
                ARP();

                break;
        }

        printf("\n");
    }

    close(fileDescriptor);

    return EXIT_SUCCESS;
}


void usage(char *name){
    printf("Usage: %s <interface>\n", name);
}