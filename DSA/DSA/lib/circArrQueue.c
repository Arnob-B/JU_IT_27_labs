#include "./arrayQueue.c"


void modifiedEnqeue(arrQueue* queue, int val){
  int r = queue->rear;
  if((r + 1) %maxSize == queue->front){ // full
    return ;
  }
  queue->rear = r;
  queue->data[queue->rear] = val;
}


int modifiedDeque(arrQueue * queue, int *val){
  if(queue->front == queue->rear)  return 0;
  queue->front = (queue->front + 1) % maxSize;
  return 1;
}
