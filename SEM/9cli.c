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
   printf("\nEnter the file name: "); 
   scanf("%s",buffer); 
   fp=fopen("recv.txt","w"); 
   if(send(sockfd,buffer,sizeof(buffer),0)==-1) 
     { 
      perror("\nError in sending file"); 
      exit(1); 
   } 
     bzero(buffer,SIZE); 
     printf("\nFile content:\n"); 
     while(1) 
     { 
      n=recv(sockfd,buffer,SIZE,0); 
      if(n<=0) 
       break; 
        fprintf(fp,"%s",buffer); 
        printf("%s",buffer); 
        bzero(buffer,SIZE); 
     } 
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
