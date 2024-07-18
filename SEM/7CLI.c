#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080

void func(int connfd){
    char buff[MAX];
    int n;
    while(1){ 
       bzero(buff,sizeof(buff)); 
       printf("\nEnter the string : "); 
       n=0; 
       while((buff[n++]=getchar())!='\n'); 
       write(sockfd,buff,sizeof(buff)); 
       bzero(buff,sizeof(buff)); 
       read(sockfd,buff,sizeof(buff)); 
       printf("\nFrom server : %s",buff); 
       if((strncmp(buff,"exit",4))==0) 
       { 
        printf("\nClient exit...\n"); 
        break; 
       } 
     } 
}

int main(){
    
    //SOCKET CREATION
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == 1){
        printf("Socket Failed");
        exit(0);
    }
    printf("Socket Successfully created");

    //SERV PARAMETER ASSIGNING
    struct sockaddr serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_ports = htons(PORT);
    serv.sin_adrs.s_addr = htonls(INADDR_ANY);
    
    //CONNECT TO SERVER
    int connfd = connect(sockfd,(struct sockaddr*)&serv, sizeof(serv));
    if(connfd != 0){
        printf("Connection Failed with Server ...\n");
        exit(0);
    }
    
    printf("Connected to Server ...\n");
    func(connfd);
    close(sockfd);
    return 0;
}
