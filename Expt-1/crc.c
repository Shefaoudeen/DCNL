#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

char data[20],divi[20],temp[20],total[20],rec[20]; 
int i,j,datalen,divlen,len,flag=1,t; 
void check(); 

int main() { 
  printf("Enter the total bit of data: ");     
  scanf("%d",&datalen); 
  printf("Enter the total bit of divisor: "); 
  scanf("%d",&divlen); 
  len=datalen+divlen-1;  
  printf("Enter the data: "); 
  scanf("%s",&data);         
  printf("Enter the divisor: "); 
  scanf("%s",divi);     
  for(i=0;i<datalen;i++) { 
        total[i]=data[i];  
        temp[i]=data[i];    
  } 
  for(i=datalen;i<len;i++)     
        total[i]='0';    
  check();
  for(i=0;i<divlen;i++)       
      temp[i+datalen]=data[i];
  printf("\ntransmitted Code Word: %s",temp);     
  strcpy(rec,temp);
  printf("\nReceived data : ");
  for(i=0;i<len;i++)
     printf("%c",rec[i]);
  srand(time(NULL));
  t = rand()%2;
  printf("\nRand = %d\n",t);
  rec[0] = (t>0.5) ? '1' : '0';
  printf("\nReceived data after replacing: ");
  for(i=0;i<len;i++)
      printf("%c",rec[i]);
  strcpy(total,rec);
  check();
  for(i=0;i<divlen-1;i++) 
     if(data[i]=='1') { 
          flag=0; 
          break; 
     } 
  if(flag==1) 
printf("\nsuccessful!!"); 
  else  
printf("\nreceived code word contains errors...\n");  
}
void check() { 
    for(j=0;j<divlen;j++) 
        data[j]=total[j]; 
    while(j<=len) { 
        if(data[0]=='1')  {   
            for(i = 1;i <divlen ; i++) 
              data[i] = (( data[i] == divi[i])?'0':'1'); 
        }
        for(i=0;i<divlen-1;i++)    
            data[i]=data[i+1]; 
        data[i]=total[j++];     
    } 
}
