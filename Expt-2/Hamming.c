 #include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
 int main()  { 
    int data[7],rec[7],i,c1,c2,c3,c; 
    printf("Enter 4 bit message with space:"); 
    scanf("%d %d %d %d",&data[2],&data[4],&data[5],&data[6]); 
    data[0]=data[2]^data[4]^data[6]; 
    data[1]=data[2]^data[5]^data[6]; 
    data[3]=data[4]^data[5]^data[6]; 
    printf("The encoded bits are given below:"); 
    for(i=0;i<7;i++) 
         printf("%d",data[i]); 
    for(i=0;i<7;i++) 
       rec[i]=data[i]; 
    srand(time(NULL)); 
    int random_position = rand() % 8; 
    srand(time(NULL));
    rec[random_position]=rand()%2; 
    printf("\nrand=%d\n",rec[random_position]); 
    printf("Received data:\n"); 
    for(i=0;i<7;i++) 
       printf("%d",rec[i]); 
   c1=rec[0]^rec[2]^rec[4]^rec[6]; 
   c2=rec[1]^rec[2]^rec[5]^rec[6]; 
   c3=rec[3]^rec[4]^rec[5]^rec[6]; 
   c=c3*4+c2*2+c1; 
  if(c==0) 
       printf("\nNo errors"); 
 else { 
     printf("\nError at position:%d\n",c); 
     printf("The correct message is: "); 
     
     rec[c-1] = (rec[c-1]==0) ? 1 : 0;

     for(i=0;i<7;i++) 
             printf("%d",rec[i]); 
     } 
 }
