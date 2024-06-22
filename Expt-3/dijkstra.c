//dijkstra algorithm to find the shortest path 
#include<stdio.h> 
#define INFINITY 9999 
#define MAX 100 

void dijkstra(int G[MAX][MAX],int n, int snode); 
int main() { 
    int G[MAX][MAX],i,j,n,u; 
  printf("Enter the no of vertices: "); 
  scanf("%d",&n); 
  printf("\nEnter the adjacency matrix [%dX%d]:\n",n,n);  
  
  for(i=0;i<n;i++) 
    for(j=0;j<n;j++) 
      scanf("%d",& G[i][j]); 
  
  printf("\nEnter the starting node: "); 
  scanf("%d",&u); 
  dijkstra(G,n,u); 
  return 0; 
} 
  
void dijkstra(int G[MAX][MAX],int n, int snode) { 
    
  int cost[MAX][MAX],distance[MAX]; 
  int pred[MAX],visited[MAX],count; 
  int mdistance,nextnode,i,j; 
  
  for(i=0;i<n;i++) 
    for(j=0;j<n;j++) 
      cost[i][j] = (G[i][j] == 0) ? INFINITY : G[i][j];
            
  for(i=0;i<n;i++) { 
      distance[i]=cost[snode][i]; 
      pred[i]=snode; 
      visited[snode]=0; 
  } 
        
  distance[snode]=0; 
 
  visited[snode]=1; 
  count=1; 
      
  while(count<n-1){ 
    mdistance=INFINITY; 
      for(i=0;i<n;i++) 
        if(distance[i]<mdistance&&! visited[i]) { 
          mdistance=distance[i]; 
          nextnode=i; 
        }           
    visited[nextnode]=1; 
    for(i=0;i<n;i++) 
        if(!visited[i]) 
          if(mdistance+cost[nextnode][i]<distance[i]) {              
            distance[i]=mdistance+cost[nextnode][i]; 
            pred[i]=nextnode; 
          } 
    count++; 
  }              
    for(i=0;i<n;i++) 
    if(i!=snode) { 
        printf("\nDistance of node %d = %d\t",i,distance [i]); 
        printf("Path =%d",i); 
        j=i;                 
                do { 
          j=pred[j]; 
          printf("<-%d",j); 
        }while(j!=snode); 
    }                        
}         
