#include<stdlib.h>
#include<stdio.h>
#include"./arrayQueue.c"
#define MAX 100
typedef struct adjEdge{
  int vertex;
  struct adjEdge *next;
}adjEdge;

typedef struct Graph{
  int noOfVert;
  adjEdge *adjList[MAX];
}Graph;


Graph* createGraph(){
  Graph *graph =(Graph*)malloc(sizeof(Graph));
  graph->noOfVert = 0;
  for(int i=0;i<MAX;i++)graph->adjList[i] = NULL;
  return graph;
}

adjEdge* createVertex(int val){
  adjEdge *v =(adjEdge*)malloc(sizeof(adjEdge));
  v->vertex = val;
  v->next = NULL;
  return v;
}


void DFS(int start, int *visited,Graph *graph){
  if(visited[start]) return;
  printf("%d ", start);
  visited[start] = 1;
  adjEdge * v = graph->adjList[start];
  while(v!=NULL){
    if(!visited[v->vertex]){
      DFS(v->vertex , visited, graph);
    }
    v = v->next;
  }
}
void BFS(int start, int *visited,Graph *graph){
  arrQueue * queue = createArrQueue();
  enqueue(queue,start);
  while(dequeue(queue, &start)){
    if(visited[start])continue;
    printf("%d ,",start);
    visited[start] = 1;
    adjEdge * temp = graph->adjList[start];
    while(temp!=NULL){
      enqueue(queue,temp->vertex);
      temp = temp->next;
    }
  }
}

void addEdge(Graph *graph ,int vertex, adjEdge * vert){
  adjEdge *  temp = graph->adjList[vertex];
  if(temp == NULL){
    graph->noOfVert++;
    graph->adjList[vertex] = vert;
    return;
  }
  while(temp->next !=NULL){
    temp = temp->next;
  }
  temp ->next = vert;
}


int main(){
  Graph *graph  = createGraph();
  addEdge(graph, 0, createVertex(5));
  addEdge(graph, 0, createVertex(2));
  addEdge(graph, 0, createVertex(1));
  addEdge(graph, 0, createVertex(6));
  addEdge(graph, 1, createVertex(0));
  addEdge(graph, 2, createVertex(0));
  addEdge(graph, 3, createVertex(5));
  addEdge(graph, 3, createVertex(4));
  addEdge(graph, 4, createVertex(6));
  addEdge(graph, 4, createVertex(5));
  addEdge(graph, 4, createVertex(3));
  addEdge(graph, 5, createVertex(0));
  addEdge(graph, 5, createVertex(4));
  addEdge(graph, 5, createVertex(3));
  addEdge(graph, 0, createVertex(4));
  addEdge(graph, 6, createVertex(0));
  int visited[] = {0,0,0,0,0,0,0,0};
  BFS(0, visited, graph);
}
