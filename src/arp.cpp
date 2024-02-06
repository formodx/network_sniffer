#include <stdio.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>


struct arphdr{
    uint16_t ar_hrd, ar_pro;
    uint8_t ar_hln, ar_pln;
    uint16_t ar_op;
    uint8_t ar_sha[ETH_ALEN], ar_sip[4];
    uint8_t ar_tha[ETH_ALEN], ar_tip[4];
};
extern void *p;


void ARP(){
    printf("ARP\n");

    struct arphdr header = * (struct arphdr *) p;
    header.ar_hrd = ntohs(header.ar_hrd);
    header.ar_pro = ntohs(header.ar_pro);
    header.ar_op = ntohs(header.ar_op);

    printf("\tSource\n");
    printf("\t\tMAC: ");
    for(int i=0; i<ETH_ALEN; ++i){
        printf("%.2hhX", header.ar_sha[i]);
        printf(i < ETH_ALEN-1 ? ":" : "\n");
    }
    printf("\t\tIP: %hhu.%hhu.%hhu.%hhu\n", header.ar_sip[0], header.ar_sip[1], header.ar_sip[2], header.ar_sip[3]);

    printf("\tTarget\n");
    printf("\t\tMAC: ");
    for(int i=0; i<ETH_ALEN; ++i){
        printf("%.2hhX", header.ar_tha[i]);
        printf(i < ETH_ALEN-1 ? ":" : "\n");
    }
    printf("\t\tIP: %hhu.%hhu.%hhu.%hhu\n", header.ar_tip[0], header.ar_tip[1], header.ar_tip[2], header.ar_tip[3]);
}