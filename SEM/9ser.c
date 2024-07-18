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
   int n; 
   FILE *fp; 
   char buffer[SIZE]; 
   bzero(buffer,SIZE); 
   n= recv(sockfd,buffer, SIZE,0); 
   fp= fopen(buffer,"r"); 
   while((fgets(buffer,SIZE,fp))!=NULL) 
     { 
      if(send(sockfd,buffer,sizeof(buffer),0)==-1) 
        { 
         perror("\nError in sending file"); 
         exit(1); 
        } 
      bzero(buffer,SIZE); 
     } 
   printf("\nFile sent successfully\n"); 
   fclose(fp); 
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
