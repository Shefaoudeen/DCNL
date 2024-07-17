//standard extension
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//netinet extension
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

//net extension
#include <netdb.h>
#include <net/ethernet.h>

//sys extension
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/type.h>


int icmp=0,igmp=0,tcp=0,udp=0,ospf=0,others=0;
void ProcessPacket(unsigned char*, int);

int main(){
    
    //buffer allocation and log file creation
    FILE *logfile;
    unsigned char *buffer = (unsigned char *)malloc(65536);
    logfile = fopen("log.txt","w");
    if(logfile == NULL){
        printf("Unable to Create a log txt");
        return 1;
    }
    
    //raw socket creation
    int sock_raw = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    
    //binding to a specific device
    setsockopt(sock_raw,SOL_SOCKET,SO_BINDTODEVICE,"eth()",strlen("eth()")+1);
    
    if(sock_raw < 0){
        printf("Socket error");
        return 1;
    }
    
    struct sockaddr saddr;
    
    while(1){
        int saddr_size = sizeof(saddr);
        
        //packet capture
        int data_size = recvfrom(sock_raw,buffer,65536,0,&saddr,(socklen_t*)&saddr_size);
        if(data_size < 0){
            printf("Recvfrom error, failed to get packets\n");
            return 1;
        }
        ProcessPacket(buffer,data_size);
    }
    
    close(sock_raw);
    printf("Finished!!!");
    return 0;
}

void ProcessPacket(unsigned char *, int){
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    total++;
    
    //protocol update
    switch(iph->protocol){
        case 1:
            icmp++;
            break;
        case 2:
            igmp++;
            break;
        case 6:
            tcp++;
            break;
        case 17:
            udp++;
            break;
        case 89:
            ospf++;
            break;
        default:
            others++;
            break;
    }
    
    //static display
    printf("ICMP : %d IGMP : %d TCP : %d UDP : %d OSPF : %d Others : %d ",icmp,igmp,tcp,udp,ospf,others)
}
