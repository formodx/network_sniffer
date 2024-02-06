#include <stdio.h>
#include <arpa/inet.h>


struct iphdr{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ihl:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int ihl:4;
#else
    # error	"Please fix <bits/endian.h>"
#endif

    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint8_t saddr[4];
    uint8_t daddr[4];
};
extern void *p;


void IP(){
    printf("IP\n");

    struct iphdr header = * (struct iphdr *) p;

    header.tot_len = ntohs(header.tot_len);
    header.id = ntohs(header.id);
    header.frag_off = ntohs(header.frag_off);
    header.check = ntohs(header.check);

    printf("\tSource: ");
    for(int i=0; i<4; ++i){
        printf("%hhu", header.saddr[i]);
        printf(i < 3 ? "." : "\n");
    }

    printf("\tDestination: ");
    for(int i=0; i<4; ++i){
        printf("%hhu", header.daddr[i]);
        printf(i < 3 ? "." : "\n");
    }
}