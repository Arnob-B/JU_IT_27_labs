#include<stdlib.h>
#define maxSize 1000
typedef struct arrQueue{
  int front , rear;
  int data[maxSize];
}
arrQueue;


arrQueue* createArrQueue(){
  arrQueue* queue = (arrQueue*)malloc(sizeof(arrQueue));
  queue->front = queue->rear=-1;
  return queue;
}

void enqueue(arrQueue* queue, int val){
  if(queue->rear == maxSize -1) return;
  queue->data[++queue->rear] = val;
}

int dequeue(arrQueue *queue,int *val){
  if(queue->front == queue->rear)return 0; // either empty
  queue->front = queue->front + 1;
  *val = queue->data[queue->front];
  return 1;
}
int empty(arrQueue * queue){return queue->rear == queue->front;}
int full(arrQueue * queue){return queue->rear == maxSize-1;}
int size(arrQueue * queue) {
  return queue->rear - queue->front;
}
