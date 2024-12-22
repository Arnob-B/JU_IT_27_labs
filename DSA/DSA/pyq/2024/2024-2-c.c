#include"./arrayQueue.c"
#include<stdio.h>

int k = 2;

void multiDeque(arrQueue * queue){
  int m = k;
  while(!empty(queue) && m--){
    int val ;
    dequeue(queue, &val);
    printf("%d ,",val);
  }
  printf("\n");
}
int main(){
  arrQueue * queue = createArrQueue();
  enqueue(queue, 1);
  enqueue(queue, 2);
  enqueue(queue, 3);
  enqueue(queue, 4);
  enqueue(queue, 4);
  multiDeque(queue);
  multiDeque(queue);
  multiDeque(queue);
  multiDeque(queue);
}
