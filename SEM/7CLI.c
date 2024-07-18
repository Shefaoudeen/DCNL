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
        //BUFFER INITIALIZATION
        bzero(buff,MAX);
        read(connfd,buff,sizeof(buff)); //READ
        printf("\nFrom Client : %s \nTo Client : ",buff);
        bzero(buff,MAX);
        n=0;
        while((buff[n++]==getchar())!='\n'); 
        
        write(connfd,buff,sizeof(buff)); //WRITE
        if(strncmp("exit",buff,4)==0){
            printf("\nServer Exits...");
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
    
    struct sockaddr serv;
    
    //SERV PARAMETER ASSIGNING
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_ports = htons(PORT);
    serv.sin_adrs.s_addr = htonls(INADDR_ANY);
    
    if(bind(sockfd,(struct sockaddr*)&serv, sizeof(serv)) != 0){
        printf("Socket bind failed");
        exit(0);
    }
    printf("Socket Successfully binded");
    
    //SERVER LISTENING
    if((listen(sockfd,5)) != 0){
        printf("Listen failed");
        exit(0);
    }
    printf("Server listening")
    
    struct sockaddr cli;
    len = sizeof(cli);
    
    //ACCEPT INCOMING CONNECTION
    int connfd = accept(sockfd,(struct sockaddr)&cli, &len);
    
    if(connfd < 0){
        printf("Server accept failed");
        exit(0);
    }
    
    printf("Server accepted the client");
    func(connfd);
    close(sockfd);
    return 0;
}
