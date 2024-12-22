#include<stdlib.h>
typedef struct heapNode{
  int vertex;
  int weight;
}heapNode;

typedef struct priorityQ{
  int last;
  heapNode * node[100];
}priorityQ;

priorityQ* construct(){
  priorityQ *pq = (priorityQ* )malloc(sizeof(priorityQ));
  pq->last = -1;
  for(int i=0;i<100;i++)pq->node[i] = NULL;
  return pq;
}
void swap(priorityQ * pq,int i,int j){
  int v = pq->node[i]->vertex;
  int w = pq->node[i]->weight;
  pq->node[i]->vertex = pq->node[j]->vertex;
  pq->node[i]->weight = pq->node[j]->weight;
  pq->node[j]->vertex = v;
  pq->node[j]->vertex = w;
}
void enqueue(priorityQ * pq, heapNode * hp){
  pq->last++;
  pq->node[pq->last] = hp;
  int l = pq->last;
  while(((l+1)/2)-1 >= 0 && pq->node[((l+1)/2)-1]->weight < pq->node[l]->weight){
    //swapping
    swap(pq,((l+1)/2) -1,l);
    l = (l/2)-1;
  }
}
int dequeue(priorityQ * pq, heapNode * hp){
  if(pq->last == -1) return 0;
  swap(pq,0,pq->last);
  int l = 0;
  //deletion logic
  pq->last--;
  return 1;
}
int empty(priorityQ *pq){
  return pq->last == -1;
}


int main(){
  int a[4][4] = {
    {0,1,7,3},
    {1,0,4,0},
    {7,4,0,0},
    {3,0,0,0},
  };
  //0
  int dist[4] = {0,0,0,0};
  dist[0] = 0;
  for(int i = 1 ;i<4;i++){
    dist[i] = a[0][i]==0?1e9 : a[0][i];
  }
  priorityQ *pq = construct();
  int visited[4] = {0,0,0,0};
  for(int i=1;i<4;i++){
    heapNode * hp = (heapNode*)malloc(sizeof(heapNode));
    hp->vertex = i;
    hp->weight = dist[i];
    enqueue(pq, hp);
  }
  heapNode *mini;
  while(dequeue(pq,mini)){
    visited[mini->vertex] = 0;
    for(int i =1;i<4;i++){
      int adjVert = i;
      if(a[mini->vertex][adjVert] + mini->weight < dist[adjVert])
      {
        dist[adjVert] = a[mini->vertex][adjVert] + mini->weight;
        heapNode * hp = (heapNode*)malloc(sizeof(heapNode));
        hp->vertex = adjVert;
        hp->weight = dist[adjVert];
        enqueue(pq,hp);
      }
    }
  }
}
